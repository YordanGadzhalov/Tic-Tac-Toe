#include "Player.h"

Player::Player()
{
}

Player::Player(PlayerID id, std::string shapeId)
{
    m_id = id;
    m_shapeId = shapeId;
}

Player::~Player()
{
}

PlayerID Player::GetId() const
{
    return m_id;
}

std::string Player::GetShapeId() const
{
    return m_shapeId;
}
