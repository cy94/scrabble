// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
#include<iostream>

class Rack;
class Bag;
class Board;
class Tile; // needed?

enum direction{HORIZONTAL, VERTICAL, NONE};

class Player{
private:
	int score;
	std::string name;
	
	Rack*  rack;
	Board& board;
	Bag&   bag;
	
	std::vector<std::string> placeLetters(std::string letters, int index, direction dir);
	void getInput( std::string& letters, int& locationNdx, char& direction );
	void fillRack();
	
	static direction charToDirection(char c);
public:
	Player();
	Player(std::string s, Board& board, Bag& bag);
	~Player();

	void selfTest() const;
	
	void playTurn();
};

#endif
