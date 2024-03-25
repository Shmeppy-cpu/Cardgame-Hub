#pragma once
#include "Gamemode.h"
#include "Card.h"
#include <vector>

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

	void pullCard();
};

