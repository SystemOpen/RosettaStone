// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/Effect.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Character.hpp>

#include <stdexcept>

namespace RosettaStone
{
Effect::Effect(GameTag gameTag, EffectOperator effectOperator, int value)
    : m_gameTag(gameTag), m_effectOperator(effectOperator), m_value(value)
{
    // Do nothing
}

void Effect::Apply(Entity* entity, bool isOneTurnEffect) const
{
    auto& oneTurnEffects = entity->owner->GetGame()->oneTurnEffects;

    if (isOneTurnEffect)
    {
        oneTurnEffects.emplace_back(std::make_pair(entity, new Effect(*this)));
    }

    const int prevValue = entity->GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            entity->SetGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SUB:
            entity->SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::MUL:
            entity->SetGameTag(m_gameTag, prevValue * m_value);
            break;
        case EffectOperator::SET:
            if (m_gameTag == GameTag::CHARGE)
            {
                if (entity->GetExhausted() &&
                    entity->GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN) == 0)
                {
                    entity->SetExhausted(false);
                }
            }
            entity->SetGameTag(m_gameTag, m_value);
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}

void Effect::Apply(AuraEffects& auraEffects) const
{
    const int prevValue = auraEffects.GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            auraEffects.SetGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SUB:
            auraEffects.SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SET:
            auraEffects.SetGameTag(m_gameTag, m_value);
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}

void Effect::Remove(Entity* entity) const
{
    const int prevValue = entity->GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            entity->SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SUB:
            entity->SetGameTag(m_gameTag,
                               entity->card.gameTags.at(m_gameTag) + m_value);
            break;
        case EffectOperator::SET:
            entity->SetGameTag(m_gameTag, 0);
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}

void Effect::Remove(AuraEffects& auraEffects) const
{
    if (m_gameTag == GameTag::HEALTH && m_effectOperator == EffectOperator::ADD)
    {
        auto owner = dynamic_cast<Character*>(auraEffects.GetOwner());
        const int prevDamage = owner->GetDamage();
        owner->SetDamage(prevDamage - m_value);
    }

    const int prevValue = auraEffects.GetGameTag(m_gameTag);

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            auraEffects.SetGameTag(m_gameTag, prevValue - m_value);
            break;
        case EffectOperator::SUB:
            auraEffects.SetGameTag(m_gameTag, prevValue + m_value);
            break;
        case EffectOperator::SET:
            auraEffects.SetGameTag(m_gameTag, prevValue - m_value);
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}
  
Effect Effect::ChangeValue(int newValue) const
{
    return Effect(m_gameTag, m_effectOperator, newValue);
}

EffectOperator Effect::GetEffectOperator() const
{
    return m_effectOperator;
}

GameTag Effect::GetGameTag() const
{
    return m_gameTag;
}

int Effect::GetValue() const
{
    return m_value;
}
}  // namespace RosettaStone
