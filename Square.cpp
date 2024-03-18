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

bool Square::IsInside(int mouseX, int mouseY)
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

SquareState Square::GetState()
{
    return m_state;
}

void Square::SetIsClicked(bool isClicked)
{
    m_isClicked = isClicked;
}

bool Square::GetIsClicked()
{
    return m_isClicked;
}

void Square::Clear()
{
    SetState(EMPTY);
    m_isClicked = false;
}

int Square::GetSquareX()
{
    return m_x;
}

int Square::GetSquareY()
{
    return m_y;
}
