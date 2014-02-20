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
	//random picking of tiles
	srand(time(nullptr));
	
	const char letters[] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	const int  counts[]  = {2,9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};
	const int points[]   = {0,1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
	//~ const int points[]   = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	
	
	int n = 0;
	for(int i=0; i<27; i++)
		for(int j=0; j<counts[i]; j++)
			tiles[n++] = new Tile(letters[i], points[i]);
	
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
	//cout << "Testing bag   ... ";
	for(int i=0; i<numTiles; i++)
		tiles[i]->selfTest();
	//cout << "passed" << endl;
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

