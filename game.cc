//game.cc

#include<iostream>
#include<vector>
#include<cassert>
#include "game.h"
#include "player.h"
#include "bag.h"
#include "board.h"

using namespace std;

Game::Game()
{
	board = new Board;
	bag = new Bag;
	players.push_back(new Player("Chandan", *board, *bag));
}

Game::~Game()
{
	delete board;
	delete bag;
	
	for(auto p : players)
		delete p;
}

void Game::begin()
{
	for(int i=0; i<10; i++)
	{
		system("clear");
		board->show();
		players[0]->playTurn();
	}
}


