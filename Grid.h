#pragma once
#include <iostream>
#include "Button.h"

class Grid {
private:
    int gridX1;
    int gridY1;
    int gridX2;
    int gridY2;
    bool isXorO = false; 

public:
    Grid();
    ~Grid();
    Grid(int x, int y, int w, int h);
    bool isInside(int mouseX, int mouseY);
    void setXorO(bool isIt);
    bool getXorO();
};