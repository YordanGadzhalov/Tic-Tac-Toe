#include "GameHistory.h"


void GameHistory::SaveGameHistoryStates(const GridState& vec)
{
    m_turnsHistory.push_back(vec);
}

auto GameHistory::GetCurrentTurn() const -> const GridState&
{
    return m_turnsHistory.at(m_historyIndex);
}

bool GameHistory::GetHistoryMode() const
{
    return m_isHistoryMode;
}

void GameHistory::ToggleMode()
{
    m_isHistoryMode = !m_isHistoryMode;
    if(m_isHistoryMode)
    {
        m_historyIndex = m_turnsHistory.size() - 1;
    }
}

auto GameHistory::NextTurn() -> const GridState&
{
    if(m_historyIndex == (m_turnsHistory.size() - 1))
    {
        m_historyIndex = 0;
    }
    else
    {
        m_historyIndex++;
    }
    return GetCurrentTurn();
}

auto GameHistory::PreviousTurn() -> const GridState&
{
    if(m_historyIndex == 0)
    {
        m_historyIndex = (m_turnsHistory.size() - 1);
    }
    else
    {
        m_historyIndex--;
    }

    return GetCurrentTurn();
}

void GameHistory::Reset()
{
    m_turnsHistory.clear();
}
