#pragma once
#include "GameTypes.h"

using TurnHistory = std::vector<GridState>;

class GameHistory
{
public:
    void SaveGameHistoryStates(const GridState& vec);
    auto GetHistoryMode() const -> bool;
    auto GetCurrentTurn() const -> const GridState&;
    void ToggleMode();
    auto NextTurn() -> const GridState&;
    auto PreviousTurn() -> const GridState&;
    void Reset();

private:
    TurnHistory m_turnsHistory;
    int m_historyIndex{0};
    bool m_isHistoryMode = false;
};
