#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "Card.h"
#include "ConsoleManager.h"

using namespace std;

class player
{
private:
	bool isMainPlayer = false;
	queue<Card> hand;
	string name;
	ConsoleManager console;
	bool out = false;

	vector<string> names = {
	"Issy",
	"Owen",
	"Rhys",
	"Will",
	"Jake",
	"Abby",
	"Katie",
	"Sasha"
	};

public:
	void setAsMainPlayer();

	bool getIsMainPlayer();

	void giveCard(Card ncard);

	void listHand(int hiddenCards);

	void setName(string nName);

	int getHandValue();

	string getName();

	void beaten();

	bool isOut();

	void assignRandomName();
};

