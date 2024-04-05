#pragma once
#include <utility>
#include <vector>

enum PlayerID
{
    NONE,
    PLAYER_1,
    PLAYER_2
};

using WinLine = std::pair<int, int>;

struct WinInfo
{
    PlayerID winner{NONE};
    WinLine line{0, 0};
};

using GridState = std::vector<PlayerID>;
