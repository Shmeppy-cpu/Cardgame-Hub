#pragma once
#include "player.h"
#include "deck.h"
#include <vector>
#include "ConsoleManager.h"
#include "Card.h"

class Gamemode
{
protected:
	player* mainPlayer;
	player* dealer;
	ConsoleManager console;

	bool gameRunning;

	Gamemode();

	void printLogo();

	void setUpGamemode(int nPlayers, int nHandCount, string nPlayerOutText, string nLogo);

	void newHands();

	void listAllPlayersHands(int hiddenCards);

	vector<player>& getAllPlayers();

	void bustPlayer(player& player);

	void dealCard(player& player);

	void displayText(string text, string colorCode);

	void win(player winner);

	void putPlayerUpForWinning(player player);

	int getMostHeldCards();

	Deck& getDeck();

	Card getDeckTopCard();

	void returnCardToDeck(Card card);

private:
	vector<player> players;
	Deck deck;

	int howManyPlayers = 2;
	int howManyCardsPerStartingHand = 2;
	string playerOutText;
	string logo;
};

