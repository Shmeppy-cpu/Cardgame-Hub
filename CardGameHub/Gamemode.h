#pragma once
#include "player.h"
#include "deck.h"
#include <vector>
#include "ConsoleManager.h"

class Gamemode
{
protected:
	player* mainPlayer;
	player* dealer;

	bool gameRunning;

	Gamemode();

	void printLogo();

	void setUpGamemode(int nPlayers, int nHandCount, string nPlayerOutText, string nLogo);

	void newHands();

	void listAllPlayersHands(int hiddenCards);

	vector<player>& getAllPlayers();

	void bustPlayer(player& player);

	vector<player>& getBustPlayers();

	void dealCard(player& player);

	void displayText(string text, string colorCode);

	void win(player winner);

	void putPlayerUpForWinning(player player);

	vector<player>& getPlayersUpForWinning();

private:
	vector<player> players;
	vector<player> bustPlayers;
	vector<player> playersUpForWinning;
	Deck deck;
	ConsoleManager console;

	int howManyPlayers = 2;
	int howManyCardsPerStartingHand = 2;
	string playerOutText;
	string logo;
};

