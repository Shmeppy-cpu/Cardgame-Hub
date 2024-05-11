#pragma once
#include <string>
#include <iostream>
#include "ConsoleManager.h"

using namespace std;

enum enum_suit {
	Placeholder,
	Hearts,
	Diamonds,
	Spades,
	Clubs
};

enum enum_valueRuleSet {
	normal,
	blackjack,
	solitaire,
};

class Card
{
private:
	int value;
	enum_suit suit;
	ConsoleManager console;

public:
	Card();

	Card(enum_suit nSuit, int nValue);

	string getDisplayForm();

	enum_suit getSuit();

	string getVisualValue();

	int getNumValue(enum_valueRuleSet ruleSet);

	string getColorCode();

	void overrideValue(int newValue);
};

