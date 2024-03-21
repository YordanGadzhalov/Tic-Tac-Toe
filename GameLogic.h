#pragma once
#include <iostream>
#include "Player.h"
#include <vector>

using GridState = std::vector<PlayerID>;
static const int FILLED_GRID = 8;//

class GameLogic
{
public:
    GameLogic();
    ~GameLogic();

    auto GetCurrentPlayer() const -> const Player&;
    auto GetPlayer(PlayerID id) const -> const Player&;
    auto GetWinner() const -> PlayerID;
    void SwitchPlayers();

    auto IsGameOver() const -> bool;

    void Undo(); //n
    void Reset(); //n

    void SetGridPositionState(int index);
    auto GetCurrentGridState() const -> GridState;

private:
    auto checkForWinner(PlayerID id) const -> bool;
    auto isGameDraw() const -> bool;
    auto isNoEmptySquares() const -> bool;

private:
    Player* m_currentPlayer{nullptr};
    Player* m_nextPlayer{nullptr};
    GridState m_currGridState; // fixed size
    GridState m_prevGridState; // fixed size
};
