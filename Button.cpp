#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

Button::Button(int x, int y, int width, int height, ButtonState state)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_state = state;
}

bool Button::contains(int mouseX, int mouseY) const
{
    return (mouseX >= m_x && mouseX <= m_width && mouseY >= m_y && mouseY <= m_height);
}

void Button::setState(ButtonState newState)
{
    m_state = newState;
}

ButtonState Button::getState() const
{
    return m_state;
}
