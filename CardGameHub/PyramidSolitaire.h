#pragma once
#include "Gamemode.h"
#include "Card.h"
#include <vector>

enum match_state {
	noMatch,
	matchedBoth,
	matchedPyramidCard,
	matchedPlayerCard,
};

class PyramidSolitaire : Gamemode
{
public:
	PyramidSolitaire();
private:
	vector<vector<Card>> Pyramid;

	void newGame();

	void buildPyramid();

	void displayPyramid();

	void playerInput();

	match_state matchCards(string cardCode, Card playerCard);
};

