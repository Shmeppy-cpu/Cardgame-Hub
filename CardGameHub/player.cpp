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
	cout << "" << endl;

	string extra;

	if (getIsMainPlayer() == true or hiddenCards == 0) {
		extra = to_string(getHandValue());
	}

	if (out == true)
	{
		extra = " out";
	}

	vector<Card> temporaryHand;
	int handSize = hand.size();
	
	for (int i = 0; i < handSize; i++) {
		temporaryHand.push_back(hand.front());
		hand.pop();
	}

	console.displayText(name + "'s Hand: " + extra, "37");

	for (Card i : temporaryHand) {
		if (hiddenCards > 0)
		{
			console.displayText(">-Hidden-<", "37");
			hand.push(i);
			hiddenCards--;
		}
		else {
			i.display();
			hand.push(i);
		}
	}

	cout << "" << endl;
}

void player::setName(string nName) {
	name = nName;
}

int player::getHandValue() {

	int value = 0;

	//Creates a temporary vector and moves all the cards over to it so it can be iterated over
	vector<Card> temporaryHand;
	int handSize = size(hand);

	for (int i = 0; i < handSize; i++) {
		temporaryHand.push_back(hand.front());
		hand.pop();
	}

	for (Card card : temporaryHand) {
		value += card.getNumValue();

		hand.push(card);
	}

	return value;
}

string player::getName() {
	return name;
}

void player::beaten() {
	out = true;
}
