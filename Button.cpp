#include "Button.h"

Button::Button(){}

Button::~Button(){}

Button::Button(int x, int y, int width, int height, ButtonState state)
{
	this->m_x = x;
	this->m_y = y;
	this->m_width = width;
	this->m_height = height;
    this->m_state = state;
}

bool Button::contains(int mouseX, int mouseY) const
{
	return (mouseX >= m_x && mouseX <= m_width &&
			mouseY >= m_y && mouseY <= m_height);

}

void Button::setState(ButtonState newState)
{
    this->m_state = newState;
}

ButtonState Button::getState()
{
    return this->m_state;
}
