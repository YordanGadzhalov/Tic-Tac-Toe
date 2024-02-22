#pragma once
#include <iostream>
#include "Button.h"

enum GridState { EMPTY, O, X };

class Grid {

private:
    int gridX1;
    int gridY1;
    int gridX2;
    int gridY2;
    GridState state;

public:
    Grid();
    ~Grid();
    Grid(int x, int y, int w, int h, GridState state); // each grid has a default state EMPTY
    bool isInside(int mouseX, int mouseY);
    void setState(GridState newState);
    GridState getState();
};