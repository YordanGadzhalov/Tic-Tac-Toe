#include "Square.h"

Square::Square()
{
}

Square::~Square()
{
}

Square::Square(int x, int y, SquareState state) : m_x(x), m_y(y), m_state(state)
{
}

bool Square::IsInside(int mouseX, int mouseY) const
{
    if(mouseX <= m_x + WIDTH && mouseX > m_x && mouseY <= m_y + HEIGHT && mouseY > m_y)
    {
        return true;
    }
    return false;
}

void Square::SetState(SquareState newState)
{
    m_state = newState;
}

SquareState Square::GetState() const
{
    return m_state;
}

void Square::SetIsClicked(bool isClicked)
{
    m_isClicked = isClicked;
}

bool Square::GetIsClicked() const
{
    return m_isClicked;
}

void Square::Clear()
{
    SetState(EMPTY);
    m_isClicked = false;
}

int Square::GetShapePosX() const
{
    return m_x + SHAPE_OFFSET;
}

int Square::GetShapePosY() const
{
    return m_y + SHAPE_OFFSET;
}


int Square::GetSquareCenterY() const
{
    return m_y + (HEIGHT / 2);
}

int Square::GetSquareCenterX() const
{
    return m_x + (WIDTH / 2);
}

