#pragma once

#include "GameTypes.h"
#include <string>

class Player
{
public:
    Player();
    Player(PlayerID id, std::string shapeId);
    ~Player();

    auto GetId() const -> PlayerID;
    auto GetShapeId() const -> std::string;

private:
    PlayerID m_id;
    std::string m_shapeId;
};
