#include "stdafx.h"
#include "Game.h"
#include "Destroyer.h"


Destroyer::Destroyer()
	{
		this->setName("Destroyer");
		this->setSize(2);
		this->setLives(2);
	}
Destroyer::Destroyer(const Point& start, const Point& ending, gameboard& playerBoard)
	{
		Destroyer::Destroyer();
		this->placeShip(start, ending, playerBoard);
	}
void Destroyer::specialAbility(Point& coordinate, side whereTo, Game& game)
{
	/*static int once = 1;
	if (once == 1)
	{*/
		switch (whereTo)
		{
		case Player:
		{
			if (coordinate.isInRange(game.computer.shipSet[destroyer]->getStartCoordinate(), game.computer.shipSet[destroyer]->getEndCoordinate()))
			{
				game.myShootBoard[coordinate.row - '0'][coordinate.column - 'a'] = abilityProtect;
				game.enemyBoard[coordinate.row - '0'][coordinate.column - 'a'] = shipOnBoard; 
				if (!this->isSunk())
				this->setLives(this->getLives() + 1);
				game.hitShipCoordinatesComputer.pop_back();
				//once--;
			}
		}break;
		case PC:
		{
			if (coordinate.isInRange(game.player.shipSet[destroyer]->getStartCoordinate(), game.player.shipSet[destroyer]->getEndCoordinate()))
			{
				game.enemyShootBoard[coordinate.row - '0'][coordinate.column - 'a'] = abilityProtect; 
				game.myBoard[coordinate.row - '0'][coordinate.column - 'a'] = shipOnBoard;
				if(!this->isSunk())
				this->setLives(this->getLives() + 1);
				game.hitShipCoordinatesPlayer.pop_back();
				//once--;
			}
		}break;
		default: /*throw "Invalid input"; */ cout << "Invalid" << endl;
			break;
		}
	//}
}
