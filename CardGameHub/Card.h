#pragma once
#include <string>
#include <iostream>
#include "ConsoleManager.h"

using namespace std;

class Card
{
private:
	int value;
	string suit;
	ConsoleManager console;

public:
	Card(string nSuit, int nValue);

	string getDisplayForm();

	void display();

	string getSuit();

	string getVisualValue();

	int getNumValue();
};

