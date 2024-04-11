#pragma once
#include "GameHistory.h"
#include "Player.h"
#include <functional>
#include <iostream>

using Notifier = std::function<void(const GridState& state)>;
constexpr int grid_Size = 9;

class GameLogic
{
public:
    GameLogic(Notifier event);
    ~GameLogic();

    void StartGame(const std::string& player1, const std::string& player2);
    auto GetCurrentPlayer() const -> const Player&;
    auto GetPlayer(PlayerID id) const -> const Player&;
    auto GetGameHistory() const -> GameHistory&;
    auto GetWinner() const -> WinInfo;
    auto HasCurrentPlayerTurn() const -> bool;
    void SwitchPlayers();

    auto IsGameOver() -> bool;

    void ToggleModes();
    void ForwardHistory();
    void BackwardHistory();

    void Undo();
    void Reset();

    void SetGridPositionState(int index);

private:
    void calculateWinner();
    auto checkForWinner() const -> WinInfo;
    auto isGameDraw() const -> bool;
    auto isNoEmptySquares() const -> bool;
    auto isOneEmptySquareLeft() const -> bool;
    void autoFillLastSquare();
    auto getCurrentGridState() const -> const GridState&;

private:
    std::shared_ptr<Player> m_currentPlayer{nullptr};
    std::shared_ptr<Player> m_nextPlayer{nullptr};
    std::shared_ptr<GameHistory> m_gameHistory{nullptr};
    GridState m_currGridState;
    GridState m_prevGridState;
    Notifier on_grid_state_changed;
    WinInfo m_winInfo;
};
