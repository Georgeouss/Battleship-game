#include "stdafx.h"
#include "Game.h"
#include "ComputerPlayerShipSet.h"

//playerShipSet
ShipSet::ShipSet()
{
	if (shipsSetSize != 5)
		throw "You have to fix the set";
	this->shipSet.push_back(new Carrier);
	this->shipSet.push_back(new BattleShip);
	this->shipSet.push_back(new Cruiser);
	this->shipSet.push_back(new Submarine);
	this->shipSet.push_back(new Destroyer);
	//this->fillChoices();

}


//void ShipSet::saveAllShips(String fileName)
//{
//	std::ofstream out (fileName + String(".txt"));
//	if (out.is_open())
//	{
//		for (size_t i = 0; i < shipsSetSize; i++)
//		{
//			out << i << endl;
//			this->shipSet[i]->write(out);
//			out << endl;
//		}
//		out.close();
//	}
//		else
//			cout << "Unable ot open the file" << endl;
//}
bool ShipSet::defeat()
{
	for (size_t i = 0; i < shipsSetSize; i++)
	{
		if (!this->shipSet[i]->isSunk())
			return false;
	}
	return true; 
}
void ShipSet::placeAllShips(gameboard& playerBoard)
{
	Position start;
	for (size_t i = 0; i < this->shipSet.size(); i++)
	{
		cout << "Enter " << this->shipSet[i]->getName() << "(size " << this->shipSet[i]->getSize() << "):" << endl;
		do
		{
			start.EnterCorrectPosition();
		} while (!(this->shipSet[i]->isValid(start.beginning, start.ending, playerBoard)));
		this->shipSet[i]->placeShip(start.beginning, start.ending, playerBoard);
		cout << "You've entered : " << this->shipSet[i]->getStartCoordinate() << " " << this->shipSet[i]->getEndCoordinate() << endl;
	}
}
void ShipSet::setIndexWithoutRepeatingInChoices(const int choice)
{
	this->choices.push_back(choice);
	if (this->choices.size() == shipsSetSize)   // Ако са използвани всички възможности
		this->choices.Empty();
}

//Computer
void ComputerShipset::setIndexWithoutRepeatingInChoices(const int choice)
{
	this->choices.pop(choice);
	if (this->choices.isEmpty())   // Ако са използвани всички възможности
		this->fillChoices();
}

void ComputerShipset::fillChoices()
{
	for (int i = 0; i < shipsSetSize; i++)
	{
		this->choices.push_back(i);
		/*if (this->shipSet[i]->isSunk())
			this->choices.pop(i); */
	}
}

void ComputerShipset::placeAllShips(gameboard& playerBoard)
	{
		Position start;
		//cout << "Loading...";
		for (size_t i = 0; i < this->shipSet.size(); i++)
		{
			do
			{
				//srand(time(NULL));
				start.beginning.row = rand() % 10 + '0';
				start.beginning.column = rand() % 10 + 'a';

				int direction = rand() % 2 + 0;
				switch (direction)
				{
				case Vertically: {start.ending.column = start.beginning.column;
					if ((this->shipSet[i]->getSize() + start.beginning.row - '0') < rows)
						start.ending.row = char(this->shipSet[i]->getSize() + start.beginning.row - 1); }break;
				case Horizontally: {start.ending.row = start.beginning.row;
					if ((this->shipSet[i]->getSize() + start.beginning.column - 'a') < columns)
						start.ending.column = char(this->shipSet[i]->getSize() + start.beginning.column - 1); }break;
				}
			} while (!(this->shipSet[i]->isValid(start.beginning, start.ending, playerBoard)));
			this->shipSet[i]->placeShip(start.beginning, start.ending, playerBoard);
		}
 }


bool isCorrectChoice(const int& choice, Vector<int> choices)      
{                                          // Възможните кораби   Не е сред използваните 
	return (choice >= 0 && choice < shipsSetSize && !choices.isElement(choice)); 
}


void switchChoice(const int choice ,Point& coordinate,Point& enemyCoord ,const ShipSet* set,side whereTo, Game& game1 )
//void switchChoice(const int choice, Point& coordinate, const ShipSet* set, side whereTo, Game& game1)
{ 
	switch (choice)
	{
	case carrier:
	{
		Point temp;
		if (whereTo == PC)
		{
			cout << "2nd attack : ";
			temp.cinPoint();
		}
		else if (whereTo == Player)
		{
			temp.row = rand() % 10 + '0';
			temp.column = rand() % 10 + 'a';
		}
		set->shipSet[carrier]->specialAbility(temp, whereTo, game1);
	}
	break;
	case battleship: set->shipSet[battleship]->specialAbility(coordinate, whereTo, game1);
		break;
	case cruiser: set->shipSet[cruiser]->specialAbility(enemyCoord, whereTo, game1);
		break;
	case submarine: set->shipSet[submarine]->specialAbility(enemyCoord, whereTo, game1);
		break;
	case destroyer: set->shipSet[destroyer]->specialAbility(enemyCoord, whereTo, game1); 
		break; 
	default: cout << "No case" << endl; break;
	}
}

void ComputerShipset::attackCoordinateUpdate(char& column, char &row,ShipSet player)
{
	if (!(this->shipSet[0]->isSuccessfulHit(Point(row, column), player.shipSet)) || this->pcStrategy.lastDirection== this->pcStrategy.None)                  
	{																			//Ако не уцели и няма посока 
		row = rand() % 10 + '0';
		column = rand() % 10 + 'a';
		this->findeCorrectDirection(Point(row, column), player);
		this->pcStrategy.getMove(column, row);
		
	}
	else {
		
			//this->findeCorrectDirection(Point(row, column), player);
		//this->pcStrategy.successful = true;
		/*if (this->pcStrategy.Up == this->pcStrategy.lastDirection || this->pcStrategy.Down == this->pcStrategy.lastDirection)
		{
			this->pcStrategy.left = this->pcStrategy.NotLikely;
			this->pcStrategy.right = this->pcStrategy.NotLikely;
		}
		else
		{
			this->pcStrategy.up = this->pcStrategy.NotLikely;
			this->pcStrategy.down = this->pcStrategy.NotLikely;
		}*/
	//	this->findeCorrectDirection(Point(row, column), player);
		this->pcStrategy.getMove(column, row);
	}
}

void ComputerShipset::findeCorrectDirection(Point coord,const ShipSet& player)
{

	if (coord.row != '9' && this->shipSet[0]->isSuccessfulHit(Point(coord.row + 1, coord.column), player.shipSet))
		this->pcStrategy.lastDirection = this->pcStrategy.Down;
	else if (coord.column != 'j' && this->shipSet[0]->isSuccessfulHit(Point(coord.row, coord.column + 1), player.shipSet))
		this->pcStrategy.lastDirection = this->pcStrategy.Right;
	else if (coord.row != '0' && this->shipSet[0]->isSuccessfulHit(Point(coord.row - 1, coord.column), player.shipSet))
		this->pcStrategy.lastDirection = this->pcStrategy.Up;
	else if (coord.column != 'a' && this->shipSet[0]->isSuccessfulHit(Point(coord.row, coord.column - 1), player.shipSet))
		this->pcStrategy.lastDirection = this->pcStrategy.Left;
	else
		this->pcStrategy.lastDirection = this->pcStrategy.None; 

}

Point ComputerShipset::hardMode(Game& game1)
{
	Point temp;
	do
	{
		temp.row = rand() % 10 + '0';
		temp.column = rand() % 10 + 'a';
	} while (!(this->shipSet[0]->isSuccessfulHit(temp, game1.player.shipSet) && !game1.hitShipCoordinatesPlayer.isElement(temp)));


	return temp;
}