// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Spell.hpp>

#include <utility>

namespace RosettaStone
{
Entity::Entity(Player& _owner, Card& _card, std::map<GameTag, int> tags)
    : owner(&_owner), card(_card), m_gameTags(std::move(tags))
{
    for (auto& gameTag : _card.gameTags)
    {
        Entity::SetGameTag(gameTag.first, gameTag.second);
    }

    id = tags[GameTag::ENTITY_ID];
    auraEffects = new AuraEffects(this);
}

Entity::Entity(const Entity& ent)
{
    FreeMemory();

    owner = ent.owner;
    card = ent.card;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;
}

Entity::Entity(Entity&& ent) noexcept
{
    FreeMemory();

    owner = ent.owner;
    card = ent.card;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;
}

Entity::~Entity()
{
    FreeMemory();
}

Entity& Entity::operator=(const Entity& ent)
{
    if (this == &ent)
    {
        return *this;
    }

    FreeMemory();

    owner = ent.owner;
    card = ent.card;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;

    return *this;
}

Entity& Entity::operator=(Entity&& ent) noexcept
{
    if (this == &ent)
    {
        return *this;
    }

    FreeMemory();

    owner = ent.owner;
    card = ent.card;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;

    return *this;
}

void Entity::Reset()
{
    SetGameTag(GameTag::DAMAGE, 0);
    SetGameTag(GameTag::EXHAUSTED, 0);
    SetGameTag(GameTag::ATK, 0);
    SetGameTag(GameTag::HEALTH, 0);
    SetGameTag(GameTag::COST, 0);
    SetGameTag(GameTag::TAUNT, 0);
    SetGameTag(GameTag::FROZEN, 0);
    SetGameTag(GameTag::CHARGE, 0);
    SetGameTag(GameTag::WINDFURY, 0);
    SetGameTag(GameTag::DIVINE_SHIELD, 0);
    SetGameTag(GameTag::STEALTH, 0);
    SetGameTag(GameTag::NUM_ATTACKS_THIS_TURN, 0);
}

int Entity::GetGameTag(GameTag tag) const
{
    int value = 0;

    if (m_gameTags.find(tag) == m_gameTags.end())
    {
        if (auraEffects != nullptr)
        {
            value += auraEffects->GetGameTag(tag);
        }
    }
    else
    {
        value += m_gameTags.at(tag);

        if (auraEffects != nullptr)
        {
            value += auraEffects->GetGameTag(tag);
        }
    }

    return value > 0 ? value : 0;
}

void Entity::SetGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
}

ZoneType Entity::GetZoneType() const
{
    return static_cast<ZoneType>(GetGameTag(GameTag::ZONE));
}

void Entity::SetZoneType(ZoneType type)
{
    SetGameTag(GameTag::ZONE, static_cast<int>(type));
}

int Entity::GetCost() const
{
    return GetGameTag(GameTag::COST);
}

void Entity::SetCost(int cost)
{
    SetGameTag(GameTag::COST, cost);
}

bool Entity::GetExhausted() const
{
    return static_cast<bool>(GetGameTag(GameTag::EXHAUSTED));
}

void Entity::SetExhausted(bool exhausted)
{
    SetGameTag(GameTag::EXHAUSTED, static_cast<int>(exhausted));
}

bool Entity::HasCombo() const
{
    return GetGameTag(GameTag::COMBO) == 1;
}

bool Entity::HasOverload() const
{
    return GetGameTag(GameTag::OVERLOAD) > 0;
}

int Entity::GetOverload() const
{
    return GetGameTag(GameTag::OVERLOAD);
}

void Entity::Destroy()
{
    isDestroyed = true;
}

Entity* Entity::GetFromCard(Player& player, Card&& card,
                            std::optional<std::map<GameTag, int>> cardTags,
                            IZone* zone, int id)
{
    std::map<GameTag, int> tags;
    if (cardTags.has_value())
    {
        tags = cardTags.value();
    }

    tags[GameTag::ENTITY_ID] = id > 0 ? id : player.GetGame()->GetNextID();
    tags[GameTag::CONTROLLER] = player.playerID;
    tags[GameTag::ZONE] =
        zone != nullptr ? static_cast<int>(zone->GetType()) : 0;

    Entity* result;

    switch (card.GetCardType())
    {
        case CardType::HERO:
            result = new Hero(player, card, tags);
            break;
        case CardType::HERO_POWER:
            result = new HeroPower(player, card, tags);
            break;
        case CardType::MINION:
            result = new Minion(player, card, tags);
            break;
        case CardType::SPELL:
            result = new Spell(player, card, tags);
            break;
        case CardType::WEAPON:
            result = new Weapon(player, card, tags);
            break;
        default:
            throw std::invalid_argument(
                "Generic::DrawCard() - Invalid card type!");
    }

    return result;
}

void Entity::FreeMemory()
{
    delete auraEffects;
    delete onGoingEffect;

    m_gameTags.clear();
}
}  // namespace RosettaStone
