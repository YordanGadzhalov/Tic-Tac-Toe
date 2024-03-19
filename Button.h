#pragma once

enum ButtonState
{
    ACTIVE,
    CLICKED,
    INACTIVE
};

class Button
{
public:
    Button();
    ~Button();
    Button(int x, int y, int width, int height, ButtonState state);
    bool contains(int mouseX, int mouseY) const;
    void setState(ButtonState newState);
    ButtonState getState() const;


private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    ButtonState m_state;


};
