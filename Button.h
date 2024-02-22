#pragma once
#include <iostream>

class Button {
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;

public:
	Button(int x, int y, int width, int height);
	bool contains(int mouseX, int mouseY);
};