#pragma once
#include "Player.h"
#include <functional>
#include <iostream>
#include <vector>

using GridState = std::vector<PlayerID>;
using GameHistory = std::vector<GridState>;
using Notifier = std::function<void(const GridState& state)>;
constexpr int grid_Size = 9;

class GameLogic
{
public:
    GameLogic(Notifier event);
    ~GameLogic();

    auto GetCurrentPlayer() const -> const Player&;
    auto GetPlayer(PlayerID id) const -> const Player&;
    auto GetWinner() const -> WinInfo;
    auto HasCurrentPlayerTurn() const -> bool;
    void SwitchPlayers();

    auto IsGameOver() -> bool;

    void Undo();
    void Reset();

    void ToggleHistoryMode();
    auto GetHistoryMode() const -> bool;
    void ForwardHistory();
    void BackwardHistory();

    void SetGridPositionState(int index);

private:
    void calculateWinner();
    auto checkForWinner() const -> WinInfo;
    auto isGameDraw() const -> bool;
    auto isNoEmptySquares() const -> bool;
    auto isOneEmptySquareLeft() const -> bool;
    void autoFillLastSquare();
    auto getCurrentGridState() const -> const GridState&;
    void saveGameHistoryStates();

private:
    Player* m_currentPlayer{nullptr};
    Player* m_nextPlayer{nullptr};
    GameHistory m_gameHistory;
    GridState m_currGridState;
    GridState m_prevGridState;
    Notifier on_grid_state_changed;
    WinInfo m_winInfo;
    int m_historyIndex{0};
    bool m_isHistoryMode = false;
};
