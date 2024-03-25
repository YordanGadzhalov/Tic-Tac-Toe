#include "Square.h"

Square::Square()
{
}

Square::~Square()
{
}

Square::Square(int x, int y) : m_x(x), m_y(y)
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

void Square::SetSymbol(const std::string& symbol)
{
    m_symbol = symbol;
}

std::string Square::GetSymbol() const
{
    return m_symbol;
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

