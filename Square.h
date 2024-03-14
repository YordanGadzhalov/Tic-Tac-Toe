#pragma once
#include <iostream>
#include "Button.h"

enum SquareState { EMPTY, O, X };

class Square {

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

    static const int SHAPE_SIZE = 125;

private:
    int m_x;
    int m_y;
    SquareState m_state;
    bool m_isClicked = false;

    static const int WIDTH = 155;
    static const int HEIGHT = 155;

};
