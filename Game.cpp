#include "stdafx.h"
#include "Game.h"


void Game::vectorPointRead(std::istream& in,Vector<Point>& vec)
{
	size_t size;
	in >> size;
	Point temp;
	vec.Empty();
	
	for (size_t i = 0; i < size; i++)
	{
		in >> temp.row >> temp.column; 
		vec.push_back(temp);
	}
}
void Game::vectorReadChoices(std::istream& in, Vector<int>& vec)
{
	size_t size;
	in >> size;
	int temp;
	vec.Empty();

	for (size_t i = 0; i < size; i++)
	{
		in >> temp ;
		vec.push_back(temp);
	}
}



void Game::saveBoard(std::ostream& out,const gameboard& board)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			out << board[i][j] << " ";
		out << endl;
	}
	out << endl; 
}

void Game::loadBoard(std::istream& in ,gameboard& board)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			in >> board[i][j] ;
		in.get();
	}
	in.get();
}


String Game::getScreenASCI(std::ifstream& in)
{
	String lines = "";        //All lines
	if (in)                      //Check if everything is good
	{
		while (in.good())
		{
			String tempLine;                  //Temp line
			in >> tempLine;							//Get temp line
			tempLine += String("\n");                      //Add newline character

			lines += tempLine;                     //Add newline
		}
		return lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}
void Game::getInfo()const
{
	cout << "Carrier    - Ability to attack twice " << endl;
	cout << "Battleship - Reveals all adjacent fields " << endl;
	cout << "Cruiser    - If is not hit or sunk restores +1 life  " << endl;
	cout << "Submarine  - 70 % chance to miss " << endl; 
	cout << "Destroyer  - Blocks one shot " << endl; 
}

void Game::printScreen()
{
	std::ifstream Reader("info.txt");             //Open file
	String Art = this->getScreenASCI(Reader);       //Get file
	cout << Art << endl;               //Print it to the screen
	Reader.close();                           //Close file
}


Game::Game()
{
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < columns; j++)
		{
			this->myBoard[i][j] = unshooted;
			this->myShootBoard[i][j] = unshooted;
			this->enemyBoard[i][j] = unshooted;
			this->enemyShootBoard[i][j] = unshooted;
		}
}

bool Game::victory()
{
	return (this->player.defeat() || this->computer.defeat());
}

void Game::saveGame(String fileName)
{
	std::ofstream out(fileName + String(".txt"));
	if (out.is_open())
	{
		for (size_t i = 0; i < shipsSetSize; i++)
		{
		//	out << i << endl;
			this->player.shipSet[i]->write(out);
			out << endl;
		}
		out << endl; 

		for (size_t i = 0; i < shipsSetSize; i++)
		{
		//	out << i << endl;
			this->computer.shipSet[i]->write(out);
			out << endl;
		}
		out << endl; 
		
		out << this->hitShipCoordinatesPlayer.size() << endl; 
		out << this->hitShipCoordinatesPlayer << endl;

		out << this->hitShipCoordinatesComputer.size() << endl; 
		out << this->hitShipCoordinatesComputer << endl;

		out << this->player.choices.size() << endl; 
		out << this->player.choices << endl; 

		out << this->computer.choices.size() << endl;
		out << this->computer.choices << endl;


		this->saveBoard(out, this->myBoard);
		this->saveBoard(out, this->myShootBoard);
		this->saveBoard(out, this->enemyBoard);
		this->saveBoard(out, this->enemyShootBoard);

		out.close();
	}
	else
		cout << "Unable ot open the file" << endl;
}

void Game::loadGame(String fileName)
{
	std::ifstream in(fileName + String(".txt"));
	if (in.is_open())
	{
		for (size_t i = 0; i < shipsSetSize; i++)
		{
			//	out << i << endl;
			this->player.shipSet[i]->read(in,Player,*this);
			in.get();
		}
		in.get(); 
	
		for (size_t i = 0; i < shipsSetSize; i++)
		{
			//	out << i << endl;
			this->computer.shipSet[i]->read(in,PC,*this);
			in.get();
		}
		in.get(); 

		this->vectorPointRead(in, hitShipCoordinatesPlayer);
		this->vectorPointRead(in, hitShipCoordinatesComputer);

		this->vectorReadChoices(in, this->player.choices);
		this->vectorReadChoices(in, this->computer.choices);

		

		this->loadBoard(in, this->myBoard);
		this->loadBoard(in, this->myShootBoard);
		this->loadBoard(in, this->enemyBoard);
		this->loadBoard(in, this->enemyShootBoard);

		in.close();
	}
	else
		cout << "Unable ot open the file" << endl;
}

void Game::Info()
{
	cout << "     -=My board=-                  -=Shoot Board=-    " << endl;
	cout << endl;
	cout << "---===INFO===---  : " << endl;
	cout << hitTheTarget << " - hit ,\n" << miss << " - miss" << endl;
	cout << abilityProtect << " - Dodged/Blocked shot\n" << shipOnBoard << " - placed ship " << endl;
	cout << unshooted << " - unshooted spot" << endl;
}

void Game::ShowBoard()
{
	cout << "   ";
	for (size_t i = 0; i < rows; i++)
	{
		cout << "|" << boardTop[i];
	}
	cout << "         ";

	for (size_t i = 0; i < rows; i++)
	{
		cout << "|" << boardTop[i];						// <-----------
	}
	//cout << "          ";

	/*for (size_t i = 0; i < rows; i++)
	{
		cout << "|" << boardTop[i];
	}
	cout << "          ";

	for (size_t i = 0; i < rows; i++)
	{
		cout << "|" << boardTop[i];
	}
	*/cout << "|" << endl;
	for (size_t i = 0; i < rows; i++)
	{
		cout << boardColumn[i] << " ";
		for (int j = 0; j < columns; j++)
			cout << this->myBoard[i][j] << " ";
		cout << "     ";

		//cout << boardColumn[i] << " ";
		//for (int j = 0; j < columns; j++)    /////////////// <==============
		//	cout << this->enemyBoard[i][j] << " ";
		//cout << "      ";

		//cout << boardColumn[i] << " ";
		//for (int j = 0; j < columns; j++)    /////////////// <==============
		//	cout << this->enemyShootBoard[i][j] << " ";
		//cout << "      ";

		cout << boardColumn[i] << " ";
		for (int j = 0; j < columns; j++)
			cout << this->myShootBoard[i][j] << " ";
		//cout << enemyBoard[i][j] << " ";
		cout << endl;
	}
	Game::Info();
	cout << endl;
}