#pragma once
#include "stdafx.h"
#include "Ship.h"

class Submarine : public Ship
{
public:
	Submarine();
	Submarine(const Point& start, const Point& ending, gameboard& playerBoard);
	void specialAbility(Point& coordinate, side whereTo, Game& game);
};
