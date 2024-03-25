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
	playerInput();
}

void PyramidSolitaire::newGame() {
	gameRunning = true;

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
	printLogo();

	cout << endl;
	vector<string> line;
	vector<string> colorsOfCards;
	vector<string> colorsOfInputs;

	vector<string> inputs;

	int rowI = 0;
	int cardI = 0;

	for (vector<Card> Row : Pyramid) {
		cardI = 0;
		line.clear();
		colorsOfCards.clear();
		colorsOfInputs.clear();
		inputs.clear();

		for (Card card : Row) {
			line.push_back(card.getDisplayForm());
			colorsOfCards.push_back(card.getColorCode());

			inputs.push_back("<---<" + to_string(rowI) + "" + to_string(cardI) + ">--->");
			colorsOfInputs.push_back("37");

			cardI++;
		}

		console.displayAlongLineWithSetGap(line, colorsOfCards, 2);
		console.displayAlongLineWithSetGap(inputs, colorsOfInputs, 3);

		rowI++;
	}

	cout << endl;
}

void PyramidSolitaire::playerInput() {
	Card currentCard(Placeholder, 1);
	string playerInp;

	while (gameRunning == true) {

		if (currentCard.getSuit() != Placeholder) 
		{
			returnCardToDeck(currentCard);
		}

		console.clearConsole();
		displayPyramid();

		currentCard = getDeckTopCard();
		console.displayAlongLineWithSetGap({ currentCard.getDisplayForm(), "code below card to try and match, c for new card " }, { currentCard.getColorCode(), "37" }, 5);
		getline(cin, playerInp);
	}
}
