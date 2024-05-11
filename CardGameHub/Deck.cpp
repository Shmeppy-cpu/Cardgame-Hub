#include "Deck.h"
#include "ConsoleManager.h"

Deck::Deck() {
	fillDeck();
}

void Deck::fillDeck() {
	//emptys the deck for when it gets re-made in some games
	queue<Card> emptyDeck;
	deckOfCards = emptyDeck;

	//creates an enum array to store the 4 types of suit
	enum_suit suits[4] = { Hearts, Diamonds, Spades, Clubs };

	//loop that runs 1 time for each suit, adding 12 new cards with values from 2 to 14 to the deck for each suit
	for (int s = 0; s <= 3; s++) {
		for (int i = 2; i <= 14; i++) {
			Card cardToAdd(suits[s], i);
			deckOfCards.push(cardToAdd);
		}
	}
}

void Deck::shuffleDeck() {
	vector<Card> temporaryDeck;

	//adds the cards from the deck into a vector which can be shuffled unlike a queue
	for (int i = 0; i < 52; i++) {
		temporaryDeck.push_back(deckOfCards.front());
		deckOfCards.pop();
	}

	//shuffles the temporary vector
	random_shuffle(temporaryDeck.begin(), temporaryDeck.end());

	//adds the newly shuffled cards from the temporary vector back to the deck
	for (Card i : temporaryDeck) {
		deckOfCards.push(i);
	}
}

void Deck::returnCardToDeck(Card card) {
	//adds given card back to the deck
	deckOfCards.push(card);
}

Card Deck::getTopCard() {
	//gets the top of the deck, removes it from the deck and then returns it
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

	//returns the copy of the deck in vector format
	return cardVector;
}
