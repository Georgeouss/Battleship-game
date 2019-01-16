#include "stdafx.h"
#include "Game.h"
#include "Battleship.h"



void BattleShip::showNearbyPoints(Point& coord, gameboard& board1, gameboard& board2) // на дъска 1 , от дъска 2 
{
	if (coord.row - 1 >= '0')
	{
		if(board2[coord.row - 1 - '0'][coord.column - 'a'] != unshooted)
		board1[coord.row - 1 - '0'][coord.column - 'a'] = board2[coord.row - 1 - '0'][coord.column - 'a'];
	}
	if (coord.row + 1 <= '9')
	{
		if(board2[coord.row + 1 - '0'][coord.column - 'a'] != unshooted)
		board1[coord.row + 1 - '0'][coord.column - 'a'] = board2[coord.row + 1 - '0'][coord.column - 'a'];
	}
	if (coord.column - 1 >= 'a')
	{
		if(board2[coord.row - '0'][coord.column - 1 - 'a'] != unshooted )
		board1[coord.row - '0'][coord.column - 1 - 'a'] = board2[coord.row - '0'][coord.column - 1 - 'a'];
	}
	if (coord.column + 1 <= 'j')
	{
		if(board2[coord.row - '0'][coord.column + 1 - 'a'] != unshooted)
		board1[coord.row - '0'][coord.column + 1 - 'a'] = board2[coord.row - '0'][coord.column + 1 - 'a'];
	}
	if ((coord.row - 1 >= '0') && (coord.column - 1 >= 'a'))
	{
		if(board2[coord.row - 1 - '0'][coord.column - 1 - 'a'] != unshooted)
		board1[coord.row - 1 - '0'][coord.column - 1 - 'a'] = board2[coord.row - 1 - '0'][coord.column - 1 - 'a'];
	}
	if ((coord.row + 1 <= '9') && (coord.column + 1 <= 'j'))
	{
		if(board2[coord.row - 1 - '0'][coord.column - 1 - 'a'] != unshooted)
		board1[coord.row + 1 - '0'][coord.column + 1 - 'a'] = board2[coord.row + 1 - '0'][coord.column + 1 - 'a'];
	}
	if ((coord.row - 1 >= '0') && (coord.column + 1 <= 'j'))
	{
		if(board2[coord.row - 1 - '0'][coord.column + 1 - 'a'] != unshooted)
		board1[coord.row - 1 - '0'][coord.column + 1 - 'a'] = board2[coord.row - 1 - '0'][coord.column + 1 - 'a'];
	}
	if ((coord.row + 1 <= '9') && (coord.column - 1 >= 'a'))
	{
		if(board2[coord.row + 1 - '0'][coord.column - 1 - 'a'] != unshooted)
		board1[coord.row + 1 - '0'][coord.column - 1 - 'a'] = board2[coord.row + 1 - '0'][coord.column - 1 - 'a'];
	}
}



BattleShip::BattleShip()
	{
		this->setName("Battlesship");
		this->setSize(4);
		this->setLives(4);
	}
BattleShip::BattleShip(const Point& start, const Point& ending, gameboard& playerBoard)
	{
		BattleShip::BattleShip();
		this->placeShip(start, ending, playerBoard);
	}
void BattleShip::specialAbility(Point& coord, side whereTo, Game& game)
{
	
	switch (whereTo)
	{
	case PC: {
		if (this->isSuccessfulHit(coord, game.computer.shipSet))
		showNearbyPoints(coord, game.myShootBoard, game.enemyBoard);
	}
				 break; 

	case Player: {
		if (this->isSuccessfulHit(coord, game.player.shipSet))
		showNearbyPoints(coord, game.enemyShootBoard, game.myBoard);
	}
			 break; 
	default: cout << "Invalid input" << endl; 
	}
}