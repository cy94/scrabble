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
#include "errorcodes.h"

using namespace std;

Player::Player(string s, Board& b, Bag& bg):
	score(0),
	name(""),
	board(b),
	bag(bg)
{
	rack = new Rack;
	
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

bool Player::canPlaceLetters(std::string letters, int index, direction dir)
{
	//check if direction is ok
	if(dir == NODIR)
	{
		cout << "Direction wrong" << endl;
		return false;
	}
		
	//word too long?
	if(letters.size() > 7)
	{
		cout << "Word too long" << endl;
		return false;
	}
		
	// check if all letters are in rack
	if(!rack->hasChars(letters))
	{
		cout << "Dont have tiles" << endl;
		return false;
	}
	
	if(index < 0 || index > 224)
	{
		cout << "Invalid index" << endl;
		return false;
	}
	
	if(!board.canPlaceLetters(letters, index, dir))
	{
		cout << "Cannot place letters" << endl;
		return false;
	}
	
	return true;
}

struct move Player::placeLetters(string letters, int index, direction dir)
{
	struct move m;
	int temp, mainScore = 0, mainMultiplier = 1, current, tempScore, tempMultiplier;
	unsigned int pos = 0;
	string mainStr = "", str1, str2;
	
	//check behind for letters
	if(dir == HORIZONTAL) //left
	{
		temp = index-1;
		while(temp/15 == index/15 && board.getTile(temp))
		{
			mainScore += board.getTile(temp)->getScore();
			mainStr = board.getTile(temp)->getLetter() + mainStr;
			temp--;
		}
	}
	else //above
	{
		temp = index-15;
		while(temp >= 0 && board.getTile(temp))
		{
			mainScore += board.getTile(temp)->getScore();
			mainStr = board.getTile(temp)->getLetter() + mainStr;
			temp-=15;
		}
	}
	
	//start placing
	current = index;
	while(1)
	{
		if(current > 224 || (dir == HORIZONTAL && (current/15 != index/15))) //out of board
			break;
			
		if(board.getTile(current))
		{
			mainScore += board.getTile(current)->getScore();
			mainStr += board.getTile(current)->getLetter();
		}
		else if(pos < letters.size())//place letter
		{
			Tile* t = rack->getTile(letters[pos]);
			pos++;
			premium p = board.getPremium(current);
			switch(p){
				case DOUBLE_LETTER: tempScore = t->getScore()*2; tempMultiplier = 1; break;
				case TRIPLE_LETTER: tempScore = t->getScore()*3; tempMultiplier = 1;  break;
				case DOUBLE_WORD: tempScore = t->getScore(); tempMultiplier = 2; break;
				case TRIPLE_WORD: tempScore = t->getScore(); tempMultiplier = 3; break;
				case NONE: tempScore = t->getScore(); tempMultiplier = 1; break;
			}
			mainScore += tempScore;
			mainMultiplier *= tempMultiplier;
			
			board.addToSquare(current, t); //add tile!
			mainStr += t->getLetter();
			
			//get the word containing this letter
			str1 = ""; str1 += t->getLetter();
			str2 = ""; 
			
			//after placing a letter, move l/r/u/d and make word, add score
			if(dir == HORIZONTAL)
			{
				//up
				temp = current-15;
				while(temp >= 0 && board.getTile(temp))
				{
					tempScore += board.getTile(temp)->getScore();
					str1 = board.getTile(temp)->getLetter() + str1; 
					temp -= 15;
				}
				//down
				temp = current+15;
				while(temp <= 224 && board.getTile(temp))
				{
					tempScore += board.getTile(temp)->getScore();
					str2 += board.getTile(temp)->getLetter(); 
					temp += 15;
				}
			}
			else
			{
				//left
				temp = current-1;
				while(temp/15 == current/15 && board.getTile(temp))
				{
					tempScore += board.getTile(temp)->getScore();
					str1 = board.getTile(temp)->getLetter() + str1; 
					temp--;
				}
				//right
				temp = current+1;
				while(temp/15 == current/15 && board.getTile(temp))
				{
					tempScore += board.getTile(temp)->getScore();
					str2 += board.getTile(temp)->getLetter(); 
					temp++;
				}
			}
			if(str1.size() + str2.size() > 1)
			{
				m.words.push_back(str1 + str2);
				m.scores.push_back(tempScore*tempMultiplier);
			}
		}
		else break;
		
		if(dir == HORIZONTAL) current++;
		else current += 15;
	}
	
	m.words.push_back(mainStr);
	m.scores.push_back(mainScore * mainMultiplier);
	m.placedletters = letters;
	
	selfTest();
	return m;
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
	
	if(!canPlaceLetters(letterString, locationNdx, charToDirection(dir)))
	{
		cout << "Cannot place" << endl;
		return;
	}
	
	cout << "Word can be placed" << endl;	
	struct move m = placeLetters(letterString, locationNdx, charToDirection(dir));

	int score = 0;
	cout << "Possible words: "<< endl;
	for(unsigned int i=0; i<m.words.size(); i++)
	{
		cout << " --> " << m.words[i] << " " << m.scores[i] << endl;
		score += m.scores[i];
	}
	cout << "Total score: " << score << endl;
	fillRack();
	
	moves.push_back( m );
	
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
			return NODIR;
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
