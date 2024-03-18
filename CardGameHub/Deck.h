#pragma once
#include "Card.h"
#include <queue>
#include <string>

using namespace std;

class Deck
{
private:
	queue<Card> deckOfCards;
	ConsoleManager console;

public:
	Deck();

	void shuffleDeck();

	void returnCardToDeck(Card card);

	Card getTopCard();
};

