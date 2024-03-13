#pragma once
#include <iostream>
#include "Button.h"

enum SquareState { EMPTY, O, X };
const int SHAPE_SIZE = 125;
const int SQUARE_WIDTH = 155;
const int SQUARE_HEIGHT = 155;

class Square {

private:
    int m_x;
    int m_y;
    SquareState m_state;
    bool m_isClicked = false;


public:
    Square();
    ~Square();
    Square(int x, int y, SquareState state);
    bool IsInside(int mouseX, int mouseY);
    void SetState(SquareState newState);
    SquareState GetState();
    void SetIsClicked(bool isClicked);
    bool GetIsClicked();
    void Clear();
};
