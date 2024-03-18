#include "Card.h"
#include <string>
#include "ConsoleManager.h"
               
using namespace std;

Card::Card(enum_suit nSuit, int nValue) {
	suit = nSuit;
	value = nValue;
}

string Card::getDisplayForm() {
	string suitString;

	switch (suit) {
	case(Hearts):
	{
		suitString = "Hearts";
		break;
	}
	case(Diamonds):
	{
		suitString = "Diamonds";
		break;
	}
	case(Clubs):
	{
		suitString = "Clubs";
		break;
	}
	case(Spades):
	{
		suitString = "Spades";
		break;
	}
	default:
		suitString = "Unkown";
		break;
	}

	//Queen-Diamonds

	string visualValue = getVisualValue() + "-" + suitString;

	for (int i = 0; i < 7 - (size(visualValue) / 2); i++) {
		visualValue = "-" + visualValue;
	}
	for (int i = 0; i < 7 - (size(visualValue) / 2); i++) {
		visualValue = visualValue + "-";
	}

	visualValue = "[" + visualValue + "]";

	return visualValue;
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
enum_suit Card::getSuit() {
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

int Card::getNumValue(enum_valueRuleSet ruleSet)
{
	int returnValue = 0; 

	switch (ruleSet) {
	case(normal):
	{
		returnValue = value;
	}
	case(blackjack):
	{
		if (value >= 10)
		{
			returnValue = 10;
			if (value == 14) {
				returnValue = 11;
			}
		}
		else {
			returnValue = value;
		}
	}
	}

	return returnValue;
}
