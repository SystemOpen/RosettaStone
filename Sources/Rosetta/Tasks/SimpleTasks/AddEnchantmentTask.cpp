// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
AddEnchantmentTask::AddEnchantmentTask(std::string&& cardID,
                                       EntityType entityType)
    : ITask(entityType), m_cardID(cardID)
{
    // Do nothing
}

TaskID AddEnchantmentTask::GetTaskID() const
{
    return TaskID::ADD_ENCHANTMENT;
}

TaskStatus AddEnchantmentTask::Impl(Player& player)
{
    Card enchantmentCard = Cards::FindCardByID(m_cardID);
    if (enchantmentCard.id.empty())
    {
        return TaskStatus::STOP;
    }

    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    Power power = enchantmentCard.power;

    for (auto& entity : entities)
    {
        const auto enchantment =
            Enchantment::GetInstance(player, enchantmentCard, entity);

        if (power.GetAura().has_value())
        {
            power.GetAura().value().Activate(*enchantment);
        }

        if (power.GetTrigger().has_value())
        {
            power.GetTrigger().value().Activate(*enchantment);
        }

        if (power.GetEnchant().has_value())
        {
            const auto& taskStack = player.GetGame()->taskStack;
            power.GetEnchant().value().ActivateTo(entity, taskStack.num,
                                                  taskStack.num1);
        }
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
