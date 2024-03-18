#include "PyramidSolitaire.h"

PyramidSolitaire::PyramidSolitaire() {
	setUpGamemode(1, 2, " Lost!",
		R"(                                                                                                      
  _____                           _     _ 
 |  __ \                         (_)   | |
 | |__) |   _ _ __ __ _ _ __ ___  _  __| |
 |  ___/ | | | '__/ _` | '_ ` _ \| |/ _` |
 | |   | |_| | | | (_| | | | | | | | (_| |
 |_|    \__, |_|  \__,_|_| |_| |_|_|\__,_|
         __/ |                            
        |___/                                     
)"
);

	newGame();
	displayPyramid();
}

void PyramidSolitaire::newGame() {
	printLogo();

	buildPyramid();
}

void PyramidSolitaire::buildPyramid() {

	int rows = 7;
	for (int collum = 0; collum < 7; collum++) {
		Pyramid.push_back({});
		for (int row = rows; row > 0; row--) {
			Pyramid[collum].push_back(getDeck().getTopCard());
		}

		rows--;
	}

	reverse(Pyramid.begin(), Pyramid.end());
}

void PyramidSolitaire::displayPyramid() {
	cout << endl;
	vector<string> line;
	vector<string> colors;

	for (vector<Card> Row : Pyramid) {
		line.clear();
		colors.clear();

		for (Card card : Row) {
			line.push_back(card.getDisplayForm());
			colors.push_back(card.getColorCode());
		}

		//console.displayAlongLine(line, colors);
		console.displayAlongLineWithSetGap(line, colors, 2);
	}
}
