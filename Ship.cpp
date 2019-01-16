#include "stdafx.h"
#include "Game.h"



char toLower(char& l)
{
	if (l >= 'A' && l <= 'Z')
	{
		return l = l - 'A' + 'a';
	}
	return l;
}


//Point
void Point::cinPoint()
	{
		do
		{
			cin >> this->row >> this->column;
		} while (!(this->isValid()));
	}
	bool Point::operator <= (Point& other)
	{
		return (row <= other.row  && column <= other.column);
	}
	bool Point::operator >= (Point& other)
	{
		return (row >= other.row  && column >= other.column);
	}
	bool Point::operator > (Point& other)
	{
		return ((row > other.row  && column >= other.column) || (row >= other.row  && column > other.column));
	}
	bool Point::operator < (Point& other)
	{
		return ((row < other.row  && column <= other.column) || (row <= other.row  && column < other.column));
	}
	bool Point::operator == (Point other)
	{
		return (row == other.row  && column == other.column);
	}
	bool Point::isValid()
	{
		toLower(this->column);
		return (this->row >= '0' && (this->row - '0') <= '9' && this->column >= 'a' && this->row <= 'z');
	}
	bool Point::isInRange(const Point& start, const Point& ending)
	{
		return ((start.row == ending.row && start.row == this->row  // ако е вертикално 
			&&	this->column >= start.column && this->column <= ending.column) // и е col м/у тях
			|| (start.column == ending.column && start.column == this->column   // ако е вертикално 
				&& this->row >= start.row && this->row <= ending.row));
	}
	std::ostream &operator << (std::ostream &out, const Point& p)
	{
		out << p.row << p.column;
		return out;
	}

//Position
	void Position::EnterCorrectPosition()
	{
		do
		{
			cout << "Enter start position (width&hight): ";
			cin >> this->beginning.row >> this->beginning.column;
			cout << "Enter end position (width&hight): ";
			cin >> this->ending.row >> this->ending.column;
		} while (!(this->beginning.isValid() && this->ending.isValid()));
	}


//Ship
	Ship::Ship(const String& _name, const size_t& _size, const size_t& _lives, const Point& start, const Point& ending, gameboard& playerBoard)
		:name(_name), size(_size), lives(_lives)
	{
		placeShip(start, ending, playerBoard);
	}
	void Ship::setName(const String& _name)
	{
		this->name = _name;
	}
	void Ship::setSize(const size_t& _size)
	{
		this->size = _size;
	}
	void Ship::setLives(const size_t& _lives)
	{
		if (_lives > 5)
		this->lives = 0; 
		else 
		this->lives = _lives;
	}
	String Ship::getName()const
	{
		return this->name;
	}
	size_t Ship::getSize()const
	{
		return this->size;
	}
	size_t Ship::getLives()const
	{
		return this->lives;
	}
	Point Ship::getStartCoordinate()const
	{
		return this->coordinates.beginning;
	}
	Point Ship::getEndCoordinate()const
	{
		return this->coordinates.ending;
	}
	void Ship::placeShip(const Point& start, const Point& ending, gameboard& playerBoard)
	{
		if (!this->coordinates.beginning.column && !this->coordinates.ending.column)
		{																				// Веднъж сетнати да не може повече ; 
			this->coordinates.beginning = min(start, ending);
			this->coordinates.ending = max(start, ending);

			if (start.column == ending.column)
			{
				for (int i = this->coordinates.beginning.row; i <= this->coordinates.ending.row; i++)
					playerBoard[i - '0'][start.column - 'a'] = shipOnBoard;
			}
			else
			{
				for (int i = this->coordinates.beginning.column; i <= this->coordinates.ending.column; i++)
					playerBoard[start.row - '0'][i - 'a'] = shipOnBoard
					;
			}
		}
	}
	bool Ship::isValid(const Point& start, const Point& ending, gameboard& playerBoard)
	{
		bool flag = true;
		if (start.row == ending.row)
			if (max(start.column, ending.column) - min(start.column, ending.column) + 1 == size)
			{
				for (int i = min(start.column, ending.column); i <= max(start.column, ending.column); i++)
				{
					if (playerBoard[start.row - '0'][i - 'a'] == shipOnBoard)
						flag = false;
				}
				return flag;
			}
		if (start.column == ending.column)
			if (max(start.row, ending.row) - min(start.row, ending.row) + 1 == size)
			{
				for (int i = min(start.row, ending.row); i <= max(start.row, ending.row); i++)
				{
					if (playerBoard[i - '0'][start.column - 'a'] == shipOnBoard)
						flag = false;
				}
				return flag;
			}

		return false;
	}
	bool Ship::isSunk()
	{
		return(this->lives == 0);
	}
	bool Ship::isSuccessfulHit(Point& coordinate,const Vector<Ship*>& other)
	{
		for (size_t i = 0; i < other.size(); i++)
		{
			if (coordinate.isInRange(other[i]->getStartCoordinate(), other[i]->getEndCoordinate()))
				return true;
		}
		return false;
	}

	void Ship::attack(Point& coordinate, Vector<Ship*> other, gameboard& playerBoard, gameboard& enemyBoard, Game& game)
	{
		for (size_t i = 0; i < other.size(); i++)
		{
			if (coordinate.isInRange(other[i]->getStartCoordinate(), other[i]->getEndCoordinate()))
			{
				if (playerBoard == game.myShootBoard)
				{
					if (!game.hitShipCoordinatesComputer.isElement(coordinate))
						game.hitShipCoordinatesComputer.push_back(coordinate);
				}
				else if (playerBoard == game.enemyShootBoard)
					if (!game.hitShipCoordinatesPlayer.isElement(coordinate))
					game.hitShipCoordinatesPlayer.push_back(coordinate);
				playerBoard[coordinate.row - '0'][coordinate.column - 'a'] = hitTheTarget;
				enemyBoard[coordinate.row - '0'][coordinate.column - 'a'] = hitTheTarget;

				other[i]->setLives(other[i]->getLives() - 1);
				/*if (other[i]->isSunk())
					cout << "You sunk a ship" << endl;*/
				return;
			}
		}
		//cout << "You missed " << endl;
		playerBoard[coordinate.row - '0'][coordinate.column - 'a'] = miss;
	}

	Ship* Ship::shipFactory(shipChoice shipp)
	{
		switch(shipp)
		{
		case carrier : 
			return new Carrier(); break; 
		case battleship:
			return new BattleShip(); break; 
		case cruiser :
			return new Cruiser(); break; 
		case submarine : 
			return new Submarine(); break; 
		case destroyer: 
			return new Destroyer(); break;
		default:
			throw "This type does not exist"; break;
		}
	}

	void Ship::write(std::ostream& out)
	{
		out << this->lives << endl; 
		out << this->coordinates.beginning.row << " " << this->coordinates.beginning.column << endl; 
		out << this->coordinates.ending.row << " " << this->coordinates.ending.column << endl;
	}
	void Ship::read(std::istream& in,side whereTo,Game& game1)
	{
		size_t tempLives; 
		Point tempBeg, tempEnd; 
		in >> tempLives;
		this->setLives(tempLives);
		in >> tempBeg.row >> tempBeg.column;
		//this->coordinates.beginning = tempBeg;  
		in >> tempEnd.row >> tempEnd.column; 
		switch(whereTo)
		{
		case Player:this->placeShip(tempBeg, tempEnd, game1.myBoard); break;
		case PC:this->placeShip(tempBeg, tempEnd, game1.enemyBoard); 
		}
		//this->coordinates.ending = tempEnd; 
	}
	
