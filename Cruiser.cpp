#include "stdafx.h"
#include "Game.h"
#include "Cruiser.h"


size_t findShipIndex(Point& point, Vector<Ship*>& ships)
{
	for (size_t i = 0; i < ships.size(); i++)
	{
		if (point.isInRange(ships[i]->getStartCoordinate(), ships[i]->getEndCoordinate()))
		{
			return i;
		}
	}
	return -1;
}


Cruiser::Cruiser()
	{
		this->setName("Cruiser");
		this->setSize(3);
		this->setLives(3);
	}
Cruiser::Cruiser(const Point& start, const Point& ending, gameboard& playerBoard)
	{
		Cruiser::Cruiser();
		this->placeShip(start, ending, playerBoard);
	}

void Cruiser::specialAbility(Point& coordinate, side whereTo, Game& game)
{

	srand(time(NULL)); //initialize the random seed
	size_t shipIndex = 0;

	switch (whereTo)
	{
	case Player:
	{
		if (!(coordinate.isInRange(game.computer.shipSet[destroyer]->getStartCoordinate(), game.computer.shipSet[destroyer]->getEndCoordinate())
			|| this->isSunk()))
		{
			if (!game.hitShipCoordinatesComputer.size())
				return;
		
				size_t index = (rand() % game.hitShipCoordinatesComputer.size()); //generates a random number between 0 and the size ; 
				shipIndex = findShipIndex(game.hitShipCoordinatesComputer[index], game.computer.shipSet);
				if (!game.computer.shipSet[shipIndex]->isSunk())
				{
					game.computer.shipSet[shipIndex]->setLives(game.computer.shipSet[shipIndex]->getLives() + 1);
					game.myShootBoard[game.hitShipCoordinatesComputer[index].row - '0'][game.hitShipCoordinatesComputer[index].column - 'a'] = unshooted;
					game.enemyBoard[game.hitShipCoordinatesComputer[index].row - '0'][game.hitShipCoordinatesComputer[index].column - 'a'] = shipOnBoard;
					game.hitShipCoordinatesComputer.pop(index);
				}
		}
	}break;
	case PC:
	{
		

		if (!(coordinate.isInRange(game.player.shipSet[destroyer]->getStartCoordinate(), game.player.shipSet[destroyer]->getEndCoordinate())
			|| this->isSunk()))
		{
			if (!game.hitShipCoordinatesPlayer.size())
				return;
				int index = rand() % (game.hitShipCoordinatesPlayer.size()); //generates a random number between 0 and the size ; 
				shipIndex = findShipIndex(game.hitShipCoordinatesPlayer[index], game.player.shipSet);

				if (!game.player.shipSet[shipIndex]->isSunk())
				{
					game.player.shipSet[shipIndex]->setLives(game.player.shipSet[shipIndex]->getLives() + 1);
					game.enemyShootBoard[game.hitShipCoordinatesPlayer[index].row - '0'][game.hitShipCoordinatesPlayer[index].column - 'a'] = unshooted;
					game.myBoard[game.hitShipCoordinatesPlayer[index].row - '0'][game.hitShipCoordinatesPlayer[index].column - 'a'] = shipOnBoard;
					game.hitShipCoordinatesPlayer.pop(index);
				}
		}
	}break;
	default: /*throw "Invalid input"; */ cout << "Invalid" << endl;
		break;
	}
}