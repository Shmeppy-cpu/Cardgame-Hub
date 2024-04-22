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
	string visualValue;

	if (suit == Placeholder) {
		visualValue = "   -   ";
	}
	else {
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

		visualValue = getVisualValue() + "^" + suitString;

		bool rightSize = false;
		bool front = true;

		while (size(visualValue) != 12)
		{
			if (front == true) {
				front = false;
				visualValue = "-" + visualValue;
			}
			else {
				front = true;
				visualValue += "-";
			}
		}

		visualValue = "[" + visualValue + "]";
	}

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
	case(1):
	{
		visualValue = "A";
		break;
	}
	case(11):
	{
		visualValue = "J";
		break;
	}
	case(12):
	{
		visualValue = "Q";
		break;
	}
	case(13):
	{
		visualValue = "K";
		break;
	}
	case(14):
	{
		visualValue = "A";
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
		break;
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
		break;
	}
	case(solitaire): 
	{
		if (value == 14) {
			returnValue = 1;
		}
		else {
			returnValue = value;
		}
	}
	break;
	}

	return returnValue;
}

string Card::getColorCode() {
	switch (suit) {
	case(Hearts): {
		return "31";
	}
	case(Diamonds): {
		return "31";
	}
	case(Spades): {
		return "30";
	}
	case(Clubs): {
		return "30";
	}
	}
}

void Card::setAsPlaceholder() {
	suit = Placeholder;
}

void Card::overrideValue(int newValue) {
	value = newValue;
}
