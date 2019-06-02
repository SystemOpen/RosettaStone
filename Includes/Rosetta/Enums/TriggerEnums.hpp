// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_ENUMS_HPP
#define ROSETTASTONE_TRIGGER_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying trigger type.
enum class TriggerType
{
    NONE,        //!< The effect has nothing.
    TURN_START,  //!< The effect will be triggered at the start of turn.
    TURN_END,    //!< The effect will be triggered at the end of turn.
    PLAY_CARD,   //!< The effect will be triggered when a player plays a card.
    CAST_SPELL,  //!< The effect will be triggered when a player plays a Spell
                 //!< card.
    HEAL,        //!< The effect will be triggered when characters are healed.
    ATTACK,      //!< The effect will be triggered when characters attack.
    SUMMON,  //!< The effect will be triggered whenever a minion is summoned.
    TAKE_DAMAGE,  //!< The effect will be triggered when a spell or a character
                  //!< deals damages.
};

//! \brief An enumerator for identifying trigger source.
enum class TriggerSource
{
    NONE,
    SELF,
    HERO,
    ALL_MINIONS,
    MINIONS_EXCEPT_SELF,
    ENCHANTMENT_TARGET,
    FRIENDLY,
};

//! \brief An enumerator for identifying sequence type.
enum class SequenceType
{
    NONE,
    PLAY_CARD,
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_ENUMS_HPP
