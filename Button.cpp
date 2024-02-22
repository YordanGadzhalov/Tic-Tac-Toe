#include "Button.h"

Button::Button(int x, int y, int width, int height)
{
	this->m_x = x;
	this->m_y = y;
	this->m_width = width;
	this->m_height = height;
}

bool Button::contains(int mouseX, int mouseY)
{
	return (mouseX >= m_x && mouseX <= m_width &&
			mouseY >= m_y && mouseY <= m_height);

}
