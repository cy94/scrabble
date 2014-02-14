// square.cc

#include<iostream>
#include<cassert>
#include<iomanip>
#include "square.h"
#include "tile.h"

using namespace std;

Square::Square(int xcoord, int ycoord):
	x(xcoord),
	y(ycoord),
	tile(nullptr)
{
}

Square::~Square() {}

void Square::show() const
{
	if(tile)
		tile->show();
	else
		//cout << setw(7) << right << x << " " << setw(3) << left << y;
		cout << "       ";
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

void Square::selfTest() const
{
	//cout << "Testing square ... ";
	//cout << "My tile:" << tile << endl;
	assert(tile == nullptr || this == tile->showSquare());
	//out << "passed" << endl;
}
