// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Attack.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone::Generic
{
void Attack(Player& player, Character* source, Character* target)
{
    // Check source can attack and target is valid
    if (!source->CanAttack() ||
        !source->IsValidCombatTarget(*player.opponent, target))
    {
        return;
    }

    // Activate attack trigger
    player.GetGame()->triggerManager.OnAttackTrigger(&player, source);
    player.GetGame()->ProcessTasks();

    // Set game step to MAIN_COMBAT
    player.GetGame()->step = Step::MAIN_COMBAT;

    // Get attack of source and target
    const int targetAttack = target->GetAttack();
    const int sourceAttack = source->GetAttack();

    // Take damage to target
    const int targetDamage = target->TakeDamage(*source, sourceAttack);
    const bool isTargetDamaged = targetDamage > 0;

    // Freeze target if attacker is freezer
    if (isTargetDamaged && source->GetGameTag(GameTag::FREEZE) == 1)
    {
        target->SetGameTag(GameTag::FROZEN, 1);
    }

    // Destroy target if attacker is poisonous
    if (isTargetDamaged && source->GetGameTag(GameTag::POISONOUS) == 1)
    {
        target->Destroy();
    }

    // Ignore damage from defenders with 0 attack
    if (targetAttack > 0)
    {
        // Take damage to source
        const int sourceDamage = source->TakeDamage(*target, targetAttack);
        const bool isSourceDamaged = sourceDamage > 0;

        // Freeze source if defender is freezer
        if (isSourceDamaged && target->GetGameTag(GameTag::FREEZE) == 1)
        {
            source->SetGameTag(GameTag::FROZEN, 1);
        }

        // Destroy source if defender is poisonous
        if (isSourceDamaged && target->GetGameTag(GameTag::POISONOUS) == 1)
        {
            source->Destroy();
        }
    }

    // Remove stealth ability if attacker has it
    if (source->GetGameTag(GameTag::STEALTH) == 1)
    {
        source->SetGameTag(GameTag::STEALTH, 0);
    }

    // Remove durability from weapon if hero attack
    Hero* hero = dynamic_cast<Hero*>(source);
    if (hero != nullptr && hero->weapon != nullptr &&
        hero->weapon->GetGameTag(GameTag::IMMUNE) == 0)
    {
        int prevValue = hero->weapon->GetDurability();
        hero->weapon->SetDurability(prevValue - 1);

        // Destroy weapon if durability is 0
        if (hero->weapon->GetDurability() == 0)
        {
            hero->RemoveWeapon();
        }
    }

    // Increase the number of attacked
    source->SetNumAttacksThisTurn(source->GetNumAttacksThisTurn() + 1);

    // Check source is exhausted
    if ((source->GetNumAttacksThisTurn() >= 1 &&
         source->GetGameTag(GameTag::WINDFURY) == 0) ||
        (source->GetNumAttacksThisTurn() >= 2 &&
         source->GetGameTag(GameTag::WINDFURY) == 1))
    {
        source->SetExhausted(true);
    }

    // Process destroy and update aura
    player.GetGame()->ProcessDestroyAndUpdateAura();

    // Set game step to MAIN_ACTION
    player.GetGame()->step = Step::MAIN_ACTION;
}
}  // namespace RosettaStone::Generic
