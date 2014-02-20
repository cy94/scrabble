// square.h

#ifndef SQUARE_H
#define SQUARE_H

#include<iostream>
class Square;
class Tile;

enum premium{DOUBLE_LETTER, TRIPLE_LETTER, DOUBLE_WORD, TRIPLE_WORD, NONE};

class Square{
private:
	int x;
	int y;
	Tile* tile;
	premium multiplier;
public:
	Square(int, int);
	~Square();
	void show() const;
	
	
	
	void setTile(Tile* t);
	Tile* showTile() const;
	
	void selfTest() const;
	
	void setPremium(premium p);
	premium getPremium() const;
};

#endif
