#pragma once
#include <string>
#include <iostream>
#include "ConsoleManager.h"

using namespace std;

enum enum_suit {
	Hearts,
	Diamonds,
	Spades,
	Clubs
};

enum enum_valueRuleSet {
	normal,
	blackjack,
};

class Card
{
private:
	int value;
	enum_suit suit;
	ConsoleManager console;

public:
	Card(enum_suit nSuit, int nValue);

	string getDisplayForm();

	void display();

	enum_suit getSuit();

	string getVisualValue();

	int getNumValue(enum_valueRuleSet ruleSet);
};

