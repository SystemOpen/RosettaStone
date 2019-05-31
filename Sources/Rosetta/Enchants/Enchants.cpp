// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Enchants/Enchants.hpp>

#include <regex>

namespace RosettaStone
{
Enchant Enchants::GetEnchantFromText(const std::string& cardID)
{
    std::vector<Effect> effects;
    bool isOneTurn = false;

    static std::regex attackHealthRegex("\\+([[:digit:]]+)/\\+([[:digit:]]+)");
    static std::regex attackRegex("\\+([[:digit:]]+) Attack");
    static std::regex healthRegex("\\+([[:digit:]]+) Health");

    const std::string text = Cards::FindCardByID(cardID).text;
    std::smatch values;

    if (std::regex_search(text, values, attackHealthRegex))
    {
        effects.emplace_back(Effects::AttackN(std::stoi(values[1].str())));
        effects.emplace_back(Effects::HealthN(std::stoi(values[2].str())));
    }
    else if (std::regex_search(text, values, attackRegex))
    {
        effects.emplace_back(Effects::AttackN(std::stoi(values[1].str())));
    }
    else if (std::regex_search(text, values, healthRegex))
    {
        effects.emplace_back(Effects::HealthN(std::stoi(values[1].str())));
    }

    if (text.find("<b>Taunt</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Taunt);
    }

    if (text.find("<b>Charge</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Charge);
    }

    if (text.find("this turn") != std::string::npos)
    {
        isOneTurn = true;
    }

    return Enchant(effects, false, isOneTurn);
}
}  // namespace RosettaStone
