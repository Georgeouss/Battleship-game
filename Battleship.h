#pragma once
#include "stdafx.h"
#include "Ship.h"


//void showNearbyPoints(Point& coord, gameboard& board1, gameboard& board2); // на дъска 1 , от дъска 2 
class BattleShip :public Ship
{
public:
	BattleShip();
	BattleShip(const Point& start, const Point& ending, gameboard& playerBoard);
	void specialAbility(Point& coordinate, side whereTo, Game& game);
private:
	void showNearbyPoints(Point& coord, gameboard& board1, gameboard& board2); // на дъска 1 , от дъска 2 
};
