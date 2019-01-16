#pragma once
#include "stdafx.h"
#include "ComputerPlayerShipSet.h"

enum comands { load, newGame };

struct Game
{
public:
	gameboard myBoard;
	gameboard myShootBoard;
	gameboard enemyBoard;
	gameboard enemyShootBoard;
	Vector<Point> hitShipCoordinatesComputer;               // <-записват се ударените точки на комп.
	Vector<Point> hitShipCoordinatesPlayer;                 // <- на играча
	ShipSet player;
	ComputerShipset computer;
	void getInfo()const;
	void printScreen(); 
	void saveGame(String fileName); 
	void loadGame(String fileName);  
	Game();
	bool victory();
	void Info();
	void ShowBoard();
private:
	String screen; 
	void vectorPointRead(std::istream& in,Vector<Point>& vec);
	void vectorReadChoices(std::istream&, Vector<int>& vec);  // можете и темплейтна , конкретно за choices
	void saveBoard(std::ostream& out, const gameboard& board);
	void loadBoard(std::istream& in, gameboard& board);
	String getScreenASCI(std::ifstream& in); 

};