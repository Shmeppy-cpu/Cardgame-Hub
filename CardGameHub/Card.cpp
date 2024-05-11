#include "Card.h"
#include <string>
#include "ConsoleManager.h"
               
using namespace std;

Card::Card() {
	//Defualt constructor
	suit = Placeholder;
	value = 1;
}

Card::Card(enum_suit nSuit, int nValue) {
	suit = nSuit;
	value = nValue;
}

string Card::getDisplayForm() {
	string suitString;
	string visualValue;

	//get a string for the correct suit
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

		//get the visual value of the card (13 becomes K etc) and add the suits string to the end of it,
		visualValue = getVisualValue() + "^" + suitString;

		//bool to alternate whether a - is being added at the front or back of the string.
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

		//add square brackets surronding the string before returning it.
		visualValue = "[" + visualValue + "]";
	}

	return visualValue;
}

enum_suit Card::getSuit() {
	return suit;
}

string Card::getVisualValue() {
	string visualValue;
	//returns the visual value of the cards numerical value so that 12 is displayed as Q rather than 12

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

	/*
	changes the return value based on the ruleset applied too it, 
	for example in blackjack, J, Q, K are all worth 10 so anything with a value above 10 is returned as 10 with the blackjack rules applied
	*/

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
	//if the suit is Hearts or diamonds return the colorCode for red, return the code for black if the suit is clubs or spades

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

void Card::overrideValue(int newValue) {
	value = newValue;
}
