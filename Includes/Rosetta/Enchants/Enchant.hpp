// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_ENCHANT_HPP
#define ROSETTASTONE_ENCHANT_HPP

#include <Rosetta/Enchants/Effect.hpp>

#include <vector>

namespace RosettaStone
{
class Entity;

//!
//! \brief Enchant class.
//!
//! This class stores an enchantment, also known as a buff or debuff. It is a
//! special effect gained by a minion, or in rarer occasions by a weapon.
//!
class Enchant
{
 public:
    //! Default constructor.
    Enchant() = default;

    //! Constructs enchant with given \p gameTag, \p effectOperator and
    //! \p value.
    //! \param gameTag The game tag of the card.
    //! \param effectOperator The effect operator to change card value.
    //! \param value The value to change.
    Enchant(GameTag gameTag, EffectOperator effectOperator, int value);

    //! Constructs enchant with given \p effect.
    //! \param effect The effect of the card.
    explicit Enchant(Effect& effect);

    //! Constructs enchant with given \p _effect, \p _useScriptTag and
    //! \p _isOneTurnEffect.
    //! \param effect The effect of the card.
    //! \param _useScriptTag A flag to use script tag.
    //! \param _isOneTurnEffect A flag whether this is one-turn effect.
    Enchant(Effect&& effect, bool _useScriptTag = false,
            bool _isOneTurnEffect = false);

    //! Constructs enchant with given \p _effects, \p _useScriptTag and
    //! \p _isOneTurnEffect.
    //! \param _effects A list of effect.
    //! \param _useScriptTag A flag to use script tag.
    //! \param _isOneTurnEffect A flag whether this is one-turn effect.
    Enchant(std::vector<Effect> _effects, bool _useScriptTag = false,
            bool _isOneTurnEffect = false);

    //! Activates enchant to \p entity.
    //! \param entity An entity to which enchant is activated.
    //! \param num1 The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \param num2 The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    void ActivateTo(Entity* entity, int num1, int num2);

    std::vector<Effect> effects;

    bool useScriptTag = false;
    bool isOneTurnEffect = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ENCHANT_HPP
