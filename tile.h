// tile.h

#ifndef TILE_H
#define TILE_H

#include<iostream>
class Square;

class Tile{
private:
	char letter;
	int score;
	Square* square;
public:
	Tile(char c, int s);
	~Tile();
	void show() const;
	void setSquare(Square* sq);
	char getLetter() const;
	void selfTest() const;
	Square* showSquare() const;
};

#endif
