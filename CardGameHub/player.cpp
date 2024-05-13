#include "player.h"
#include "ConsoleManager.h"

void player::setAsMainPlayer() {
	isMainPlayer = true;
}

bool player::getIsMainPlayer() {
	return isMainPlayer;
}

void player::giveCard(Card nCard) {
	hand.push(nCard);
	Beep(1000, 100);
}

void player::setName(string nName) {
	name = nName;
}

int player::getHandValue(enum_valueRuleSet ruleSet) {

	//set the last used rule set to the given one so it can be used elsewhere
	lastUsedRuleSet = ruleSet;

	int value = 0;

	//Creates a temporary vector and moves all the cards over to it so it can be iterated over
	vector<Card> temporaryHand;
	vector<int> values;
	int handSize = size(hand);

	for (int i = 0; i < handSize; i++) {
		temporaryHand.push_back(hand.front());
		hand.pop();
	}

	//add each cards value to the total value and add it back to the hand
	for (Card card : temporaryHand) {
		value += card.getNumValue(ruleSet);
		values.push_back(card.getNumValue(ruleSet));

		hand.push(card);
	}

	//if the ruleset is blackjack, iterate through all the values, if there is an 11(ace), set it to 1 if it goes over 21 and keep it at 11 otherwise
	if (ruleSet == blackjack and value > 21 and find(values.begin(), values.end(), 11) != values.end())
	{
		value = 0;

		for (Card card : temporaryHand) {

			if (card.getNumValue(blackjack) == 11) {
				card.overrideValue(1);
			}

			value += card.getNumValue(ruleSet);
		}
	}

	return value;
}

string player::getName() {
	return name;
}

void player::setOutStatus(bool nOutStatus) {
	out = nOutStatus;
}

void player::setPossibleWinStatus(bool nWinStatus) {
	upForWin = nWinStatus;
}

bool player::isOut() {
	return out;
}

bool player::isUpForWinning() {
	return upForWin;
}

void player::assignRandomName() {
	//pick a random name from the array of names and assign it to the player
	int amountOfNames = size(names);
	setName(names[(0 + rand() % amountOfNames)]);
}

Card player::getTopCard() {
	Card card = hand.front();
	hand.pop();
	return card;
}

int player::getSizeOfHand() {
	return size(hand);
}

vector<Card> player::getHand() {
	//creates a vector and fills it with the hand before returning it
	vector<Card> returnHand;
	int handSize = getSizeOfHand();
 
	for (int i = 0; i < handSize; i++) {
		returnHand.push_back(getTopCard());
	}

	for (Card card : returnHand) {
		giveCard(card);
	}

	return returnHand;
}
