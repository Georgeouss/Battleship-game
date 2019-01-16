#include "stdafx.h"
#include "Game.h"
#include "Submarine.h"


Submarine::Submarine()
	{
		this->setName("Submarine");
		this->setSize(3);
		this->setLives(3);
	}
Submarine::Submarine(const Point& start, const Point& ending, gameboard& playerBoard)
	{
		Submarine::Submarine();
		this->placeShip(start, ending, playerBoard);
	}

void Submarine::specialAbility(Point& coordinate, side whereTo, Game& game)
{

	if ((rand() % 100) <= 70)
		switch (whereTo)
		{
		case Player:
		{
			if (coordinate.isInRange(game.computer.shipSet[submarine]->getStartCoordinate(), game.computer.shipSet[submarine]->getEndCoordinate()))
			{
				game.myShootBoard[coordinate.row - '0'][coordinate.column - 'a'] = abilityProtect;
				game.enemyBoard[coordinate.row - '0'][coordinate.column - 'a'] = shipOnBoard;
				game.hitShipCoordinatesComputer.pop_back();
				if (!this->isSunk())
				this->setLives(this->getLives() + 1);
			}

		}break;
		case PC:
		{
			if (coordinate.isInRange(game.player.shipSet[submarine]->getStartCoordinate(), game.player.shipSet[submarine]->getEndCoordinate()))
			{
				game.enemyShootBoard[coordinate.row - '0'][coordinate.column - 'a'] = abilityProtect;
				game.myBoard[coordinate.row - '0'][coordinate.column - 'a'] = shipOnBoard;
				game.hitShipCoordinatesPlayer.pop_back();
				if (!this->isSunk())
				this->setLives(this->getLives() + 1);
			}
		}break;
		default: /*throw "Invalid input"; */ cout << "Invalid" << endl;
			break;
		}
}
