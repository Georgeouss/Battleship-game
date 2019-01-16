#pragma once
#include "stdafx.h"
#include "Ship.h"


class ComputerStrategy
{
public:
	enum dir { None, Up, Down, Left, Right };
	ComputerStrategy() : lastDirection(None) {};
	bool getMove(char &c, char &r);

	//Point hardMod();
	//void set(char c, char r);
	dir lastDirection;
	void reset();
};
