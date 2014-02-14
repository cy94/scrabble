#include<iostream>
#include<vector>
#include<cassert>
#include<cstdlib>
#include<ctime>
#include "tile.h"
#include "bag.h"

using namespace std;

//using array
Bag::Bag():
	numTiles(100)
{
	int currentTile = 0;
	//random picking of tiles
	srand(time(nullptr));
	
	//blank tiles
	for(int i=0; i<2; i++)
	{
		tiles[currentTile++] = new Tile(' ', 0);
	}
	
	//e tiles
	for(int i=0; i<12; i++)
	{
		tiles[currentTile++] = new Tile('e', 1);
	}
	
	//a and i tiles
	for(int i=0; i<9; i++)
	{
		tiles[currentTile++] = new Tile('a', 1);
		tiles[currentTile++] = new Tile('i', 1);
	}
	
	//o tiles
	for(int i=0; i<8; i++)
	{
		tiles[currentTile++] = new Tile('o', 1);
	}
	
	//n,r,t tiles
	for(int i=0; i<6; i++)
	{
		tiles[currentTile++] = new Tile('n', 1);
		tiles[currentTile++] = new Tile('r', 1);
		tiles[currentTile++] = new Tile('t', 1);
	}
	
	//l,s,u,d tiles
	for(int i=0; i<4; i++)
	{
		tiles[currentTile++] = new Tile('l', 1);
		tiles[currentTile++] = new Tile('s', 1);
		tiles[currentTile++] = new Tile('u', 1);
		tiles[currentTile++] = new Tile('d', 2);
	}
	
	//g tiles
	for(int i=0; i<3; i++)
	{
		tiles[currentTile++] = new Tile('g', 2);
	}
	
	//b,c,m,p,f,h,v,w,y tiles
	for(int i=0; i<2; i++)
	{
		tiles[currentTile++] = new Tile('b', 3);
		tiles[currentTile++] = new Tile('c', 3);
		tiles[currentTile++] = new Tile('m', 3);
		tiles[currentTile++] = new Tile('p', 3);
		
		tiles[currentTile++] = new Tile('f', 4);
		tiles[currentTile++] = new Tile('h', 4);

		tiles[currentTile++] = new Tile('v', 4);
		tiles[currentTile++] = new Tile('w', 4);
		tiles[currentTile++] = new Tile('y', 4);
	}
	
	//other tiles - single
	tiles[currentTile++] = new Tile('k', 5);
	tiles[currentTile++] = new Tile('j', 8);
	tiles[currentTile++] = new Tile('x', 8);
	tiles[currentTile++] = new Tile('q', 10);
	tiles[currentTile++] = new Tile('z', 10);
	
	selfTest();
}

Bag::~Bag()
{
	for(int i=0; i<100; i++)
		delete tiles[i];
}

void Bag::show() const
{
	for(int i=0; i<numTiles; i++)
	{
		tiles[i]->show();
		cout << endl;
	}
}

int Bag::getNumTiles() const
{
	return numTiles;
}

Tile* Bag::getTile()
{
	if(numTiles)
	{
		int index = rand()%numTiles;
		Tile* temp = tiles[index];          // return this
		tiles[index] = tiles[numTiles - 1]; // move last tile to random index
		tiles[numTiles - 1] = temp;         // move random tile to last
		numTiles--;
		
		selfTest();
		
		return temp;
	}
	else
		return nullptr;
}

void Bag::reset()
{
	numTiles = 100;
	selfTest();
}

void Bag::selfTest() const
{
	cout << "Testing bag   ... ";
	for(int i=0; i<numTiles; i++)
		tiles[i]->selfTest();
	cout << "passed" << endl;
}

void Bag::addTile(Tile* t) 
{
	if(numTiles != 100)
		tiles[numTiles] = t;
	numTiles++;
	
	selfTest();
}

Tile* Bag::getTile( char letter )
{
	int location = 0;
	bool found = 0;
	Tile *tile = nullptr;
	
	for( int ndx = 0; !found && ndx < numTiles; ndx++ ){ 
		tile = tiles[ndx];
		if( tile->getLetter() == letter ){
			found = true;
			location = ndx;
		}
	}
	if( found ){
		// Push the null to the back
		tiles[location] = tiles[numTiles-1];
		tiles[numTiles-1] = tile;
		numTiles--;
	}
	selfTest();
	return tile;
}

