#include "GameLogic.h"

GameLogic::GameLogic(Notifier event)
{
    m_currentPlayer = new Player(PlayerID::PLAYER_1, "circle2");
    m_nextPlayer = new Player(PlayerID::PLAYER_2, "Ximage2");
    m_currGridState.resize(grid_Size, PlayerID::NONE);
    m_prevGridState.resize(grid_Size, PlayerID::NONE);
    on_grid_state_changed = event;
}

GameLogic::~GameLogic()
{
    delete m_currentPlayer;
    m_currentPlayer = nullptr;
    delete m_nextPlayer;
    m_nextPlayer = nullptr;
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

WinInfo GameLogic::GetWinner() const
{
    return m_winInfo;
}

auto GameLogic::HasCurrentPlayerTurn() -> bool
{
    return m_currGridState != m_prevGridState;
}

void GameLogic::SwitchPlayers()
{
    std::swap(m_currentPlayer, m_nextPlayer);
    m_prevGridState = m_currGridState;
    autoFillLastSquare();
}

bool GameLogic::IsGameOver() const
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
    on_grid_state_changed();
}

void GameLogic::Reset()
{
    for(int i = 0; i < GetCurrentGridState().size(); i++)
    {
        m_currGridState.at(i) = NONE;
        m_prevGridState.at(i) = NONE;
    }

    m_winInfo = {};
    on_grid_state_changed();

    if(GetCurrentPlayer().GetId() == PLAYER_2)
    {
        SwitchPlayers();
    }
}

void GameLogic::SetGridPositionState(int index)
{
    m_currGridState.at(index) = m_currentPlayer->GetId();
    calculateWinner();
    on_grid_state_changed();
}

GridState GameLogic::GetCurrentGridState() const
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
    for(int i = 0; i < m_currGridState.size(); i++)
    {
        if(m_currGridState.at(i) == NONE)
        {
            return false;
        }
    }
    return true;
}

bool GameLogic::isOneEmptySquareLeft() const
{
    int square_counter = 0;
    for(const auto& square : m_currGridState)
    {
        if(square != NONE)
        {
            square_counter++;
        }
        if(square_counter == m_currGridState.size() - 1)
        {
            return true;
        }
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
                on_grid_state_changed();
                return;
            }
        }
    }
}
