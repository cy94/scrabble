// rack.h

#ifndef RACK_H
#define RACK_H

#include<string>

class Tile;
class Bag;


class Rack{
private:
	Tile* tiles[7];
public:
	Rack();
	Rack(Bag&);
	~Rack();
	
	void show() const;
	int getNumTiles() const;
	bool addTile(Tile* t);
	
	bool hasTile(char letter);
	Tile* getTile(int index); 
	Tile* getTile(char c);
	
	Tile* showTile(int index) const;
	Tile* showTile(char c) const;
	
	std::string getChars() const;
	bool hasChars(std::string letters) const;
	
	void selfTest() const;
};

#endif
