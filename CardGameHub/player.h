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
	bool upForWin = false;
	enum_valueRuleSet lastUsedRuleSet = normal;

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

	int getHandValue(enum_valueRuleSet ruleSet);

	string getName();

	void setOutStatus(bool nInStatus);

	bool isOut();

	void assignRandomName();

	Card getTopCard();

	int getSizeOfHand();

	vector<Card> getHand();

	string handValueDisplay();
};

