// scrabbleTest.cc

#include<iostream>
#include<string>

#include "board.h"
#include "bag.h"
#include "rack.h"
#include "player.h"

using namespace std;

int main(int argc, char** argv)
{
	Board* board = new Board;
	Bag* bag = new Bag;
	
	Player* player = new Player("Chandan", *board, *bag);
	
	for(int i=0; i<10; i++)
	{
		board->show();
		player->playTurn();
	}
	
    return 1;
}
