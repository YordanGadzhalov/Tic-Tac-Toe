#include "Square.h"

Square::Square(){}

Square::~Square(){}

Square::Square(int x, int y, int w, int h, SquareState state) : m_x(x), m_w(y), m_y(w), m_h(h), m_state(state) {}

bool Square::IsInside(int mouseX, int mouseY) {
    // Check if the mouse click is inside this grid
    if (mouseX >= m_x && mouseX <= m_w && mouseY >= m_y && mouseY <= m_h) {
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
