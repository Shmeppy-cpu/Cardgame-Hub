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
	void fillDeck();

	void shuffleDeck();

	Card getTopCard();
};

