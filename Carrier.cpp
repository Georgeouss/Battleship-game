#include "stdafx.h"
#include "Game.h"
#include "Carrier.h"

Carrier::Carrier()
{
	this->setName("Carrier");
	this->setSize(5);
	this->setLives(5);
}

Carrier::Carrier(const Point& start, const Point& ending, gameboard& playerBoard)
{
	Carrier::Carrier();
	this->placeShip(start, ending, playerBoard);
}
void Carrier::specialAbility(Point& coordinate, side whereToAttack, Game& game)
{

	switch (whereToAttack)
	{
	case Player:
		this->attack(coordinate, game.player.shipSet, game.enemyShootBoard, game.myBoard, game);
		break;
	case PC:
		this->attack(coordinate, game.computer.shipSet, game.myShootBoard, game.enemyBoard, game);
		break;
	default: /*throw "Invalid input"; */ cout << "Invalid" << endl;
		break;
	}
}