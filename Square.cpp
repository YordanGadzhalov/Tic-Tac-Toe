#include "Square.h"

Square::Square(){}

Square::~Square(){}

Square::Square(int x, int y, int w, int h, SquareState state) : m_x(x), m_w(y), m_y(w), m_h(h), state(state) {}

bool Square::isInside(int mouseX, int mouseY) {
    // Check if the mouse click is inside this grid
    if (mouseX >= m_x && mouseX <= m_w && mouseY >= m_y && mouseY <= m_h) {
        return true;
    }
    return false;
}

void Square::setState(SquareState newState)
{
    this->state = newState;
}

SquareState Square::getState()
{
    return this->state;
}

void Square::setIsClicked(bool isClicked)
{
    this->isClicked = isClicked;
}

bool Square::getIsClicked()
{
    return this->isClicked;
}

void Square::clear()
{
    this->setState(EMPTY);
    this->isClicked = false;
}
