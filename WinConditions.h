#pragma once

class WinConditions {
private:
	bool ThreeInArow = false;
	bool ThreeVertically = false;
	bool ThreeDiagonal = false;
	bool NoWinner = false;

public:
	bool isThreeInArow(); // if(grid1.getXorO() == grid2.getXorO() == grid3.getXorO)
	bool isThreeVertically(); 
	bool isThreeDiagonal();
	bool isNoWinner();
};