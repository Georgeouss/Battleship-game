#pragma once
#include "Carrier.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Submarine.h"
#include "Destroyer.h"
#include "ComputerStrategy.h"
#include <fstream>

//using std::ios;


struct ShipSet
{
	Vector<Ship*> shipSet;
	Vector<int> choices;
	ShipSet();
	bool defeat();
	void placeAllShips(gameboard& playerBoard);
	virtual void setIndexWithoutRepeatingInChoices(const int choice);
	//void saveAllShips(String fileName);
};

struct ComputerShipset : public ShipSet
{
	ComputerShipset() :ShipSet()
	{
		this->fillChoices(); 
	}
	ComputerStrategy pcStrategy; 
	void attackCoordinateUpdate(char& column, char &row, ShipSet player);
	void setIndexWithoutRepeatingInChoices(const int choice);
	Point hardMode(Game& game1);
	void placeAllShips(gameboard& playerBoard);
private:
	void fillChoices(); 
	void findeCorrectDirection(Point coord,const ShipSet& player);

};

bool isCorrectChoice(const int& choice, Vector<int> choices);
//void switchChoice(const int choice, Point& coordinate, const ShipSet* set, side whereTo, Game& game1);
void switchChoice(const int choice, Point& coordinate, Point& otherCoord , const ShipSet* set, side whereTo, Game& game1);
