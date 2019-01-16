#pragma once
#include "stdafx.h"
#include "Ship.h"

size_t findShipIndex(Point& point, Vector<Ship*>& ships);

class Cruiser :public Ship
{
public:
	Cruiser();
	Cruiser(const Point& start, const Point& ending, gameboard& playerBoard);
	void specialAbility(Point& coordinate, side whereTo, Game& game);
};
