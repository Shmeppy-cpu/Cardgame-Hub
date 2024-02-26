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

	string getSuit();

	string getVisualValue();

	int getNumValue();
};

