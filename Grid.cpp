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

void Grid::setState(GridState newState)
{
    this->state = newState;
}

GridState Grid::getState()
{
    return this->state;
}

void Grid::setIsClicked(bool isClicked)
{
    this->isClicked = isClicked;
}

bool Grid::getIsClicked()
{
    return this->isClicked;
}

void Grid::clear()
{
    this->setState(EMPTY);
    this->isClicked = false;
}

