// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Power.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Policies/Policy.hpp>
#include <Rosetta/Tasks/ITask.hpp>
#include <Rosetta/Tasks/PlayerTasks/ChooseTask.hpp>

#include <effolkronium/random.hpp>

#include <algorithm>

using Random = effolkronium::random_static;
using namespace RosettaStone::PlayerTasks;

namespace RosettaStone
{
Game::Game(GameConfig& gameConfig) : m_gameConfig(gameConfig)
{
    // Set game to player
    for (auto& p : m_players)
    {
        p.SetGame(this);
    }

    // Set player type
    GetPlayer1().playerType = PlayerType::PLAYER1;
    GetPlayer2().playerType = PlayerType::PLAYER2;

    // Add hero and hero power
    GetPlayer1().AddHeroAndPower(
        Cards::GetHeroCard(gameConfig.player1Class),
        Cards::GetDefaultHeroPower(gameConfig.player1Class));
    GetPlayer2().AddHeroAndPower(
        Cards::GetHeroCard(gameConfig.player2Class),
        Cards::GetDefaultHeroPower(gameConfig.player2Class));

    // Set opponent player
    GetPlayer1().opponent = &GetPlayer2();
    GetPlayer2().opponent = &GetPlayer1();
}

Player& Game::GetPlayer1()
{
    return m_players[0];
}

Player& Game::GetPlayer2()
{
    return m_players[1];
}

Player& Game::GetCurrentPlayer() const
{
    return *m_currentPlayer;
}

Player& Game::GetOpponentPlayer() const
{
    return *m_currentPlayer->opponent;
}

std::size_t Game::GetNextID()
{
    return m_entityID++;
}

std::size_t Game::GetNextOOP()
{
    return m_oopIndex++;
}

void Game::BeginFirst()
{
    // Set next step
    nextStep = Step::BEGIN_SHUFFLE;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::BeginShuffle()
{
    // Shuffle cards in deck
    if (m_gameConfig.doShuffle)
    {
        GetPlayer1().GetDeckZone().Shuffle();
        GetPlayer2().GetDeckZone().Shuffle();
    }

    // Set next step
    nextStep = Step::BEGIN_DRAW;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::BeginDraw()
{
    for (auto& p : m_players)
    {
        // Draw 3 cards
        Generic::Draw(p);
        Generic::Draw(p);
        Generic::Draw(p);

        if (&p != m_firstPlayer)
        {
            // Draw 4th card for second player
            Generic::Draw(p);

            // Give "The Coin" card to second player
            Card coin = Cards::FindCardByID("GAME_005");
            p.GetHandZone().Add(*Entity::GetFromCard(p, std::move(coin)));
        }
    }

    // Set next step
    nextStep =
        m_gameConfig.skipMulligan ? Step::MAIN_BEGIN : Step::BEGIN_MULLIGAN;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::BeginMulligan()
{
    // Start mulligan state
    GetPlayer1().mulliganState = Mulligan::INPUT;
    GetPlayer2().mulliganState = Mulligan::INPUT;

    // Collect cards that can redraw
    std::vector<std::size_t> p1HandIDs, p2HandIDs;
    for (auto& entity : GetPlayer1().GetHandZone().GetAll())
    {
        p1HandIDs.emplace_back(entity->id);
    }
    for (auto& entity : GetPlayer2().GetHandZone().GetAll())
    {
        p2HandIDs.emplace_back(entity->id);
    }

    // Create choice for each player
    Generic::CreateChoice(GetPlayer1(), ChoiceType::MULLIGAN,
                          ChoiceAction::HAND, p1HandIDs);
    Generic::CreateChoice(GetPlayer2(), ChoiceType::MULLIGAN,
                          ChoiceAction::HAND, p2HandIDs);
}

void Game::MainBegin()
{
    // Set next step
    nextStep = Step::MAIN_READY;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainReady()
{
    // Reset the number of attacked
    for (auto& p : m_players)
    {
        // Hero
        p.GetHero()->SetNumAttacksThisTurn(0);
        // Field
        for (auto& m : p.GetFieldZone().GetAll())
        {
            m->SetNumAttacksThisTurn(0);
        }
    }

    // Reset exhaust for current player
    auto& curPlayer = GetCurrentPlayer();
    // Hero
    curPlayer.GetHero()->SetExhausted(false);
    // Weapon
    if (curPlayer.GetHero()->weapon != nullptr)
    {
        curPlayer.GetHero()->weapon->SetExhausted(false);
    }
    // Hero power
    curPlayer.GetHero()->heroPower->SetExhausted(false);
    // Field
    for (auto& m : curPlayer.GetFieldZone().GetAll())
    {
        m->SetExhausted(false);
    }

    // Reset combo active
    curPlayer.SetComboActive(false);

    // Set next step
    nextStep = Step::MAIN_START_TRIGGERS;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainStartTriggers()
{
    triggerManager.OnStartTurnTrigger(&GetCurrentPlayer(), nullptr);
    ProcessTasks();
    ProcessDestroyAndUpdateAura();

    // Set next step
    nextStep = Step::MAIN_RESOURCE;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainResource()
{
    auto& curPlayer = GetCurrentPlayer();

    // Add mana crystal to current player
    Generic::ChangeManaCrystal(curPlayer, 1, false);

    // Clear used mana
    curPlayer.SetUsedMana(0);
    // Remove temporary mana
    curPlayer.SetTemporaryMana(0);

    // Process overload
    curPlayer.SetOverloadLocked(curPlayer.GetOverloadOwed());
    curPlayer.SetOverloadOwed(0);

    // Set next step
    nextStep = Step::MAIN_DRAW;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainDraw()
{
    // Draw a card for current player
    Generic::Draw(GetCurrentPlayer());

    // Set next step
    nextStep = Step::MAIN_START;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainStart()
{
    // Set next step
    nextStep = Step::MAIN_ACTION;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainAction()
{
    // Do nothing
}

void Game::MainEnd()
{
    triggerManager.OnEndTurnTrigger(&GetCurrentPlayer(), nullptr);
    ProcessTasks();
    ProcessDestroyAndUpdateAura();

    // Set next step
    nextStep = Step::MAIN_CLEANUP;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainCleanUp()
{
    auto& curPlayer = GetCurrentPlayer();

    // Remove one-turn effects
    for (auto& effectPair : oneTurnEffects)
    {
        Entity* entity = effectPair.first;
        Effect* effect = effectPair.second;

        effect->Remove(entity);
        delete effect;
    }
    oneTurnEffects.clear();

    // Unfreeze all characters they control that are Frozen, don't have
    // summoning sickness (or do have Charge) and have not attacked that turn
    // Hero
    if (curPlayer.GetHero()->GetGameTag(GameTag::FROZEN) == 1 &&
        curPlayer.GetHero()->GetNumAttacksThisTurn() == 0)
    {
        curPlayer.GetHero()->SetGameTag(GameTag::FROZEN, 0);
    }
    // Field
    for (auto& m : curPlayer.GetFieldZone().GetAll())
    {
        if (m->GetGameTag(GameTag::FROZEN) == 1 &&
            m->GetNumAttacksThisTurn() == 0 && !m->GetExhausted())
        {
            m->SetGameTag(GameTag::FROZEN, 0);
        }
    }

    // Set next step
    nextStep = Step::MAIN_NEXT;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::MainNext()
{
    // Set player for next turn
    m_currentPlayer = m_currentPlayer->opponent;

    // Count next turn
    m_turn++;

    // Set next step
    nextStep = Step::MAIN_READY;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::FinalWrapUp()
{
    // Set game states according by result
    for (auto& p : m_players)
    {
        if (p.playState == PlayState::LOSING ||
            p.playState == PlayState::CONCEDED)
        {
            p.playState = PlayState::LOST;
            p.opponent->playState = PlayState::WON;
        }
    }

    // Set next step
    nextStep = Step::FINAL_GAMEOVER;
    GameManager::ProcessNextStep(*this, nextStep);
}

void Game::FinalGameOver()
{
    // Set game state to complete
    state = State::COMPLETE;
}

void Game::StartGame()
{
    // Reverse card order in deck
    if (!m_gameConfig.doShuffle)
    {
        std::reverse(m_gameConfig.player1Deck.begin(),
                     m_gameConfig.player1Deck.end());
        std::reverse(m_gameConfig.player2Deck.begin(),
                     m_gameConfig.player2Deck.end());
    }

    // Set up decks
    for (auto& card : m_gameConfig.player1Deck)
    {
        if (card.id.empty())
        {
            continue;
        }

        Entity* entity = Entity::GetFromCard(GetPlayer1(), std::move(card));
        GetPlayer1().GetDeckZone().Add(*entity);
    }
    for (auto& card : m_gameConfig.player2Deck)
    {
        if (card.id.empty())
        {
            continue;
        }

        Entity* entity = Entity::GetFromCard(GetPlayer2(), std::move(card));
        GetPlayer2().GetDeckZone().Add(*entity);
    }

    // Fill cards to deck
    if (m_gameConfig.doFillDecks)
    {
        for (auto& p : m_players)
        {
            for (auto& cardID : m_gameConfig.fillCardIDs)
            {
                Card card = Cards::FindCardByID(cardID);
                Entity* entity = Entity::GetFromCard(p, std::move(card));
                p.GetDeckZone().Add(*entity);
            }
        }
    }

    // Set game states
    state = State::RUNNING;
    for (auto& p : m_players)
    {
        p.playState = PlayState::PLAYING;
    }

    // Determine first player
    switch (m_gameConfig.startPlayer)
    {
        case PlayerType::RANDOM:
        {
            const auto val = Random::get(0, 1);
            m_firstPlayer = &m_players[val];
            break;
        }
        case PlayerType::PLAYER1:
            m_firstPlayer = &m_players[0];
            break;
        case PlayerType::PLAYER2:
            m_firstPlayer = &m_players[1];
            break;
    }
    m_currentPlayer = m_firstPlayer;

    // Set first turn
    m_turn = 1;

    // Set next step
    nextStep = Step::BEGIN_FIRST;
    if (m_gameConfig.autoRun)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::ProcessTasks()
{
    while (!taskQueue.empty())
    {
        ITask* task = taskQueue.front();
        taskQueue.pop_front();

        task->Run(GetCurrentPlayer());
    }
}

void Game::ProcessDestroyAndUpdateAura()
{
    UpdateAura();

    // Process summoned minions
    if (triggerManager.summonTrigger != nullptr)
    {
        for (auto& minion : summonedMinions)
        {
            triggerManager.OnSummonTrigger(&GetCurrentPlayer(), minion);
        }
    }

    do
    {
        ProcessGraveyard();
        ProcessTasks();
    } while (!deadMinions.empty());

    UpdateAura();
}

void Game::ProcessGraveyard()
{
    // Destroy weapons
    if (GetPlayer1().GetHero()->weapon != nullptr &&
        GetPlayer1().GetHero()->weapon->isDestroyed)
    {
        GetPlayer1().GetHero()->RemoveWeapon();
    }
    if (GetPlayer2().GetHero()->weapon != nullptr &&
        GetPlayer2().GetHero()->weapon->isDestroyed)
    {
        GetPlayer2().GetHero()->RemoveWeapon();
    }

    // Destroy minions
    if (!deadMinions.empty())
    {
        for (auto& deadMinion : deadMinions)
        {
            Minion* minion = deadMinion.second;

            // Remove minion from battlefield
            minion->SetLastBoardPos(minion->zonePos);
            minion->zone->Remove(*minion);

            // Process deathrattle tasks
            for (auto& power : minion->card.power.GetDeathrattleTask())
            {
                if (power == nullptr)
                {
                    continue;
                }

                power->Run(*minion->owner);
            }

            // Add minion to graveyard
            minion->owner->GetGraveyardZone().Add(*minion);
        }

        deadMinions.clear();
    }

    CheckGameOver();
}

void Game::UpdateAura()
{
    const int auraSize = static_cast<int>(auras.size());
    if (auraSize == 0)
    {
        return;
    }

    for (int i = auraSize - 1; i >= 0; --i)
    {
        auras[i]->Update();
    }
}

void Game::Process(Player& player, ITask* task)
{
    // Process task
    Task::Run(player, task);

    CheckGameOver();
}

void Game::Process(Player& player, ITask&& task)
{
    // Process task
    Task::Run(player, std::move(task));

    CheckGameOver();
}

void Game::ProcessUntil(Step untilStep)
{
    m_gameConfig.autoRun = false;
    while (nextStep != untilStep)
    {
        GameManager::ProcessNextStep(*this, nextStep);
    }
}

void Game::PlayPolicy()
{
    StartGame();

    Player& player1 = GetPlayer1();
    // Request mulligan choices to policy.
    TaskMeta p1Choice = player1.policy->Require(player1, TaskID::MULLIGAN);

    // Get mulligan choices from policy.
    Process(player1,
            PlayerTasks::ChooseTask::Mulligan(
                player1, p1Choice.GetObject<std::vector<std::size_t>>()));

    Player& player2 = GetPlayer2();
    // Request mulligan choices to policy.
    TaskMeta p2Choice = player2.policy->Require(player2, TaskID::MULLIGAN);

    // Get mulligan choices from policy.
    Process(player2,
            PlayerTasks::ChooseTask::Mulligan(
                player2, p2Choice.GetObject<std::vector<std::size_t>>()));

    MainReady();

    while (state != State::COMPLETE)
    {
        auto& player = GetCurrentPlayer();
        ITask* nextAction = player.GetNextAction();
        Process(player, nextAction);
    }
}

void Game::CheckGameOver()
{
    // Check hero of two players is destroyed
    if (GetPlayer1().GetHero()->isDestroyed)
    {
        if (GetPlayer2().GetHero()->isDestroyed)
        {
            GetPlayer1().playState = PlayState::TIED;
            GetPlayer2().playState = PlayState::TIED;
        }
        else
        {
            GetPlayer1().playState = PlayState::LOSING;
        }

        // Set next step
        nextStep = Step::FINAL_WRAPUP;
        GameManager::ProcessNextStep(*this, nextStep);
    }
    else if (GetPlayer2().GetHero()->isDestroyed)
    {
        GetPlayer2().playState = PlayState::LOSING;

        // Set next step
        nextStep = Step::FINAL_WRAPUP;
        GameManager::ProcessNextStep(*this, nextStep);
    }
}
}  // namespace RosettaStone
