// Battleshipsproject71781.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"


int main()
{
	srand(time(NULL));
	Game game1;
	
	
	game1.printScreen();
	game1.getInfo();

	cout << endl;
	String name;
	cout << "Enter your name : ";
	cin >> name;
	int com;
	cout << "   Press 0 to Load Game" << endl;
	cout << "   Press 1 to Start a new Game" << endl;
	cout << "   Enter your choice : ";
	cin >> com;
	cout << endl;
	int mode = 1; 

	switch (com)
	{
	case load:
	{
		game1.loadGame("Test11");
	}
	break;
	case newGame:
	{

		cout << "1 Normal Game" << endl;
		cout << "2 Hard Mode" << endl;
		cin >> mode;
		system("cls");
		
		game1.computer.placeAllShips(game1.enemyBoard);
		
		cout << endl;
		game1.ShowBoard();
		game1.player.placeAllShips(game1.myBoard);
	}break;
	}
	game1.ShowBoard();

	int choice;
	Point coordinate;
	Point compCoord;
	int compChoice;
	size_t index; 
	

	while (!game1.victory())
	{
		
		if (game1.computer.choices.size() - 1)
		{
			
			index = rand() % (game1.computer.choices.size() - 1);
			compChoice = game1.computer.choices[index];
		}
		else
		{
			index = 0;
			compChoice = game1.computer.choices[index];
		}
		cout << game1.computer.choices[index] << endl;
		game1.computer.setIndexWithoutRepeatingInChoices(index);
	


		cout << "Press 0 to attack with Carrier\nPress 1 to attack with Battleship\nPress 2 to attack with Cruiser" << endl;
		cout << "Press 3 to attack with Submarine\nPress 4 to attack with Destroyer " << endl;
		cout << "Enter choice : ";

		do
		{
			cin >> choice;
		} while (!isCorrectChoice(choice, game1.player.choices));
		game1.player.setIndexWithoutRepeatingInChoices(choice);

		cout << "Comp atack : ";
		
		if (mode == 1)
			game1.computer.attackCoordinateUpdate(compCoord.column, compCoord.row, game1.player);
		else if (mode == 2)
			compCoord=game1.computer.hardMode(game1);
		cout << compCoord << endl; 
		

		cout << "Enter cooridante where to attack : ";
		coordinate.cinPoint();
		game1.player.shipSet[choice]->attack(coordinate, game1.computer.shipSet, game1.myShootBoard, game1.enemyBoard, game1);
		game1.computer.shipSet[index]->attack(compCoord, game1.player.shipSet, game1.enemyShootBoard, game1.myBoard, game1);
		switchChoice(choice, coordinate, compCoord, &game1.player, PC, game1);
		switchChoice(compChoice, compCoord, coordinate, &game1.computer, Player, game1);

		game1.saveGame("Test11");
		std::system("cls");
		game1.ShowBoard();
	}
	
	if (game1.computer.defeat())
		cout << name << " you win ! " << endl;
	else
		cout << "You lose !" << endl; 


	return 0;
}

