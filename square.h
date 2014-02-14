// square.h

#ifndef SQUARE_H
#define SQUARE_H

#include<iostream>
class Square;
class Tile;

class Square{
private:
	int x;
	int y;
	Tile* tile;
public:
	Square(int, int);
	~Square();
	void show() const;
	void setTile(Tile* t);
	Tile* showTile() const;
	void selfTest() const;
};

#endif
