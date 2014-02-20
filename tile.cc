// tile.cc

#include<iostream>
#include<cassert>
#include "tile.h"
#include "square.h"

using namespace std;

Tile::Tile(char c, int s):
	letter(c),
	score(s),
	square(nullptr)
{
}

Tile::~Tile()
{
}

void Tile::show() const
{
	cout << "   " << letter << "   ";
}

void Tile::setSquare(Square* sq)
{
	square = sq;
	
	selfTest();
}

char Tile::getLetter() const
{
	return letter;
}

int Tile::getScore() const
{
	return score;
}

Square* Tile::showSquare() const
{
	return square;
}

void Tile::selfTest() const
{
	//cout << "Testing tile ... ";
	assert( square == nullptr || this == square->showTile() );
	//cout << "passed" << endl;
}

