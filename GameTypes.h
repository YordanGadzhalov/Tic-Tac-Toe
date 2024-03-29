#pragma once
#include <utility>

enum PlayerID
{
    NONE,
    PLAYER_1,
    PLAYER_2
};

using WinLine = std::pair<int, int>; // startIdx, endIndx in grid

struct WinInfo
{
    PlayerID winner{NONE};
    WinLine line{0, 0};
};
