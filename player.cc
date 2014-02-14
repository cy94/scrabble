// player.cc

#include<iostream>
#include<vector>
#include<cassert>
#include<string>
#include "player.h"
#include "bag.h"
#include "board.h"
#include "tile.h"
#include "rack.h"

using namespace std;

Player::Player(string s, Board& b, Bag& bg):
	score(0),
	name(""),
	board(b),
	bag(bg)
{
	rack = new Rack;
	
	board.addToSquare(112 , bag.getTile());
	fillRack();
	
}

Player::~Player()
{
	delete rack;
}

void Player::selfTest() const
{
	rack->selfTest();
	board.selfTest();
	bag.selfTest();
}

vector<string> Player::placeLetters(string letters, int index, direction dir)
{
	vector<string> words;
	bool inDirection = false;
	
	//check if direction is ok
	if(dir == NONE)
	{
		cout << "Direction wrong" << endl;
		return words;
	}
		
	//word too long?
	if(letters.size() > 7)
	{
		cout << "Word too long" << endl;
		return words;
	}
		
	// check if all letters are in rack
	if(!rack->hasChars(letters))
	{
		cout << "Dont have tiles" << endl;
		return words;
	}
	
	if(!board.canPlaceLetters(letters, index, dir))
	{
		cout << "Cannot place letters" << endl;
		return words;
	}
	
	int tempndx;
	string str1, str2;
	string mainstr;
	
	for(auto c : letters)
	{
		//already has a tile
		while(board.getTile(index)) //const method!
		{
			inDirection = true;
			mainstr += board.getTile(index)->getLetter(); //string along direction of placing
			//change index	
			if(dir == 0) //right
				index++;	
			else         //down
				index += 15;	
		}
		
		board.addToSquare(index, rack->getTile(c));
		mainstr += c; //string along direction of placing
		
		if(dir == HORIZONTAL) //possible words below and above
		{
			tempndx = index-15;
			str1 = "";
			str1 += c;
			
			while(tempndx/15 != 0 && board.getTile(tempndx)) //above
			{
				str1 = board.getTile(tempndx)->getLetter() + str1; // add char in other order!
				tempndx -= 15;
			}
			
			tempndx = index+15;
			str2 = "";
			
			while(tempndx/15 != 15 && board.getTile(tempndx)) //below
			{
				str2 += board.getTile(tempndx)->getLetter();
				tempndx += 15;
			}
			
			if(str1.size() + str2.size() > 1)
				words.push_back(str1 + str2);
		}
		else                 //possible words left and right
		{
			tempndx = index-1;
			str1 = "";
			str1 += c;
			
			while(tempndx%15 != 0 && board.getTile(tempndx)) //left
			{
				str1 = board.getTile(tempndx)->getLetter() + str1; // add char in other order!
				tempndx -= 1;
			}
			
			tempndx = index+1;
			str2 = "";
			
			while(tempndx%15 != 14 && board.getTile(tempndx)) //right
			{
				str2 += board.getTile(tempndx)->getLetter();
				tempndx += 1;
			}
			
			if(str1.size() + str2.size() > 1)
				words.push_back(str1 + str2);
		}
		//change index	
		if(dir == 0) //right
			index++;	
		else         //down
			index += 15;	
	}
	if(inDirection) //previous char on board along this direction
		words.push_back(mainstr);
		
	selfTest();
	return words;
}

void Player::fillRack()
{
	Tile* t;
	while(rack->getNumTiles() < 7 && (t=bag.getTile()) != nullptr)
	{
		rack->addTile(t);
	}
	
	selfTest();
}

void Player::playTurn()
{
	rack->show();
	
	string letterString;
	int locationNdx;
	char dir;

	getInput( letterString, locationNdx, dir );
	vector<string> words = placeLetters(letterString, locationNdx, charToDirection(dir));
	
	cout << "Possible words: "<< endl;
	for(auto word: words)
	{
		cout << "-->" << word << endl;
	}
	fillRack();
	
	selfTest();
}

direction Player::charToDirection(char c)
{
	switch(c){
		case 'h':
			return HORIZONTAL;
		case 'v':
			return VERTICAL;
		default:
			return NONE;
	}
}

void Player::getInput( string& letters, int& locationNdx, char& direction )
{
	do{
		cout << "Enter the string, location (0-224), direction (h/v) " << endl;
		cin >> letters >> locationNdx >> direction;
		cin.clear();
	} while( locationNdx < 0 || locationNdx > 224 || (direction != 'h' && direction != 'v' ));
}
