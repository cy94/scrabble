// square.cc

#include<iostream>
#include<cassert>
#include<iomanip>
#include "colors.h"
#include "square.h"
#include "tile.h"

using namespace std;

Square::Square(int xcoord, int ycoord):
	x(xcoord),
	y(ycoord),
	tile(nullptr),
	multiplier(NONE)
{
}

Square::~Square() {}

void Square::show() const
{
	if(tile)
		cout << CYAN << setw(4) << tile->getLetter() << RESET << setw(4);
	else
	{
		switch(multiplier)
		{
			case DOUBLE_LETTER:
				cout << BLUE << setw(4) << y*15+x << RESET << setw(4); break;
			case TRIPLE_LETTER:
				cout << GREEN << setw(4) << y*15+x << RESET << setw(4);break;
			case DOUBLE_WORD:
				cout << RED << setw(4) << y*15+x << RESET << setw(4);break;
			case TRIPLE_WORD:
				cout << YELLOW << setw(4) << y*15+x << RESET << setw(4);break;
			case NONE: cout << setw(4) << y*15+x << setw(4); break;
			default: break;
		}
	}
}

void Square::setTile(Tile* t)
{
	tile = t;
	//CANNOT SELFTEST: TILE DOES NOT HAVE THIS SQUARE*
}

Tile* Square::showTile() const
{
	return tile;
}

void Square::setPremium(premium p)
{
	multiplier = p;
}

premium Square::getPremium() const
{
	return multiplier;
}

void Square::selfTest() const
{
	//cout << "Testing square ... ";
	//cout << "My tile:" << tile << endl;
	assert(tile == nullptr || this == tile->showSquare());
	//out << "passed" << endl;
}
