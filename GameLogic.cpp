#include "GameLogic.h"
#include <algorithm>

GameLogic::GameLogic(Notifier event)
{
    m_currGridState.resize(grid_Size, PlayerID::NONE);
    m_prevGridState.resize(grid_Size, PlayerID::NONE);
    m_gameHistory = std::make_shared<GameHistory>();
    on_grid_state_changed = event;
}

GameLogic::~GameLogic()
{
}

auto GameLogic::GetCurrentPlayer() const -> const Player&
{
    return *m_currentPlayer;
}

auto GameLogic::GetPlayer(PlayerID id) const -> const Player&
{
    if(id == m_currentPlayer->GetId())
    {
        return *m_currentPlayer;
    }
    else
    {
        return *m_nextPlayer;
    }
}

GameHistory& GameLogic::GetGameHistory() const
{
    return *m_gameHistory;
}

WinInfo GameLogic::GetWinner() const
{
    return m_winInfo;
}

auto GameLogic::HasCurrentPlayerTurn() const -> bool
{
    return m_currGridState != m_prevGridState;
}

void GameLogic::SwitchPlayers()
{
    std::swap(m_currentPlayer, m_nextPlayer);
    m_prevGridState = m_currGridState;
    m_gameHistory->SaveGameHistoryStates(m_currGridState);
    autoFillLastSquare();
}

bool GameLogic::IsGameOver()
{
    if(checkForWinner().winner != NONE || isGameDraw())
    {
        return true;
    }
    return false;
}

void GameLogic::Undo()
{
    m_currGridState = m_prevGridState;
    on_grid_state_changed(getCurrentGridState());
}

void GameLogic::Reset()
{
    for(int i = 0; i < getCurrentGridState().size(); i++)
    {
        m_currGridState.at(i) = NONE;
        m_prevGridState.at(i) = NONE;
    }

    m_gameHistory->Reset();
    m_winInfo = {};
    on_grid_state_changed(getCurrentGridState());

    if(GetCurrentPlayer().GetId() == PLAYER_2)
    {
        SwitchPlayers();
    }
}

void GameLogic::StartGame(const std::string& player1, const std::string& player2)
{
    m_currentPlayer = std::make_shared<Player>(PlayerID::PLAYER_1, player1);
    m_nextPlayer = std::make_shared<Player>(PlayerID::PLAYER_2, player2);
}

void GameLogic::SetGridPositionState(int index)
{
    m_currGridState.at(index) = m_currentPlayer->GetId();
    on_grid_state_changed(getCurrentGridState());
    if(IsGameOver())
    {
        m_gameHistory->SaveGameHistoryStates(m_currGridState);
    }
    calculateWinner();
}

const GridState& GameLogic::getCurrentGridState() const
{
    return m_currGridState;
}

void GameLogic::calculateWinner()
{
    m_winInfo = checkForWinner();
}

WinInfo GameLogic::checkForWinner() const
{
    WinInfo result;
    if(m_currGridState.at(0) == m_currGridState.at(1) && m_currGridState.at(1) == m_currGridState.at(2) &&
       m_currGridState.at(0) != NONE)
    {
        result = {m_currGridState.at(0), {0, 2}};
        return result;
    }
    if(m_currGridState.at(3) == m_currGridState.at(4) && m_currGridState.at(4) == m_currGridState.at(5) &&
       m_currGridState.at(3) != NONE)
    {
        result = {m_currGridState.at(3), {3, 5}};
        return result;
    }
    if(m_currGridState.at(6) == m_currGridState.at(7) && m_currGridState.at(7) == m_currGridState.at(8) &&
       m_currGridState.at(6) != NONE)
    {
        result = {m_currGridState.at(6), {6, 8}};
        return result;
    }
    if(m_currGridState.at(0) == m_currGridState.at(3) && m_currGridState.at(3) == m_currGridState.at(6) &&
       m_currGridState.at(0) != NONE)
    {
        result = {m_currGridState.at(0), {0, 6}};
        return result;
    }
    if(m_currGridState.at(1) == m_currGridState.at(4) && m_currGridState.at(4) == m_currGridState.at(7) &&
       m_currGridState.at(1) != NONE)
    {
        result = {m_currGridState.at(1), {1, 7}};
        return result;
    }
    if(m_currGridState.at(2) == m_currGridState.at(5) && m_currGridState.at(5) == m_currGridState.at(8) &&
       m_currGridState.at(2) != NONE)
    {
        result = {m_currGridState.at(2), {2, 8}};
        return result;
    }
    if(m_currGridState.at(0) == m_currGridState.at(4) && m_currGridState.at(4) == m_currGridState.at(8) &&
       m_currGridState.at(0) != NONE)
    {
        result = {m_currGridState.at(0), {0, 8}};
        return result;
    }
    if(m_currGridState.at(2) == m_currGridState.at(4) && m_currGridState.at(4) == m_currGridState.at(6) &&
       m_currGridState.at(2) != NONE)
    {
        result = {m_currGridState.at(2), {2, 6}};
        return result;
    }
    return result;
}

bool GameLogic::isGameDraw() const
{
    auto it = std::find(m_currGridState.begin(), m_currGridState.end(), NONE);
    if(it != m_currGridState.end())
    {
        return false;
    }

    return true;
}

bool GameLogic::isOneEmptySquareLeft() const
{
    auto count = std::count(m_currGridState.begin(), m_currGridState.end(), NONE);
    if(count == 1)
    {
        return true;
    }
    return false;
}

void GameLogic::autoFillLastSquare()
{
    if(isOneEmptySquareLeft())
    {
        for(int i = 0; i < m_currGridState.size(); i++)
        {
            if(m_currGridState.at(i) == NONE)
            {
                m_currGridState.at(i) = m_currentPlayer->GetId();
                on_grid_state_changed(getCurrentGridState());
                m_gameHistory->SaveGameHistoryStates(m_currGridState);
                calculateWinner();
                return;
            }
        }
    }
}

void GameLogic::ToggleModes()
{
    m_gameHistory->ToggleMode();
    if(m_gameHistory->GetHistoryMode() == true)
    {
        on_grid_state_changed(m_gameHistory->GetCurrentTurn());
    }
    else
    {
        on_grid_state_changed(getCurrentGridState());
    }
}

void GameLogic::ForwardHistory()
{
    on_grid_state_changed(m_gameHistory->NextTurn());
}

void GameLogic::BackwardHistory()
{
    on_grid_state_changed(m_gameHistory->PreviousTurn());
}
