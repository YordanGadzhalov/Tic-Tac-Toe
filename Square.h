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
    SquareState m_state;
    bool m_isClicked = false;

public:
    Square();
    ~Square();
    Square(int x, int y, int w, int h, SquareState state);
    bool IsInside(int mouseX, int mouseY);
    void SetState(SquareState newState);
    SquareState GetState();
    void SetIsClicked(bool isClicked);
    bool GetIsClicked();
    void Clear();
};
