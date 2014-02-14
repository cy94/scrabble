// bag.h

#include<iostream>
#include<vector>

#ifndef BAG_H
#define BAG_H

class Tile;

class Bag{
private:
	Tile* tiles[100];
	int numTiles;
public:
	Bag();
	~Bag();
	void show() const;
	int getNumTiles() const;
	Tile* getTile();
	void addTile(Tile* t);
	void reset();
	void selfTest() const;
	Tile* getTile( char letter );
};

#endif
