// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Aura.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

#include <algorithm>

namespace RosettaStone
{
Aura::Aura(std::string&& enchantmentID, AuraType type)
    : m_enchantmentID(enchantmentID), m_type(type)
{
    // Do nothing
}

Aura::Aura(Aura& prototype, Entity& owner)
    : condition(prototype.condition),
      restless(prototype.restless),
      m_enchantmentID(prototype.m_enchantmentID),
      m_type(prototype.m_type),
      m_owner(&owner),
      m_effects(prototype.m_effects),
      m_turnOn(prototype.m_turnOn)
{
    // Do nothing
}

void Aura::SetToBeUpdated(bool value)
{
    m_toBeUpdated = value;
}

void Aura::Activate(Entity& owner)
{
    Card card = Cards::FindCardByID(m_enchantmentID);

    if (m_effects.empty())
    {
        m_effects = card.power.GetEnchant().value().effects;
    }

    Aura* instance = new Aura(*this, owner);

    owner.owner->GetGame()->auras.emplace_back(instance);
    owner.onGoingEffect = instance;

    instance->AddToField();

    switch (m_type)
    {
        case AuraType::FIELD:
        {
            for (auto& minion : owner.owner->GetFieldZone().GetAll())
            {
                if (condition == nullptr || condition->Evaluate(minion))
                {
                    if (card.power.GetTrigger().has_value())
                    {
                        const auto enchantment = Enchantment::GetInstance(
                            *owner.owner, card, minion);
                        card.power.GetTrigger().value().Activate(*enchantment);
                    }
                }

                instance->m_tempList.emplace_back(minion);
            }
            break;
        }
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            for (auto& minion : owner.owner->GetFieldZone().GetAll())
            {
                if (minion == &owner)
                {
                    continue;
                }

                if (condition == nullptr || condition->Evaluate(minion))
                {
                    if (card.power.GetTrigger().has_value())
                    {
                        const auto enchantment = Enchantment::GetInstance(
                            *owner.owner, card, minion);
                        card.power.GetTrigger().value().Activate(*enchantment);
                    }
                }

                instance->m_tempList.emplace_back(minion);
            }
            break;
        }
        default:
            break;
    }
}

void Aura::Update()
{
    if (!m_toBeUpdated)
    {
        return;
    }

    UpdateInternal();
}

void Aura::Remove()
{
    m_turnOn = false;
    m_toBeUpdated = true;
    m_owner->onGoingEffect = nullptr;
}

void Aura::RemoveEntity(Entity& entity)
{
    if (&entity == m_owner)
    {
        Remove();
    }
    else
    {
        if (m_appliedEntities.empty())
        {
            return;
        }
        const auto iter = std::find(m_appliedEntities.cbegin(),
                                    m_appliedEntities.cend(), &entity);
        if (iter != m_appliedEntities.end())
        {
            m_appliedEntities.erase(iter);
        }
    }
}

void Aura::Apply(Entity& entity)
{
    const auto iter =
        std::find(m_appliedEntities.begin(), m_appliedEntities.end(), &entity);
    if (iter != m_appliedEntities.end())
    {
        if (!restless || (condition != nullptr && condition->Evaluate(&entity)))
        {
            return;
        }

        for (auto& effect : m_effects)
        {
            effect.Remove(*entity.auraEffects);
        }

        m_appliedEntities.erase(iter);
    }

    if (condition != nullptr && !condition->Evaluate(&entity))
    {
        return;
    }

    for (auto& effect : m_effects)
    {
        effect.Apply(*entity.auraEffects);
    }

    m_appliedEntities.emplace_back(&entity);
}

void Aura::AddToField()
{
    switch (m_type)
    {
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
            m_owner->owner->GetFieldZone().auras.emplace_back(this);
            break;
        default:
            throw std::invalid_argument(
                "Aura::AddToField() - Invalid aura type!");
    }
}

void Aura::UpdateInternal()
{
    if (m_turnOn)
    {
        if (!m_tempList.empty())
        {
            for (auto& temp : m_tempList)
            {
                Apply(*temp);
            }

            m_tempList.clear();
        }

        switch (m_type)
        {
            case AuraType::ADJACENT:
            {
                const int pos = m_owner->zonePos;
                auto& field = m_owner->owner->GetFieldZone();

                const int entitySize =
                    static_cast<int>(m_appliedEntities.size());
                for (int i = entitySize - 1; i >= 0; --i)
                {
                    Entity* entity = m_appliedEntities[i];

                    if (m_owner->zone == entity->zone &&
                        std::abs(pos - entity->zonePos) == 1)
                    {
                        continue;
                    }

                    for (auto& effect : m_effects)
                    {
                        effect.Remove(*entity->auraEffects);
                    }

                    auto iter = std::find(m_appliedEntities.begin(),
                                          m_appliedEntities.end(), entity);
                    if (iter != m_appliedEntities.end())
                    {
                        m_appliedEntities.erase(iter);
                    }
                }

                if (pos > 0)
                {
                    Apply(*field[pos - 1]);
                }
                if (pos < m_owner->owner->GetFieldZone().GetCount() - 1 &&
                    m_owner->owner->GetFieldZone().GetCount() > pos)
                {
                    Apply(*field[pos + 1]);
                }

                break;
            }
            case AuraType::FIELD:
                for (auto& minion : m_owner->owner->GetFieldZone().GetAll())
                {
                    Apply(*minion);
                }
                break;
            case AuraType::FIELD_EXCEPT_SOURCE:
            {
                for (auto& minion : m_owner->owner->GetFieldZone().GetAll())
                {
                    if (minion != m_owner)
                    {
                        Apply(*minion);
                    }
                }
                break;
            }
            default:
                throw std::invalid_argument(
                    "Aura::UpdateInternal() - Invalid aura type!");
        }

        if (!restless)
        {
            m_toBeUpdated = false;
        }
    }
    else
    {
        RemoveInternal();
    }
}

void Aura::RemoveInternal()
{
    switch (m_type)
    {
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            auto auras = m_owner->owner->GetFieldZone().auras;
            const auto iter = std::find(auras.begin(), auras.end(), this);
            auras.erase(iter);
            break;
        }
        default:
            throw std::invalid_argument(
                "Aura::RemoveInternal() - Invalid aura type!");
    }

    for (auto& entity : m_appliedEntities)
    {
        for (auto& effect : m_effects)
        {
            effect.Remove(*entity->auraEffects);
        }
    }

    auto auras = m_owner->owner->GetGame()->auras;
    const auto iter = std::find(auras.begin(), auras.end(), this);
    auras.erase(iter);
}

AuraType Aura::GetAuraType() const
{
    return m_type;
}

std::vector<Effect> Aura::GetEffects() const
{
    return m_effects;
}

std::vector<Entity*> Aura::GetAppliedEntities() const
{
    return m_appliedEntities;
}
}  // namespace RosettaStone
