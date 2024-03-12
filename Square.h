#pragma once
#include <iostream>
#include "Button.h"

enum SquareState { EMPTY, O, X };
const int SIZE = 125;

class Square {

private:
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    SquareState state;
    bool isClicked = false;

public:
    Square();
    ~Square();
    Square(int x, int y, int w, int h, SquareState state);
    bool isInside(int mouseX, int mouseY);
    void setState(SquareState newState);
    SquareState getState();
    void setIsClicked(bool isClicked);
    bool getIsClicked();
    void clear();
};
