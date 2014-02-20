//game.h

#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<vector>

class Player;
class Board;
class Rack;
class Bag;

class Game{
	Board* board;
	Bag* bag;
	std::vector<Player*> players;
public:
	Game();
	~Game();
	void begin();
};

#endif
