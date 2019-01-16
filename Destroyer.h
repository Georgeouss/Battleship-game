#pragma once
#include "stdafx.h"
#include "Ship.h"

class Destroyer : public Ship
{
public:
	Destroyer();
	Destroyer(const Point& start, const Point& ending, gameboard& playerBoard);
	void specialAbility(Point& coordinate, side whereTo, Game& game);
};