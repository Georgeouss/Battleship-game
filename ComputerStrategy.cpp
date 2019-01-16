#include "stdafx.h"
#include "ComputerStrategy.h"

//void ComputerStrategy::update(char& column, char &row) 
//{
//	if (!firstTry.column)                  //Ако не е сетнато
//	{
//		this->set(column, row);
//	}
//	else {
//		this->successful = true;
//		if (Up == lastDirection || Down == lastDirection) {
//			this->left = NotLikely;
//			this->right = NotLikely;
//		}
//		else {
//			this->up = NotLikely;
//			this->down = NotLikely;
//		}
//		this->getMove(column, row);
//	}
//}

void ComputerStrategy::reset() 
{
	/*this->firstTry.column = 0;
	this->firstTry.row = 0;
	this->lastTry.column = 0;
	this->lastTry.row = 0;*/
	/*this->up = NoChance;
	this->down = NoChance;
	this->left = NoChance;
	this->right = NoChance;
	this->successful = false;*/
	this->lastDirection = None;
}

//void ComputerStrategy::set(char c, char r) 
//{
//	this->firstTry.column = c;
//	this->firstTry.row = r;
//	this->lastTry.column = c;
//	this->lastTry.row = r;
//}



//bool ComputerStrategy::getMove(char &c, char &r)
//{
//	if (successful) {
//		switch (lastDirection)
//		{
//		case Up: this->up = Maybe; break;
//			/*if (Up == lastDirection) {
//				up = NotLikely;*/
//				/*}
//				else if (Down == lastDirection) {
//					down = NotLikely;*/
//		case Down: this->down = Maybe; break;
//		case Left: this->left = Maybe; break;
//		case Right: this->right = Maybe; break;
//		}
//		bool success = false;  // ако избора е бил успешен , за граничните случеи
//		while (!success) {
//			if (Maybe == this->up) {
//
//				if (Up == this->lastDirection)
//				{
//					this->lastDirection = Up;
//					this->lastTry = firstTry;
//				}
//
//				if ('0' == lastTry.row)
//				{
//					this->up = NoChance;
//				}
//				else
//				{
//					this->lastTry.row--;
//					success = true;
//				}
//			}
//			else if (Maybe == this->down)
//			{
//
//				if (Down == this->lastDirection)
//				{
//					this->lastDirection = Down;
//					this->lastTry = firstTry;
//				}
//
//				if ('9' == this->lastTry.row)
//				{
//					this->down = NoChance;
//				}
//				else
//				{
//					this->lastTry.row++;
//					success = true;
//				}
//			}
//			else if (Maybe == this->left)
//			{
//
//				if (Left == this->lastDirection) {
//					this->lastDirection = Left;
//					this->lastTry = firstTry;
//				}
//
//				if ('a' == this->lastTry.column) {
//					this->left = NoChance;
//				}
//				else {
//					this->lastTry.column--;
//					success = true;
//				}
//			}
//			else if (Maybe == this->right) {
//
//				if (Right == this->lastDirection) {
//					this->lastDirection = Right;
//					this->lastTry = firstTry;
//				}
//
//				if ('j' == this->lastTry.column) {
//					this->right = NoChance;
//				}
//				else {
//					++lastTry.column;
//					success = true;
//				}
//			}
//			else {
//				reset();
//				return false;
//			}
//		}
//		c = lastTry.column;
//		r = lastTry.row;
//		//this->successful = false;
//
//		return true;
//	}
//}


bool ComputerStrategy::getMove(char &c, char &r)
{
	switch (lastDirection)
	{
	case Up:
	{
		if (r != '0')
		{
			r--;
		}
		else
		{
			this->reset();
			this->getMove(c, r);
		}
	}break;
	case Down:
	{
		if (r != '9')
		{
			r++;
		}
		else
		{
			this->reset();
			this->getMove(c, r);
		}
	}
	break;
	case Left:
	{
		if (c != 'a')
		{
			c--;
		}
		else
		{
			this->reset();
			this->getMove(c, r);
		}
	}break;
	case Right:
	{
		if (c != 'j')
		{
			c++;
		}
		else
		{
			this->reset();
			this->getMove(c, r);
		}
	}break;
	default: {
		return false;
	}
	}
	return true;
}
