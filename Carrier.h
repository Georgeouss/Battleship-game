#pragma once
#include "stdafx.h"
#include "Ship.h"

class Carrier : public Ship
{
public:
	Carrier();
	Carrier(const Point& start, const Point& ending, gameboard& playerBoard);
	void specialAbility(Point& coordinate, side whereToAttack, Game& game);
};