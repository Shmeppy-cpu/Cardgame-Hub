#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "player.h"
#include "Gamemode.h"
#include "Blackjack.h"
#include "ConsoleManager.h"

void testDeck();

int main()
{
	srand(1);
	//srand(time(0));

	system("Color 60");

	Blackjack blackjack;

	//testDeck();
}

void testDeck() {
	Deck deck;
	deck.fillDeck();
	deck.shuffleDeck();

	for (int i = 0; i < 52; i++) {
		Card card = deck.getTopCard();
		card.display();
	}
}