﻿// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/CardSets/CoreCardsGen.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddStackToTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ArmorTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/CopyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/CountTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/EnqueueTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FlagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealFullTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ManaCrystalTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathSubTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomEntourageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ReturnHandTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/TempManaTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/TransformTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/WeaponTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
void CoreCardsGen::AddHeroes(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- HERO - WARRIOR
    // [HERO_01] Garrosh Hellscream - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 725
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_01", power);

    // ------------------------------------------ HERO - SHAMAN
    // [HERO_02] Thrall - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 687
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_02", power);

    // ------------------------------------------- HERO - ROGUE
    // [HERO_03] Valeera Sanguinar - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 730
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_03", power);

    // ----------------------------------------- HERO - PALADIN
    // [HERO_04] Uther Lightbringer - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 472
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_04", power);

    // ------------------------------------------ HERO - HUNTER
    // [HERO_05] Rexxar - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 229
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_05", power);

    // ------------------------------------------- HERO - DRUID
    // [HERO_06] Malfurion Stormrage - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 1123
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_06", power);

    // ----------------------------------------- HERO - WARLOCK
    // [HERO_07] Gul'dan - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 300
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_07", power);

    // -------------------------------------------- HERO - MAGE
    // [HERO_08] Jaina Proudmoore - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 807
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_08", power);

    // ------------------------------------------ HERO - PRIEST
    // [HERO_09] Anduin Wrynn - COST:0 [ATK:0/HP:30]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - HERO_POWER = 479
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("HERO_09", power);
}

void CoreCardsGen::AddHeroPowers(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------ HERO_POWER - PRIEST
    // [CS1h_001] Lesser Heal (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Restore #2 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 2));
    cards.emplace("CS1h_001", power);

    // ------------------------------------- HERO_POWER - DRUID
    // [CS2_017] Shapeshift (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       +1 Attack this turn.    +1 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_017o", EntityType::HERO));
    power.AddPowerTask(new ArmorTask(1));
    cards.emplace("CS2_017", power);

    // -------------------------------------- HERO_POWER - MAGE
    // [CS2_034] Fireblast (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal $1 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1, false));
    cards.emplace("CS2_034", power);

    // ------------------------------------ HERO_POWER - SHAMAN
    // [CS2_049] Totemic Call (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a random Totem.
    // --------------------------------------------------------
    // Entourage: CS2_050, CS2_051, CS2_052, NEW1_009
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new FuncNumberTask([](Entity* entity) {
        auto minions = entity->owner->GetFieldZone().GetAll();
        std::vector<Card> totemCards;
        totemCards.reserve(4);

        for (const auto& id : entity->card.entourages)
        {
            bool exist = false;
            for (auto minion : minions)
            {
                if (id == minion->card.id)
                {
                    exist = true;
                    break;
                }
            }

            if (!exist)
            {
                totemCards.emplace_back(Cards::GetInstance().FindCardByID(id));
            }
        }

        if (totemCards.empty())
        {
            return;
        }

        const auto idx = Random::get<int>(0, totemCards.size() - 1);
        Entity* totem =
            Entity::GetFromCard(*entity->owner, std::move(totemCards[idx]));
        entity->owner->GetFieldZone().Add(*dynamic_cast<Minion*>(totem));
    }));
    cards.emplace("CS2_049", power);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [CS2_056] Life Tap (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Draw a card and take $2 damage.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::HERO, 2, false));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("CS2_056", power);

    // ------------------------------------- HERO_POWER - ROGUE
    // [CS2_083b] Dagger Mastery (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Equip a 1/2 Dagger.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new WeaponTask("CS2_082"));
    cards.emplace("CS2_083b", power);

    // ----------------------------------- HERO_POWER - PALADIN
    // [CS2_101] Reinforce (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a 1/1 Silver Hand Recruit.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("CS2_101t", SummonSide::DEFAULT));
    cards.emplace("CS2_101", power);

    // ----------------------------------- HERO_POWER - WARRIOR
    // [CS2_102] Armor Up! (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Gain 2 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ArmorTask(2));
    cards.emplace("CS2_102", power);

    // ------------------------------------ HERO_POWER - HUNTER
    // [DS1h_292] Steady Shot (*) - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal $2 damage to the enemy hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_STEADY_SHOT = 0
    // - REQ_MINION_OR_ENEMY_HERO = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_HERO, 2, false));
    cards.emplace("DS1h_292", power);
}

void CoreCardsGen::AddDruid(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [CS2_005] Claw - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn. Gain 2 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ArmorTask(2));
    power.AddPowerTask(new AddEnchantmentTask("CS2_005o", EntityType::HERO));
    cards.emplace("CS2_005", power);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_007] Healing Touch - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore #8 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 8));
    cards.emplace("CS2_007", power);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_008] Moonfire - COST:0
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1, true));
    cards.emplace("CS2_008", power);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_009] Mark of the Wild - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Taunt</b> and +2/+2.<i>
    //       (+2 Attack/+2 Health)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_009e", EntityType::TARGET));
    cards.emplace("CS2_009", power);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_011] Savage Roar - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your characters +2 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_011o", EntityType::FRIENDS));
    cards.emplace("CS2_011", power);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_012] Swipe - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $4 damage to an enemy and $1 damage to all other enemies.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 4, true));
    power.AddPowerTask(new DamageTask(EntityType::ENEMIES_NOTARGET, 1, true));
    cards.emplace("CS2_012", power);

    // ------------------------------------------ SPELL - DRUID
    // [CS2_013] Wild Growth - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain an empty Mana Crystal.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ManaCrystalTask(1, false));
    cards.emplace("CS2_013", power);

    // ----------------------------------------- MINION - DRUID
    // [CS2_232] Ironbark Protector - COST:8 [ATK:8/HP:8]
    // - Faction: neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_232", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_169] Innervate - COST:0
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new TempManaTask(1));
    cards.emplace("EX1_169", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_173] Starfire - COST:6
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $5 damage.
    //       Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 5));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("EX1_173", power);
}

void CoreCardsGen::AddDruidNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS2_005o] Claw (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_005o"));
    cards.emplace("CS2_005o", power);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS2_009e] Mark of the Wild (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_009e"));
    cards.emplace("CS2_009e", power);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS2_011o] Savage Roar (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_011o"));
    cards.emplace("CS2_011o", power);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [CS2_017o] Claws (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Your hero has +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_017o"));
    cards.emplace("CS2_017o", power);
}

void CoreCardsGen::AddHunter(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - HUNTER
    // [CS2_084] Hunter's Mark - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Change a minion's Health to 1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_084e", EntityType::TARGET));
    cards.emplace("CS2_084", power);

    // ---------------------------------------- MINION - HUNTER
    // [CS2_237] Starving Buzzard - COST:5 [ATK:3/HP:2]
    // - Race: Beast, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever you summon a Beast, draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger(TriggerType::SUMMON));
    power.GetTrigger().value().triggerSource =
        TriggerSource::MINIONS_EXCEPT_SELF;
    power.GetTrigger().value().condition =
        new SelfCondition(SelfCondition::IsRace(Race::BEAST));
    power.GetTrigger().value().tasks = { new DrawTask(1) };
    cards.emplace("CS2_237", power);

    // ---------------------------------------- MINION - HUNTER
    // [DS1_070] Houndmaster - COST:4 [ATK:4/HP:3]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Beast +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("DS1_070o", EntityType::TARGET));
    cards.emplace("DS1_070", power);

    // ---------------------------------------- MINION - HUNTER
    // [DS1_175] Timber Wolf - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other Beasts have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(Aura("DS1_175o", AuraType::FIELD_EXCEPT_SOURCE));
    power.GetAura().value().condition =
        new SelfCondition(SelfCondition::IsRace(Race::BEAST));
    cards.emplace("DS1_175", power);

    // ---------------------------------------- MINION - HUNTER
    // [DS1_178] Tundra Rhino - COST:5 [ATK:2/HP:5]
    // - Race: Beast, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Your Beasts have <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(Aura("DS1_178e", AuraType::FIELD));
    power.GetAura().value().condition =
        new SelfCondition(SelfCondition::IsRace(Race::BEAST));
    cards.emplace("DS1_178", power);

    // ----------------------------------------- SPELL - HUNTER
    // [DS1_183] Multi-Shot - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage to two random enemy minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::ENEMY_MINIONS, 2));
    power.AddPowerTask(new DamageTask(EntityType::STACK, 3, true));
    cards.emplace("DS1_183", power);

    // ----------------------------------------- SPELL - HUNTER
    // [DS1_184] Tracking - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Look at the top 3 cards of your deck. Draw one and discard
    // the others.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new FuncNumberTask([](Entity* entity) {
        DeckZone& deck = entity->owner->GetDeckZone();
        if (deck.IsEmpty())
        {
            return;
        }

        std::vector<std::size_t> ids;
        ids.reserve(3);

        for (int i = 0; i < 3 && deck.GetCount() != 0; ++i)
        {
            Entity* card = deck.GetTopCard();
            deck.Remove(*card);
            ids.emplace_back(card->id);
            entity->owner->GetSetasideZone().Add(*card);
        }

        Generic::CreateChoice(*entity->owner, ChoiceType::GENERAL,
                              ChoiceAction::HAND, ids);
    }));
    cards.emplace("DS1_184", power);

    // ----------------------------------------- SPELL - HUNTER
    // [DS1_185] Arcane Shot - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    cards.emplace("DS1_185", power);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_539] Kill Command - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage. If you control a Beast, deal
    //       $5 damage instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ConditionTask(
        EntityType::SOURCE, { SelfCondition::IsControllingRace(Race::BEAST) }));
    power.AddPowerTask(
        new FlagTask(true, new DamageTask(EntityType::TARGET, 5, true)));
    power.AddPowerTask(
        new FlagTask(false, new DamageTask(EntityType::TARGET, 3, true)));
    cards.emplace("EX1_539", power);

    // ----------------------------------------- SPELL - HUNTER
    // [NEW1_031] Animal Companion - COST:3
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon a random Beast Companion.
    // --------------------------------------------------------
    // Entourage: NEW1_032, NEW1_033, NEW1_034
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomEntourageTask());
    power.AddPowerTask(new SummonTask());
    cards.emplace("NEW1_031", power);
}

void CoreCardsGen::AddHunterNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [CS2_084e] Hunter's Mark (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: This minion has 1 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant(GameTag::HEALTH, EffectOperator::SET, 1));
    cards.emplace("CS2_084e", power);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DS1_070o] Master's Presence (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DS1_070o"));
    cards.emplace("DS1_070o", power);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DS1_175o] Furious Howl (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +1 Attack from Timber Wolf.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DS1_175o"));
    cards.emplace("DS1_175o", power);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DS1_178e] Charge (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Tundra Rhino grants <b>Charge</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DS1_178e"));
    cards.emplace("DS1_178e", power);

    // ---------------------------------------- MINION - HUNTER
    // [NEW1_032] Misha (*) - COST:3 [ATK:4/HP:4]
    // - Race: Beast, Set: Core, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("NEW1_032", power);

    // ---------------------------------------- MINION - HUNTER
    // [NEW1_033] Leokk (*) - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: Core, Rarity: Common
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(Aura("NEW1_033o", AuraType::FIELD_EXCEPT_SOURCE));
    cards.emplace("NEW1_033", power);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [NEW1_033o] Eye In The Sky (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Leokk is granting this minion +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("NEW1_033o"));
    cards.emplace("NEW1_033o", power);

    // ---------------------------------------- MINION - HUNTER
    // [NEW1_034] Huffer (*) - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: Core, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("NEW1_034", power);
}

void CoreCardsGen::AddMage(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------- SPELL - MAGE
    // [CS2_022] Polymorph - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Transform a minion
    //       into a 1/1 Sheep.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new TransformTask(EntityType::TARGET, "CS2_tk1"));
    cards.emplace("CS2_022", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_023] Arcane Intellect - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(2));
    cards.emplace("CS2_023", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_024] Frostbolt - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage to a_character and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3, true));
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::FROZEN, 1));
    cards.emplace("CS2_024", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_025] Arcane Explosion - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage to all enemy minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_MINIONS, 1, true));
    cards.emplace("CS2_025", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_026] Frost Nova - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Freeze</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SetGameTagTask(EntityType::ENEMY_MINIONS, GameTag::FROZEN, 1));
    cards.emplace("CS2_026", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_027] Mirror Image - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon two 0/2 minions with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("CS2_mirror", 2));
    cards.emplace("CS2_027", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_029] Fireball - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $6 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 6, true));
    cards.emplace("CS2_029", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_032] Flamestrike - COST:7
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $4 damage to all enemy minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_MINIONS, 4, true));
    cards.emplace("CS2_032", power);

    // ------------------------------------------ MINION - MAGE
    // [CS2_033] Water Elemental - COST:4 [ATK:3/HP:6]
    // - Race: Elemental, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_033", power);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_277] Arcane Missiles - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new EnqueueTask({ new RandomTask(EntityType::ENEMIES, 1),
                                         new DamageTask(EntityType::STACK, 1) },
                                       3, true));
    cards.emplace("EX1_277", power);
}

void CoreCardsGen::AddMageNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddPaladin(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_087] Blessing of Might - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +3 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_087e", EntityType::TARGET));
    cards.emplace("CS2_087", power);

    // --------------------------------------- MINION - PALADIN
    // [CS2_088] Guardian of Kings - COST:7 [ATK:5/HP:6]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 6 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::HERO, 6));
    cards.emplace("CS2_088", power);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_089] Holy Light - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore #6 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 6));
    cards.emplace("CS2_089", power);

    // --------------------------------------- WEAPON - PALADIN
    // [CS2_091] Light's Justice - COST:1 [ATK:1/HP:0]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_091", power);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_092] Blessing of Kings - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +4/+4. <i>(+4 Attack/+4 Health)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_092e", EntityType::TARGET));
    cards.emplace("CS2_092", power);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_093] Consecration - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage to all enemies.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMIES, 2, true));
    cards.emplace("CS2_093", power);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_094] Hammer of Wrath - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage.
    //       Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3, true));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("CS2_094", power);

    // --------------------------------------- WEAPON - PALADIN
    // [CS2_097] Truesilver Champion - COST:4 [ATK:4/HP:0]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever your hero attacks, restore 2 Health to it.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger(TriggerType::ATTACK));
    power.GetTrigger().value().triggerSource = TriggerSource::HERO;
    power.GetTrigger().value().tasks = { new HealTask(EntityType::HERO, 2) };
    cards.emplace("CS2_097", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_360] Humility - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Change a minion's Attack to 1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_360e", EntityType::TARGET));
    cards.emplace("EX1_360", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_371] Hand of Protection - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Divine Shield</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("EX1_371", power);
}

void CoreCardsGen::AddPaladinNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [CS2_087e] Blessing of Might (*) - COST:0
    // - Faction: Neutral, Set: Core
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_087e"));
    cards.emplace("CS2_087e", power);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [CS2_092e] Blessing of Kings (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_092e"));
    cards.emplace("CS2_092e", power);

    // --------------------------------------- MINION - PALADIN
    // [CS2_101t] Silver Hand Recruit (*) - COST:1 [ATK:1/HP:1]
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_101t", power);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_360e] Humility (*) - COST:0
    // - Faction: Neutral, Set: Core
    // --------------------------------------------------------
    // Text: Attack has been changed to 1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant(GameTag::ATK, EffectOperator::SET, 1));
    cards.emplace("EX1_360e", power);
}

void CoreCardsGen::AddPriest(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_112] Holy Nova - COST:5
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage to all enemies.
    //       Restore #2 Health to all friendly characters.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMIES, 2, true));
    power.AddPowerTask(new HealTask(EntityType::FRIENDS, 2));
    cards.emplace("CS1_112", power);

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_113] Mind Control - COST:10
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Take control of an enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ControlTask(EntityType::TARGET));
    cards.emplace("CS1_113", power);

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_130] Holy Smite - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    cards.emplace("CS1_130", power);

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_003] Mind Vision - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Put a copy of a random card in your opponent's hand into your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::ENEMY_HAND, 1));
    power.AddPowerTask(new CopyTask(EntityType::STACK, 1));
    power.AddPowerTask(new AddStackToTask(EntityType::HAND));
    cards.emplace("CS2_003", power);

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_004] Power Word: Shield - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion +2 Health.
    //       Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_004e", EntityType::TARGET));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("CS2_004", power);

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_234] Shadow Word: Pain - COST:2
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a minion with 3 or less Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_MAX_ATTACK = 3
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    cards.emplace("CS2_234", power);

    // ---------------------------------------- MINION - PRIEST
    // [CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever a minion is healed, draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger(TriggerType::HEAL));
    power.GetTrigger().value().triggerSource = TriggerSource::ALL_MINIONS;
    power.GetTrigger().value().tasks = { new DrawTask(1) };
    cards.emplace("CS2_235", power);

    // ----------------------------------------- SPELL - PRIEST
    // [CS2_236] Divine Spirit - COST:2
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Double a minion's Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new GetGameTagTask(EntityType::TARGET, GameTag::HEALTH));
    power.AddPowerTask(new MathSubTask(EntityType::TARGET, GameTag::DAMAGE));
    power.AddPowerTask(new AddEnchantmentTask("CS2_236e", EntityType::TARGET));
    cards.emplace("CS2_236", power);

    // ----------------------------------------- SPELL - PRIEST
    // [DS1_233] Mind Blast - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $5 damage to the enemy hero.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_HERO, 5, true));
    cards.emplace("DS1_233", power);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_622] Shadow Word: Death - COST:3
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a minion with 5 or more Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MIN_ATTACK = 5
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    cards.emplace("EX1_622", power);
}

void CoreCardsGen::AddPriestNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CS2_004e] Power Word: Shield (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_004e"));
    cards.emplace("CS2_004e", power);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CS2_236e] Divine Spirit (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: This minion has double Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant(Enchants::AddHealthScriptTag));
    cards.emplace("CS2_236e", power);
}

void CoreCardsGen::AddRogue(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_072] Backstab - COST:0
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage to an undamaged minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_UNDAMAGED_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    cards.emplace("CS2_072", power);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_074] Deadly Poison - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your weapon +2 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_074e", EntityType::WEAPON));
    cards.emplace("CS2_074", power);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_075] Sinister Strike - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage to the enemy hero.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_HERO, 3, true));
    cards.emplace("CS2_075", power);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_076] Assassinate - COST:5
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy an enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    cards.emplace("CS2_076", power);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_077] Sprint - COST:7
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Draw 4 cards.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(4));
    cards.emplace("CS2_077", power);

    // ----------------------------------------- WEAPON - ROGUE
    // [CS2_080] Assassin's Blade - COST:5 [ATK:3/HP:0]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_080", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_129] Fan of Knives - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage to all enemy minions.
    //       Draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_MINIONS, 1, true));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("EX1_129", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_278] Shiv - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage.
    //       Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1, true));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("EX1_278", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_581] Sap - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Return an enemy minion to your opponent's hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ReturnHandTask(EntityType::TARGET));
    cards.emplace("EX1_581", power);

    // ------------------------------------------ SPELL - ROGUE
    // [NEW1_004] Vanish - COST:6
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Return all minions to their owner's hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ReturnHandTask(EntityType::ALL_MINIONS));
    cards.emplace("NEW1_004", power);
}

void CoreCardsGen::AddRogueNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- WEAPON - ROGUE
    // [CS2_082] Wicked Knife (*) - COST:1 [ATK:1/HP:0]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_082", power);
}

void CoreCardsGen::AddShaman(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_037] Frost Shock - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage to an enemy character and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1, true));
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::FROZEN, 1));
    cards.emplace("CS2_037", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_039] Windfury - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Windfury</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::WINDFURY, 1));
    cards.emplace("CS2_039", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_041] Ancestral Healing - COST:0
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore a minion
    //       to full Health and
    //       give it <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // Tag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealFullTask(EntityType::TARGET));
    power.AddPowerTask(new AddEnchantmentTask("CS2_041e", EntityType::TARGET));
    cards.emplace("CS2_041", power);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_042] Fire Elemental - COST:6 [ATK:6/HP:5]
    // - Race: Elemental, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3));
    cards.emplace("CS2_042", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_045] Rockbiter Weapon - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a friendly character +3 Attack this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_045e", EntityType::TARGET));
    cards.emplace("CS2_045", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_046] Bloodlust - COST:5
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your minions +3 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_046e", EntityType::MINIONS));
    cards.emplace("CS2_046", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_244] Totemic Might - COST:0
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your Totems +2 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new FilterStackTask(EntityType::MINIONS,
                                           SelfCondition::IsRace(Race::TOTEM)));
    power.AddPowerTask(new AddEnchantmentTask("EX1_244e", EntityType::STACK));
    cards.emplace("EX1_244", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_246] Hex - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Transform a minion into a 0/1 Frog with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new TransformTask(EntityType::TARGET, "hexfrog"));
    cards.emplace("EX1_246", power);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_565] Flametongue Totem - COST:2 [ATK:0/HP:3]
    // - Race: Totem, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Adjacent minions have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ADJACENT_BUFF = 1
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(Aura("EX1_565o", AuraType::ADJACENT));
    cards.emplace("EX1_565", power);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_587] Windspeaker - COST:4 [ATK:3/HP:3]
    // - Faction: Neutral, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::WINDFURY, 1));
    cards.emplace("EX1_587", power);
}

void CoreCardsGen::AddShamanNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_041e] Ancestral Infusion (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Taunt.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant(Effects::Taunt));
    cards.emplace("CS2_041e", power);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_045e] Rockbiter Weapon (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: This character has +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_045e"));
    cards.emplace("CS2_045e", power);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_046e] Bloodlust (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_046e"));
    cards.emplace("CS2_046e", power);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_050] Searing Totem (*) - COST:1 [ATK:1/HP:1]
    // - Race: Totem, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_050", power);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_051] Stoneclaw Totem (*) - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_051", power);

    // ---------------------------------------- MINION - SHAMAN
    // [CS2_052] Wrath of Air Totem (*) - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_052", power);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [EX1_244e] Totemic Might (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_244e"));
    cards.emplace("EX1_244e", power);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [EX1_565o] Flametongue (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +2 Attack from Flametongue Totem.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_565o"));
    cards.emplace("EX1_565o", power);

    // ---------------------------------------- MINION - SHAMAN
    // [NEW1_009] Healing Totem (*) - COST:1 [ATK:0/HP:2]
    // - Race: Totem, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: At the end of your turn, restore 1 Health to all friendly minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger(TriggerType::TURN_END));
    power.GetTrigger().value().tasks = { new HealTask(EntityType::MINIONS, 1) };
    cards.emplace("NEW1_009", power);
}

void CoreCardsGen::AddWarlock(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_057] Shadow Bolt - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $4 damage
    //       to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 4, true));
    cards.emplace("CS2_057", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_061] Drain Life - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage. Restore #2 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    power.AddPowerTask(new HealTask(EntityType::HERO, 2));
    cards.emplace("CS2_061", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_062] Hellfire - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage to all characters.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ALL, 3, true));
    cards.emplace("CS2_062", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_063] Corruption - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Choose an enemy minion. At the start of your turn, destroy it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_063e", EntityType::TARGET));
    cards.emplace("CS2_063", power);

    // --------------------------------------- MINION - WARLOCK
    // [CS2_064] Dread Infernal - COST:6 [ATK:6/HP:6]
    // - Race: Demon, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to ALL other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ALL, 1));
    cards.emplace("CS2_064", power);

    // --------------------------------------- MINION - WARLOCK
    // [CS2_065] Voidwalker - COST:1 [ATK:1/HP:3]
    // - Race: Demon, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_065", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_302] Mortal Coil - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage to a minion. If that kills it, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1, true));
    power.AddPowerTask(
        new ConditionTask(EntityType::TARGET, { SelfCondition::IsDead() }));
    power.AddPowerTask(new FlagTask(true, new DrawTask(1)));
    cards.emplace("EX1_302", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_306] Succubus - COST:2 [ATK:4/HP:3]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a random card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::HAND, 1));
    power.AddPowerTask(new DiscardTask(EntityType::STACK));
    cards.emplace("EX1_306", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_308] Soulfire - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $4 damage.
    //       Discard a random card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 4));
    power.AddPowerTask(new RandomTask(EntityType::HAND, 1));
    power.AddPowerTask(new DiscardTask(EntityType::STACK));
    cards.emplace("EX1_308", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [NEW1_003] Sacrificial Pact - COST:0
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a Demon. Restore #5 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 15
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    power.AddPowerTask(new HealTask(EntityType::HERO, 5));
    cards.emplace("NEW1_003", power);
}

void CoreCardsGen::AddWarlockNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [CS2_063e] Corruption (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: At the start of the corrupting player's turn, destroy this minion.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger(TriggerType::TURN_START));
    power.GetTrigger().value().tasks = { new DestroyTask(EntityType::TARGET) };
    cards.emplace("CS2_063e", power);
}

void CoreCardsGen::AddWarrior(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_103] Charge - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a friendly minion <b>Charge</b>. It can't attack heroes this
    // turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_103e2", EntityType::TARGET));
    cards.emplace("CS2_103", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_105] Heroic Strike - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_105e", EntityType::HERO));
    cards.emplace("CS2_105", power);

    // --------------------------------------- WEAPON - WARRIOR
    // [CS2_106] Fiery War Axe - COST:3 [ATK:3/HP:0]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_106", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_108] Execute - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Destroy a damaged enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    cards.emplace("CS2_108", power);

    // --------------------------------------- WEAPON - WARRIOR
    // [CS2_112] Arcanite Reaper - COST:5 [ATK:5/HP:0]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_112", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_114] Cleave - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage to two random enemy minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::ENEMY_MINIONS, 2));
    power.AddPowerTask(new DamageTask(EntityType::STACK, 2, true));
    cards.emplace("CS2_114", power);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_084] Warsong Commander - COST:3 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Your <b>Charge</b> minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(Aura("EX1_084e", AuraType::FIELD));
    power.GetAura().value().condition =
        new SelfCondition(SelfCondition::IsTagValue(GameTag::CHARGE, 1));
    power.GetAura().value().restless = true;
    cards.emplace("EX1_084", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_400] Whirlwind - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage to all minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ALL_MINIONS, 1, true));
    cards.emplace("EX1_400", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_606] Shield Block - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    //       Draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ArmorTask(5));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("EX1_606", power);

    // --------------------------------------- MINION - WARRIOR
    // [NEW1_011] Kor'kron Elite - COST:4 [ATK:4/HP:3]
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("NEW1_011", power);
}

void CoreCardsGen::AddWarriorNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CS2_103e2] Charge (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Has <b>Charge</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(
        Enchant({ Effects::Charge, Effect(GameTag::CANNOT_ATTACK_HEROES,
                                          EffectOperator::SET, 1) }));
    power.AddTrigger(Trigger(TriggerType::TURN_END));
    power.GetTrigger().value().tasks = { new SetGameTagTask(
        EntityType::TARGET, GameTag::CANNOT_ATTACK_HEROES, 0) };
    power.GetTrigger().value().removeAfterTriggered = true;
    cards.emplace("CS2_103e2", power);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CS2_105e] Heroic Strike (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_105e"));
    cards.emplace("CS2_105e", power);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_084e] Charge (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Warsong Commander is granting this minion +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_084e"));
    cards.emplace("EX1_084e", power);
}

void CoreCardsGen::AddNeutral(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [CS1_042] Goldshire Footman - COST:1 [ATK:1/HP:2]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS1_042", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_118] Magma Rager - COST:3 [ATK:5/HP:1]
    // - Race: Elemental, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_118", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_119] Oasis Snapjaw - COST:4 [ATK:2/HP:7]
    // - Race: Beast, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_119", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_120] River Crocolisk - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_120", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_121] Frostwolf Grunt - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_121", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_122] Raid Leader - COST:3 [ATK:2/HP:2]
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(Aura("CS2_122e", AuraType::FIELD_EXCEPT_SOURCE));
    cards.emplace("CS2_122", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_124", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_125] Ironfur Grizzly - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_125", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_127] Silverback Patriarch - COST:3 [ATK:1/HP:4]
    // - Race: Beast, Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_127", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_131] Stormwind Knight - COST:4 [ATK:2/HP:5]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_131", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_141] Ironforge Rifleman - COST:3 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1));
    cards.emplace("CS2_141", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_142] Kobold Geomancer - COST:2 [ATK:2/HP:2]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_142", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_147] Gnomish Inventor - COST:4 [ATK:2/HP:4]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("CS2_147", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_150] Stormpike Commando - COST:5 [ATK:4/HP:2]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2));
    cards.emplace("CS2_150", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_155] Archmage - COST:6 [ATK:4/HP:7]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_155", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_162] Lord of the Arena - COST:6 [ATK:6/HP:5]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_162", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_168] Murloc Raider - COST:1 [ATK:2/HP:1]
    // - Race: Murloc, Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_168", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_171] Stonetusk Boar - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_171", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_172] Bloodfen Raptor - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_172", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_173] Bluegill Warrior - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_173", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_179", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_182", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_186] War Golem - COST:7 [ATK:7/HP:7]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_186", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_187] Booty Bay Bodyguard - COST:5 [ATK:5/HP:4]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_187", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_189] Elven Archer - COST:1 [ATK:1/HP:1]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1));
    cards.emplace("CS2_189", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_196] Razorfen Hunter - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Boar.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("CS2_boar", SummonSide::RIGHT));
    cards.emplace("CS2_196", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_197] Ogre Magi - COST:4 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_197", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_200] Boulderfist Ogre - COST:6 [ATK:6/HP:7]
    // - Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_200", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_201] Core Hound - COST:7 [ATK:9/HP:5]
    // - Race: Beast, Set: Core, Rarity: Free
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_201", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_213] Reckless Rocketeer - COST:6 [ATK:5/HP:2]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_213", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_222] Stormwind Champion - COST:7 [ATK:6/HP:6]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other minions have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(Aura("CS2_222o", AuraType::FIELD_EXCEPT_SOURCE));
    cards.emplace("CS2_222", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_226] Frostwolf Warlord - COST:5 [ATK:4/HP:4]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1/+1 for each other friendly minion on the
    // battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new CountTask(EntityType::MINIONS_NOSOURCE));
    power.AddPowerTask(new AddEnchantmentTask("CS2_226e", EntityType::SOURCE));
    cards.emplace("CS2_226", power);

    // --------------------------------------- MINION - NEUTRAL
    // [DS1_055] Darkscale Healer - COST:5 [ATK:4/HP:5]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health to all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::FRIENDS, 2));
    cards.emplace("DS1_055", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_011] Voodoo Doctor - COST:1 [ATK:2/HP:1]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 2));
    cards.emplace("EX1_011", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_015] Novice Engineer - COST:2 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("EX1_015", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_019] Shattered Sun Cleric - COST:3 [ATK:3/HP:2]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_019e", EntityType::TARGET));
    cards.emplace("EX1_019", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_025] Dragonling Mechanic - COST:4 [ATK:2/HP:4]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/1 Mechanical Dragonling.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("EX1_025t", SummonSide::RIGHT));
    cards.emplace("EX1_025", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::ENEMY_WEAPON));
    cards.emplace("EX1_066", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_399] Gurubashi Berserker - COST:5 [ATK:2/HP:7]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, gain +3 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(Trigger(TriggerType::TAKE_DAMAGE));
    power.GetTrigger().value().triggerSource = TriggerSource::SELF;
    power.GetTrigger().value().tasks = { new AddEnchantmentTask(
        "EX1_399e", EntityType::SOURCE) };
    cards.emplace("EX1_399", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_506] Murloc Tidehunter - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("EX1_506a", SummonSide::RIGHT));
    cards.emplace("EX1_506", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_508] Grimscale Oracle - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Your other Murlocs have +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(Aura("EX1_508o", AuraType::FIELD_EXCEPT_SOURCE));
    power.GetAura().value().condition =
        new SelfCondition(SelfCondition::IsRace(Race::MURLOC));
    cards.emplace("EX1_508", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_582] Dalaran Mage - COST:3 [ATK:1/HP:4]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_582", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_593] Nightblade - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry: </b>Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_HERO, 3));
    cards.emplace("EX1_593", power);
}

void CoreCardsGen::AddNeutralNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_074e] Deadly Poison (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_074e"));
    cards.emplace("CS2_074e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_122e] Enhanced (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Raid Leader is granting this minion +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_122e"));
    cards.emplace("CS2_122e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_222o] Might of Stormwind (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Has +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_222o"));
    cards.emplace("CS2_222o", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_226e] Frostwolf Banner (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchant(Enchants::AddAttackHealthScriptTag));
    cards.emplace("CS2_226e", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_boar] Boar (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Core, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_boar", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_tk1] Sheep (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Core, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_tk1", power);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [EX1_019e] Cleric's Blessing (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_019e"));
    cards.emplace("EX1_019e", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_025t] Mechanical Dragonling (*) - COST:1 [ATK:2/HP:1]
    // - Race: Mechanical, Faction: Neutral, Set: Core, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_025t", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_506a] Murloc Scout (*) - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Faction: Neutral, Set: Core, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_506a", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_508o] Mlarggragllabl! (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: This Murloc has +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_508o"));
    cards.emplace("EX1_508o", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_399e] Berserking (*) - COST:0
    // - Set: Core
    // --------------------------------------------------------
    // Text: This minion has increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Effects::AttackN(3));
    cards.emplace("EX1_399e", power);

    // --------------------------------------- MINION - NEUTRAL
    // [hexfrog] Frog (*) - COST:0 [ATK:0/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Core, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("hexfrog", power);
}

void CoreCardsGen::AddAll(std::map<std::string, Power>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddDruid(cards);
    AddDruidNonCollect(cards);

    AddHunter(cards);
    AddHunterNonCollect(cards);

    AddMage(cards);
    AddMageNonCollect(cards);

    AddPaladin(cards);
    AddPaladinNonCollect(cards);

    AddPriest(cards);
    AddPriestNonCollect(cards);

    AddRogue(cards);
    AddRogueNonCollect(cards);

    AddShaman(cards);
    AddShamanNonCollect(cards);

    AddWarlock(cards);
    AddWarlockNonCollect(cards);

    AddWarrior(cards);
    AddWarriorNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone
