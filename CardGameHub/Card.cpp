#include "Card.h"
#include <string>
#include "ConsoleManager.h"

using namespace std;

Card::Card(string nSuit, int nValue) {
	suit = nSuit;
	value = nValue;
}

string Card::getDisplayForm() {
	return ">-" + getVisualValue() + " of " + getSuit() + "-<";
}

void Card::display() {
	string colorCode;
	if (suit == "Hearts" or suit == "Diamonds") {
		colorCode = "31";
	}
	else if (suit == "Spades" or suit == "Clubs")
	{
		colorCode = "30";
	}

	console.displayText(">-" + getVisualValue() + " of " + getSuit() + "-<", colorCode);
}

string Card::getSuit() {
	return suit;
}

string Card::getVisualValue() {
	string visualValue;

	switch (value)
	{
	case(11):
	{
		visualValue = "Jack";
		break;
	}
	case(12):
	{
		visualValue = "Queen";
		break;
	}
	case(13):
	{
		visualValue = "King";
		break;
	}
	case(14):
	{
		visualValue = "Ace";
		break;
	}
	default:
		visualValue = to_string(value);
		break;
	}

	return visualValue;
}

int Card::getNumValue() 
{
	if (value > 10) {
		if (value == 14) {
			value = 11;
		}

		value = 10;
	}

	return value;
}
