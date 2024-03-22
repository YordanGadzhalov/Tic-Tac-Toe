#pragma once
#include "Player.h"
#include <iostream>
#include <vector>

using GridState = std::vector<PlayerID>;

class GameLogic
{
public:
    GameLogic();
    ~GameLogic();

    auto GetCurrentPlayer() const -> const Player&;
    auto GetPlayer(PlayerID id) const -> const Player&;
    auto GetWinner() const -> PlayerID;
    auto HasCurrentPlayerTurn() -> bool;
    void SwitchPlayers();

    auto IsGameOver() const -> bool;

    void Undo();
    void Reset();

    void SetGridPositionState(int index);
    auto GetCurrentGridState() const -> GridState;

private:
    auto checkForWinner(PlayerID id) const -> bool;
    auto isGameDraw() const -> bool;
    auto isNoEmptySquares() const -> bool;
    auto isOneEmptySquareLeft() const -> bool;
    void autoFillLastSquare();

private:
    Player* m_currentPlayer{nullptr};
    Player* m_nextPlayer{nullptr};
    GridState m_currGridState;
    GridState m_prevGridState;
};
