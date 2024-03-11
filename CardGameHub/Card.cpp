#include "Card.h"
#include <string>
#include "ConsoleManager.h"
               
using namespace std;

Card::Card(enum_suit nSuit, int nValue) {
	suit = nSuit;
	value = nValue;
}

string Card::getDisplayForm() {
	return ">-" + getVisualValue() + " of " + getSuit() + "-<";
}

void Card::display() {
	string colorCode;
	if (suit == Hearts or suit == Diamonds) {
		colorCode = "31";
	}
	else if (suit == Spades or suit == Clubs)
	{
		colorCode = "30";
	}

	console.displayText(getDisplayForm(), colorCode);
}
string Card::getSuit() {
	switch (suit)
	{
	case Hearts:
		return "Hearts";
		break;
	case Diamonds:
		return "Diamonds";
		break;
	case Spades:
		return "Spades";
		break;
	case Clubs:
		return "Clubs";
		break;
	default:
		break;
	}
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
	return value;
}
