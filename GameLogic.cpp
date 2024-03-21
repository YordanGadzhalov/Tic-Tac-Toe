#include "GameLogic.h"

GameLogic::GameLogic()
{
    m_currentPlayer = new Player(PlayerID::PLAYER_1, "circle2");
    m_nextPlayer = new Player(PlayerID::PLAYER_2, "imageX2");
    m_currGridState.resize(9, PlayerID::NONE);
}

GameLogic::~GameLogic()
{
    delete m_currentPlayer;
    delete m_nextPlayer;
}

const Player& GameLogic::GetCurrentPlayer() const
{
    return *m_currentPlayer;
}

const Player& GameLogic::GetPlayer(PlayerID id) const
{
    if(id == PLAYER_1)
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

void GameLogic::SwitchPlayers()
{
    std::swap(m_currentPlayer, m_nextPlayer);
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

}

void GameLogic::Reset()
{
    for(int i = 0; i < GetCurrentGridState().size(); i++)
    {
        m_currGridState.at(i) = NONE;
    }
    if(GetCurrentPlayer().GetId() == PLAYER_2)
    {
        SwitchPlayers();
    }
}

void GameLogic::SetGridPositionState(int index)
{
    m_currGridState.at(index) = m_currentPlayer->GetId();
    m_prevGridState = m_currGridState;
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
    int counter = 0;
    for(int i = 0; i < m_currGridState.size(); i++)
    {
        if(m_currGridState.at(i) != NONE)
        {
            counter++;
            if(counter == m_currGridState.size())
            {
                return true;
            }
        }
    }
    return false;
}

// bool GameLogic::isNoEmptySquares() const
// {

// }
