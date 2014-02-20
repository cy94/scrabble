// rack.cc

#include<iostream>
#include<iomanip>
#include<string>
#include<cassert>
#include "tile.h"
#include "rack.h"
#include "bag.h"
#include "colors.h"
using namespace std;

Rack::Rack()
{
	//empty rack
	for(int i=0; i<7; i++)
	{
		tiles[i] = nullptr;
	}
}

Rack::Rack(Bag& bag)
{
	//initialise with bag - dont do this?
	for(int i=0; i<7; i++)
	{
		tiles[i] = nullptr;
	}
	
	for(int i=0; i<7; i++)
	{
		addTile( bag.getTile() );
	}
	
	selfTest();
}


Rack::~Rack()
{
	for(int i=0; i<7; i++)
	{
		tiles[i] = nullptr;
	}
}

void Rack::show() const
{
	for(int i=0; i<7; i++)
		cout << "---";
	cout << endl;
	
	for(int i=0; i<7; i++)
	{
		if(tiles[i] != nullptr)
		{
			cout << " " << tiles[i]->getLetter() << " ";
		}
		else
		{
			cout << "   ";
		}
	}
	cout << endl;
	
	for(int i=0; i<7; i++)
	{
		if(tiles[i] != nullptr)
		{
			cout << BOLDRED << setw(2) << tiles[i]->getScore() << " " << RESET;
		}
		else
		{
			cout << "   ";
		}
	}
	cout << endl;
	
	for(int i=0; i<7; i++)
		cout << "---";
	cout << endl;
}

bool Rack::addTile(Tile* t)
{
	for(int i=0; i<7; i++)
	{
		if(tiles[i] == nullptr)
		{
			tiles[i] = t;
			
			selfTest();
			return true;
		}
	}
	
	selfTest();
	return false;
}

Tile* Rack::getTile(int index)
{
	if(index < 0 || index > 6)
	{
		cout << "Invalid" << endl;
		return nullptr;
	}
	else
	{
		Tile* temp = tiles[index];
		tiles[index] = nullptr;
		
		selfTest();
		return temp;
	}
}

Tile* Rack::showTile(char c) const
{
	for(int i=0; i<7; i++)
		if(tiles[i]->getLetter() == c)
		{
			return tiles[i];
		}
	return nullptr;
}

Tile* Rack::showTile(int index) const
{
	assert(index < 0 || index > 6);
	
	return tiles[index];
}

Tile* Rack::getTile(char c)
{
	for(int i=0; i<7; i++)
		if(tiles[i] != nullptr && tiles[i]->getLetter() == c)
		{
			Tile* temp = tiles[i];
			tiles[i] = nullptr;
			
			selfTest();
			return temp;
		}
	
	return nullptr;
}

void Rack::selfTest() const
{
	//cout << "Testing rack  ... ";
	
	int n = 0;
	for(int i=0; i<7; i++)
	{
		if(tiles[i] != nullptr)
		{
			n++;
			tiles[i]->selfTest();
		}
	}
	//cout << "passed" << endl;
}

bool Rack::hasTile(char letter)
{
	for(int i=0; i<7; i++)
	{
		if(tiles[i]->getLetter() == letter)
			return true;
	}
	return false;
	
}

string Rack::getChars() const
{
	string s = "";
	for(int i=0; i<7; i++)
		if(tiles[i])
			s += tiles[i]->getLetter();
		else
			s += '0';
			
	return s;
}

bool Rack::hasChars(string letters) const
{
	string rackChars = getChars();
	size_t i;
	
	for(auto c : letters)
	{
		i = rackChars.find(c); 
		if(i == string::npos) //not in string
			return false;
		else
			rackChars[i] = '0'; //remove from string
	}
	
	return true;
}

int Rack::getNumTiles() const
{
	int numTiles = 0;
	for(int i=0; i<7; i++)
		if(tiles[i] != nullptr)
			numTiles++;
	return numTiles;
}
