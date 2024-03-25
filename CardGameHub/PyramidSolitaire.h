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
	vector<vector<bool>> clearedPyramid;

	void newGame();

	void buildPyramid();

	void displayPyramid();

	void playerInput();

	match_state matchCards(string cardCode, Card playerCard);

	void removeCardFromPyramid(int row, int collum);

	bool canCardBeMatched(int row, int collum);
};

