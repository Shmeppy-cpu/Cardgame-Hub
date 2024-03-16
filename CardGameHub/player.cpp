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

void player::listHand(int hiddenCards) {
	//cout << "" << endl;

	string extra;
	vector<string> handDisplayLine;
	vector<string> colorCodes;

	if (getIsMainPlayer() == true or hiddenCards == 0 or isOut() == true) {
		extra = to_string(getHandValue(lastUsedRuleSet));
	}

	if (out == true)
	{
		if (upForWin == true) {
			extra = " standing" + to_string(getHandValue(lastUsedRuleSet));
		}
		else {
			extra = " out";
		}
	}

	vector<Card> temporaryHand;
	int handSize = hand.size();

	for (int i = 0; i < handSize; i++) {
		temporaryHand.push_back(hand.front());
		hand.pop();
	}

	console.displayText(name + "'s Hand: " + extra, "37");
	cout << endl;

	for (Card i : temporaryHand) {
		if (hiddenCards > 0)
		{
			handDisplayLine.push_back(">-Hidden-<");
			colorCodes.push_back("37");
			//console.displayText(">-Hidden-<", "37");
			hand.push(i);
			hiddenCards--;
		}
		else {
			handDisplayLine.push_back(i.getDisplayForm());

			colorCodes.push_back("37");

			//i.display();
			hand.push(i);
		}
	}

	console.displayAlongLine(handDisplayLine, colorCodes);

	cout << "" << endl;
}

void player::setName(string nName) {
	name = nName;
}

int player::getHandValue(enum_valueRuleSet ruleSet) {

	lastUsedRuleSet = ruleSet;

	int value = 0;

	//Creates a temporary vector and moves all the cards over to it so it can be iterated over
	vector<Card> temporaryHand;
	int handSize = size(hand);

	for (int i = 0; i < handSize; i++) {
		temporaryHand.push_back(hand.front());
		hand.pop();
	}

	for (Card card : temporaryHand) {
		value += card.getNumValue(ruleSet);

		hand.push(card);
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
	vector<Card> returnHand;

	for (int i = 0; i <= size(hand) + 1; i++) {
		returnHand.push_back(getTopCard());
	}

	for (auto card : returnHand) {
		giveCard(card);
	}

	return returnHand;
}

string player::handValueDisplay() {
	int value = getHandValue(lastUsedRuleSet);
	string display;
	if (value > 21) {
		display = "Bust! - " + to_string(value);
	}
	else if (isMainPlayer == true)
	{
		display = to_string(value);
	}
	else if (out == true) 
	{
		display = to_string(value);

	}
	else {
		display = "hidden!";
	}

	return display;
}
