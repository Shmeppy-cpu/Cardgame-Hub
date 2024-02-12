#include "Deck.h"
#include "ConsoleManager.h"

void Deck::fillDeck() {
	string suits[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	for (int s = 0; s <= 3; s++) {
		for (int i = 2; i <= 14; i++) {
			Card cardToAdd(suits[s], i);
			deckOfCards.push(cardToAdd);
		}
	}
}

void Deck::shuffleDeck() {
	vector<Card> temporaryDeck;

	for (int i = 0; i < 52; i++) {
		temporaryDeck.push_back(deckOfCards.front());
		deckOfCards.pop();
	}

	random_shuffle(temporaryDeck.begin(), temporaryDeck.end());

	for (Card i : temporaryDeck) {
		deckOfCards.push(i);
	}
}

Card Deck::getTopCard() {
	Card card = deckOfCards.front();
	deckOfCards.pop();
	return card;
}
