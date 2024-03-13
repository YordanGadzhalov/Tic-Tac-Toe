#include "Square.h"

Square::Square(){}

Square::~Square(){}

Square::Square(int x, int y, SquareState state = EMPTY)
    : m_x(x)
    , m_y(y)
    , m_state(state)
{}

bool Square::IsInside(int mouseX, int mouseY) {
    if (mouseX <= m_x + SQUARE_WIDTH && mouseX > m_x && mouseY <= m_y + SQUARE_HEIGHT && mouseY > m_y) {
        return true;
    }
    return false;
}

void Square::SetState(SquareState newState)
{
    this->m_state = newState;
}

SquareState Square::GetState()
{
    return this->m_state;
}

void Square::SetIsClicked(bool isClicked)
{
    this->m_isClicked = isClicked;
}

bool Square::GetIsClicked()
{
    return this->m_isClicked;
}

void Square::Clear()
{
    this->SetState(EMPTY);
    this->m_isClicked = false;
}
