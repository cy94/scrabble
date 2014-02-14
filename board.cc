// board.cc

#include<iostream>
#include<iomanip>
#include<string>
#include "square.h"
#include "board.h"
#include "tile.h"
#include "bag.h"

using namespace std;

Board::Board()
{
	for(int i=0; i<NUMSQUARES; i++)
	{
		squares[i] = new Square(i%15, i/15);
	}
	
	selfTest();
}

Board::~Board()
{
	for(int i=0; i<225; i++)
	{
		delete squares[i];
	}
}

void Board::show() const
{
	cout << "  \t";
	for(int j=0; j<15; j++)
		cout << setw(5) << j << "   ";
	cout << endl;
	
	cout << "  \t";
	for(int j=0; j<15; j++)
		cout << "+-------";
	cout << "+" << endl;
			
	for(int i=0; i<NUMSQUARES; i++)
	{
		if(i%15 == 0)
			cout << (i/15) << "\t";
			
		cout << "|";
		if(squares[i]->showTile() != nullptr)
			squares[i]->show();
		else
			cout << setw(4) << i << setw(4);
		
		if((i+1)%15 == 0)
		{
			cout << "|" << endl;
			
			cout << "  \t";
			for(int j=0; j<15; j++)
				cout << "+-------";
				
			cout << "+" << endl;
		}
			
	}
}

bool Board::addToSquare(int index, Tile* t) // single index - 0 to 224
{
	return addToSquare(index%15, index/15, t);
}

bool Board::addToSquare(int xcoord, int ycoord, Tile* t)
{
	if(xcoord<0 || xcoord>14 || ycoord<0 || ycoord>14)
	{
		cout << "Invalid index";
		return false;
	}
	if( squares[ycoord*15 + xcoord]->showTile() == nullptr )
	{
		squares[ycoord*15 + xcoord]->setTile( t );
		t->setSquare( squares[ycoord*15 + xcoord] );
		
		selfTest();
		return true;
	}
	return false;
}

void Board::selfTest() const
{
	cout << "Testing board ... ";
	for(auto sq : squares)
	{
		sq->selfTest();
	}
	cout << "passed" << endl;
}
	
void Board::setupBoard(Bag* bag, const char* rows[])
{
	Tile* tile;
	
	for(int i=0; i<15; i++)
	{
		for(int j=0; j<15; j++)
		{
			if( rows[i][j] != '0' )
			{
				tile = bag->getTile( rows[i][j] );
				
				squares[ getI(j,i) ]->setTile( tile );
				tile->setSquare( squares[ getI(j,i) ] );
			}
		}
	}
	
	selfTest();
}

bool Board::canPlaceLetters (std::string letters, int index, int dir) const 
{
	if(index < 0 || index > 224)
		return false;
	
	bool first = true;      // first letter
	bool intersect = false; // intersects existing letter
	
	//first tile intersection
	if(index%15 != 0 && dir == 0 && squares[index-1]->showTile())       //check left tile
		intersect = true;
	else if(index/15 != 0 && dir == 1 && squares[index-15]->showTile()) //check tile above
		intersect = true;	
	
	for(auto c : letters)
	{
		if(index > 224)           //went below bottom
			return false;
		if(!first && index%15==0) // went beyond right
			return false;
		
		//check for intersection	
		if(((index+1)%15 != 14 && squares[index+1]->showTile())  ||     //right tile

		((index+15)/15 != 14 && squares[index+15]->showTile()) ||	  //bottom tile
		
		((index-15)/15 != 0 && squares[index-15]->showTile())  ||	  //top tile
		
		((index-1)%15 != 0 && squares[index-1]->showTile()))     	  //left tile
			intersect = true;		
		
		//square already has a tile? skip
		if(squares[index]->showTile())
		{
			//change index	
			if(dir == 0) //right
				index++;	
			else         //down
				index += 15;	
				
			if(index > 224 || index%15 == 0)
				return false;
			continue;
		}
		
		
		//change index	
		if(dir == 0) //right
			index++;	
		else         //down
			index += 15;	
		continue;
			
		if(first) //first letter
			first = false;
	}
	
	return intersect;
}

Tile* Board::getTile(int index) const
{
	return squares[index]->showTile();
}

int Board::getX(int index)
{
	return index%15;
}
int Board::getY(int index)
{
	return index/15;
}
int Board::getI(int x, int y)
{
	return y*15+x;
}
