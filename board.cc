// board.cc

#include<iostream>
#include<iomanip>
#include<string>
#include "square.h"
#include "board.h"
#include "tile.h"
#include "bag.h"

using namespace std;

Board::Board():
	firstword(false)
{
	for(int i=0; i<NUMSQUARES; i++)
	{
		squares[i] = new Square(i%15, i/15);
	}
	
	//add premium multipliers
	int dletter[] = {3,11,45,165,59,179,52,36,38,108,92,122,172,186,188,116,102,132,96,98,126,128};
	for(int index: dletter)
		squares[index]->setPremium(DOUBLE_LETTER);
		
	int tletter[] = {20,24,76,136,200,204,88,148,80,84,140,144};
	for(int index: tletter)
		squares[index]->setPremium(TRIPLE_LETTER);
		
	int dword[] = {16,32,48,64,28,42,56,70,112,196,182,168,154,208,192,176,160};
	for(int index: dword)
		squares[index]->setPremium(DOUBLE_WORD);
		
	int tword[] = {0,7,14,105,119,210,217,224};
	for(int index: tword)
	{
		squares[index]->setPremium(TRIPLE_WORD);
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
		
		squares[i]->show();
		
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

premium Board::getPremium(int index)
{
	return squares[index]->getPremium();
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
	//cout << "Testing board ... ";
	for(auto sq : squares)
	{
		sq->selfTest();
	}
	//cout << "passed" << endl;
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
	bool intersect = false;      // intersects existing letter
	bool through_center = false; // goes through center? for first word
	bool sizeok = false;
	int orgindex = index; //original index
	
	unsigned int placed = 0;     //no of letters placed
	
	if(( dir == 0 && index%15 != 0 && squares[index-1]->showTile() )|| //check behind
		             (index/15 != 0 && squares[index-15]->showTile()) )
		intersect = true;
	
	while(1)
	{
		if((dir==0 && index/15 != orgindex/15) || index > 224 || placed == letters.size())
			break;
		if(index == 112)
			through_center = true;
		if(squares[index]->showTile())
			intersect = true;
		else
		{
			if(dir == 0 && ((index/15 !=  0 && squares[index-15]->showTile()) ||
		   			    (index/15 != 14 && squares[index+15]->showTile())))
				intersect = true;
				
			if( (index%15 !=  0 && squares[index-1]->showTile()) ||
				 (index%15 != 14 && squares[index+1]->showTile()) )
				intersect = true;	
		
			placed++;
		}

		if(dir == 0) index++;
		else         index += 15;
	}	
	
	if(index >= 0 && index <= 224 && squares[index]->showTile())
		intersect = true;
		
	sizeok = (placed == letters.size());
		
	if(!firstword && through_center && sizeok)
	{
		firstword = true;
		return true;
	}	
	
	return sizeok && intersect;
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
