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

PlayerID GameLogic::GetWinner() const
{
    if(IsGameOver())
    {
        if(checkForWinner(PLAYER_1))
        {
            return PLAYER_1;
        }
        else if(checkForWinner(PLAYER_2))
        {
            return PLAYER_2;
        }
    }
    return NONE;
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
    if(checkForWinner(PLAYER_1) || checkForWinner(PLAYER_2) || isGameDraw())
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
    on_grid_state_changed();

    if(GetCurrentPlayer().GetId() == PLAYER_2)
    {
        SwitchPlayers();
    }
}

void GameLogic::SetGridPositionState(int index)
{
    m_currGridState.at(index) = m_currentPlayer->GetId();
    on_grid_state_changed();
}

GridState GameLogic::GetCurrentGridState() const
{
    return m_currGridState;
}

bool GameLogic::checkForWinner(PlayerID id) const
{
    if(m_currGridState.at(0) == id && m_currGridState.at(1) == id && m_currGridState.at(2) == id &&
           m_currGridState.at(0) != NONE ||
       m_currGridState.at(3) == id && m_currGridState.at(4) == id && m_currGridState.at(5) == id &&
           m_currGridState.at(3) != NONE ||
       m_currGridState.at(6) == id && m_currGridState.at(7) == id && m_currGridState.at(8) == id &&
           m_currGridState.at(6) != NONE)
    {
        return true;
    }
    if(m_currGridState.at(0) == id && m_currGridState.at(3) == id && m_currGridState.at(6) == id &&
           m_currGridState.at(0) != NONE ||
       m_currGridState.at(1) == id && m_currGridState.at(4) == id && m_currGridState.at(7) == id &&
           m_currGridState.at(1) != NONE ||
       m_currGridState.at(2) == id && m_currGridState.at(5) == id && m_currGridState.at(8) == id &&
           m_currGridState.at(2) != NONE)
    {
        return true;
    }
    if(m_currGridState.at(0) == id && m_currGridState.at(4) == id && m_currGridState.at(8) == id &&
           m_currGridState.at(0) != NONE ||
       m_currGridState.at(2) == id && m_currGridState.at(4) == id && m_currGridState.at(6) == id &&
           m_currGridState.at(2) != NONE)
    {
        return true;
    }
    return false;
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
