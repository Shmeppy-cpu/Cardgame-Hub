#include "Deck.h"
#include "ConsoleManager.h"

Deck::Deck() {
	fillDeck();
}

void Deck::fillDeck() {
	queue<Card> emptyDeck;
	deckOfCards = emptyDeck;

	enum_suit suits[4] = { Hearts, Diamonds, Spades, Clubs };

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

void Deck::returnCardToDeck(Card card) {
	deckOfCards.push(card);
}

Card Deck::getTopCard() {
	Card card = deckOfCards.front();
	deckOfCards.pop();
	return card;
}

int Deck::getSize() {
	return size(deckOfCards);
}

vector<Card> Deck::getDeckOfCardsAsVector() {
	vector<Card> cardVector;

	int sizeOfDeck = getSize();

	//fills the vector with all the cards from the deck queue
	for (int i = 0; i < sizeOfDeck; i++) {
		cardVector.push_back(getTopCard());
	}

	//re-fill the deck with the cards used to assemble the vector
	for (Card card : cardVector) {
		deckOfCards.push(card);
	}

	return cardVector;
}
