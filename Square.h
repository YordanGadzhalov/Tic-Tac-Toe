#pragma once
#include "Button.h"
#include <string>

class Square
{
public:
    Square();
    ~Square();
    Square(int x, int y);
    bool IsInside(int mouseX, int mouseY) const;
    void SetSymbol(const std::string& symbol = "");
    std::string GetSymbol() const;
    void SetIsClicked(bool isClicked);
    bool GetIsClicked() const;
    void Clear();
    int GetShapePosX() const;
    int GetShapePosY() const;
    int GetSquareCenterX() const;
    int GetSquareCenterY() const;
    static const int SHAPE_SIZE = 125;


private:
    int m_x;
    int m_y;
    std::string m_symbol;
    bool m_isClicked = false;
    static const int WIDTH = 155;
    static const int HEIGHT = 155;
    static const int SHAPE_OFFSET = 15;
};
