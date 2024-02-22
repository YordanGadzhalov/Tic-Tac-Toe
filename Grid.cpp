#include "Grid.h"

Grid::Grid(){}

Grid::~Grid(){}

Grid::Grid(int x, int y, int w, int h, GridState state) : gridX1(x), gridX2(y), gridY1(w), gridY2(h), state(state) {}

bool Grid::isInside(int mouseX, int mouseY) {
    // Check if the mouse click is inside this grid
    if (mouseX >= gridX1 && mouseX <= gridX2 && mouseY >= gridY1 && mouseY <= gridY2) {
        return true;
    }
    return false;
}

void Grid::setXorO(bool isIt)
{
    this->isXorO = isIt;
}

bool Grid::getXorO()
{
    return this->isXorO;
}

void Grid::setState(GridState newState)
{
    this->state = newState;
}

GridState Grid::getState()
{
    return this->state;
}

