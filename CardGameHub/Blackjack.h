#pragma once
#include "Gamemode.h"

class Blackjack : Gamemode
{
private:
	int hits;

public:
	Blackjack();

	void newRound();

	void checkForWin();

	void playersInput();

	void displayPlayersHands(int shownCards);
};

