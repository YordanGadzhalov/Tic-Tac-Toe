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

auto GameLogic::HasCurrentPlayerTurn() const -> bool
{
    return m_currGridState != m_prevGridState;
}

void GameLogic::SwitchPlayers()
{
    std::swap(m_currentPlayer, m_nextPlayer);
    m_prevGridState = m_currGridState;
    autoFillLastSquare();
    saveGameHistoryStates();
}

bool GameLogic::IsGameOver()
{
    if(checkForWinner().winner != NONE || isGameDraw())
    {
        return true;
    }
    return false;
}

bool GameLogic::GetHistoryMode() const
{
    return m_isHistoryMode;
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

    m_gameHistory.clear();
    m_winInfo = {};
    on_grid_state_changed(getCurrentGridState());

    if(GetCurrentPlayer().GetId() == PLAYER_2)
    {
        SwitchPlayers();
    }
}


void GameLogic::ToggleHistoryMode()
{
    m_isHistoryMode = !m_isHistoryMode;
    if(m_isHistoryMode)
    {
        m_historyIndex = m_gameHistory.size() - 1;
        on_grid_state_changed(m_gameHistory.back());
    }
    else
    {
        on_grid_state_changed(getCurrentGridState());
    }
}


void GameLogic::ForwardHistory()
{
    if(m_historyIndex == (m_gameHistory.size() - 1))
    {
        m_historyIndex = 0;
    }
    else
    {
        m_historyIndex++;
    }
    on_grid_state_changed(m_gameHistory.at(m_historyIndex));
}

void GameLogic::BackwardHistory()
{
    if(m_historyIndex == 0)
    {
       m_historyIndex = (m_gameHistory.size() - 1);
    }
    else
    {
        m_historyIndex--;
    }
    on_grid_state_changed(m_gameHistory.at(m_historyIndex));
}

void GameLogic::SetGridPositionState(int index)
{
    m_currGridState.at(index) = m_currentPlayer->GetId();
    calculateWinner();
    if(IsGameOver())
    {
        saveGameHistoryStates();
    }
    on_grid_state_changed(getCurrentGridState());
}

const GridState& GameLogic::getCurrentGridState() const
{
    return m_currGridState;
}

void GameLogic::saveGameHistoryStates()
{
    m_gameHistory.push_back(m_currGridState);
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
                on_grid_state_changed(getCurrentGridState());
                return;
            }
        }
    }
}
