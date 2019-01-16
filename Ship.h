#pragma once
#include "stdafx.h"
#include <iostream>
#include "String.h"
#include "Vector.h"
#include <stdlib.h>		/* srand, rand */
#include <time.h>  

const size_t rows = 10;
const size_t columns = 10;
using gameboard = char[rows][columns];

const size_t shipsSetSize = 5;
const char boardTop[rows + 1] = "ABCDEFGHIJ";                   // <- +1  ÇÀ /0 ; 
const String boardColumn[columns + 1] = { " 0|"," 1|"," 2|"," 3|"," 4|"," 5|"," 6|"," 7|"," 8|"," 9|" };

const char abilityProtect = '@';
const char shipOnBoard = '1';
const char hitTheTarget = 'X';
const char miss = 'O';
const char unshooted = '.';

enum side { Player, PC };
enum shipChoice { carrier, battleship, cruiser, submarine, destroyer };
enum direction { Vertically, Horizontally};

struct Game;

template <typename T>
T max(T first, T snd)
{
	if (first > snd)
		return first;
	return snd;
}
template <typename T>
T min(T first, T snd)
{
	if (first < snd)
		return first;
	return snd;
}

char toLower(char& l);

struct Point
{
	char row;
	char column;
	Point() : row(0), column(0) {};
	Point(int _row, char _column) : row(_row), column(_column) {};
	void cinPoint();
	bool operator <= (Point& other);
	bool operator >= (Point& other);
	bool operator > (Point& other);
	bool operator < (Point& other);
	bool operator == (Point other);
	bool isValid();
	bool isInRange(const Point& start, const Point& ending);
	friend std::ostream &operator << (std::ostream &out, const Point& p);

};

struct Position
{
	Point beginning;
	Point ending;
	Position() {}; //: beginning('0', 'a'), ending('0', 'a') {};
	Position(const Point& _start, const Point& _ending) : beginning(_start), ending(_ending) {};
	void EnterCorrectPosition();
};

class Ship
{
private:
	String name;
	size_t size;
	size_t lives;
	Position coordinates;
protected:
	void setName(const String& _name);
	void setSize(const size_t& _size);
public:
	Ship() {};
	Ship(const String& _name, const size_t& _size, const size_t& _lives, const Point& start, const Point& ending, gameboard& playerBoard);
	void setLives(const size_t& _lives);
	String getName()const;
	size_t getSize()const;
	size_t getLives()const;
	Point getStartCoordinate()const;
	Point getEndCoordinate()const;
	void placeShip(const Point& start, const Point& ending, gameboard& playerBoard);
	bool isValid(const Point& start, const Point& ending, gameboard& playerBoard);
	bool isSunk();
	void read(std::istream& in, side whereTo, Game& game1);
	void write(std::ostream& out); 
	void Ship::attack(Point& coordinate, Vector<Ship*> other, gameboard& playerBoard, gameboard& enemyBoard, Game& game);
	bool isSuccessfulHit(Point& coordinate,const Vector<Ship*>& other);
	Ship* shipFactory(shipChoice shipp);
	virtual void specialAbility(Point& coordinate, side whereTo, Game& game) = 0; 
};
