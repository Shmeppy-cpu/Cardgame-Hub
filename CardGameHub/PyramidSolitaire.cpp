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
		clearedPyramid.push_back({});

		for (int row = rows; row > 0; row--) {
			Pyramid[collum].push_back(getDeck().getTopCard());
			clearedPyramid[collum].push_back(false);
		}

		rows--;
	}

	reverse(Pyramid.begin(), Pyramid.end());
	reverse(clearedPyramid.begin(), clearedPyramid.end());
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
			if (clearedPyramid[rowI][cardI] == true)
			{
				line.push_back("    .    ");
				colorsOfCards.push_back("37");

				inputs.push_back("       ");
				colorsOfInputs.push_back("37");
			}
			else {
				line.push_back(card.getDisplayForm());
				colorsOfCards.push_back(card.getColorCode());

				inputs.push_back("    <" + to_string(rowI) + "" + to_string(cardI) + ">    ");
				colorsOfInputs.push_back("37");
			}

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

	match_state matchState;

	bool newCard = true;
	bool returnCurrentCardToDeck = false;

	while (gameRunning == true) {
		console.clearConsole();
		displayPyramid();

		if (newCard == true) {
			if (returnCurrentCardToDeck == true)
			{
				returnCardToDeck(currentCard);
			}

			currentCard = getDeckTopCard();
		}

		console.displayAlongLineWithSetGap({ currentCard.getDisplayForm(), "enter code below card to try and match, just press enter for new card " }, { currentCard.getColorCode(), "37" }, 5);
		getline(cin, playerInp);

		if (playerInp != "") {
			//cout << matchCards(playerInp, currentCard) << endl;

			matchState = matchCards(playerInp, currentCard);

			switch (matchState)
			{
			case(matchedBoth):
			{
				newCard = true;
				returnCurrentCardToDeck = false;
				break;
			}
			case(matchedPlayerCard):
			{
				newCard = true;
				returnCurrentCardToDeck = false;
				break;
			}
			case(matchedPyramidCard):
			{
				newCard = false;
				returnCurrentCardToDeck = false;
				break;
			}
			case(noMatch):
			{
				newCard = false;
				returnCurrentCardToDeck = false;
				break;
			}
				break;
			}
		}
		else {
			newCard = true;
			returnCurrentCardToDeck = true;
		}
	}
}

match_state PyramidSolitaire::matchCards(string cardCode, Card playerCard)
{
	match_state matchState = noMatch;

	int row = stoi(cardCode.substr(0, 1), 0);
	int collum = stoi(cardCode.substr(1, 2), 0);

	if (canCardBeMatched(row, collum))
	{
		Card card = Pyramid[row][collum];

		if (card.getNumValue(solitaire) + playerCard.getNumValue(solitaire) == 13)
		{
			console.displayAlongLineWithSetGap({ playerCard.getDisplayForm(), " and ", card.getDisplayForm(), " match!" }, { playerCard.getColorCode(), "37", card.getColorCode(), "37" }, 2);
			removeCardFromPyramid(row, collum);
			matchState = matchedBoth;
		}
		else 
		{
			if (card.getNumValue(solitaire) == 13)
			{
				console.displayAlongLineWithSetGap({ card.getDisplayForm(), " clears itself!" }, { card.getColorCode(), "37" }, 2);
				removeCardFromPyramid(row, collum);
				matchState = matchedPyramidCard;
			}

			if (playerCard.getNumValue(solitaire) == 13)
			{
				console.displayAlongLineWithSetGap({ playerCard.getDisplayForm(), " clears itself!" }, { playerCard.getColorCode(), "37" }, 2);

				if (matchState == matchedPyramidCard) {
					matchState = matchedBoth;
				}
				else {
					matchState = matchedPlayerCard;
				}
			}

			if ((playerCard.getNumValue(solitaire) != 13) and (card.getNumValue(solitaire) != 13)) {
				console.displayAlongLineWithSetGap({ playerCard.getDisplayForm(), " and ", card.getDisplayForm(), " don't match..." }, { playerCard.getColorCode(), "37", card.getColorCode(), "37" }, 2);
				matchState = noMatch;
			}
		}
	}
	else
	{
		if (row < 7 and collum <= row) {
			Card card = Pyramid[row][collum];
			console.displayAlongLineWithSetGap({ "Can't match with ", card.getDisplayForm(), " yet..." }, { "37", card.getColorCode(), "37" }, 2);
		}
		else {
			console.displayText("No card there to match with", "37");
		}
	}

	//Card card = Pyramid[cardCode[0]][cardCode[1]];

	Sleep(3000);

	return matchState;
}

void PyramidSolitaire::removeCardFromPyramid(int row, int collum) {
	//Pyramid[row].erase(Pyramid[row].begin() + collum);
	//Pyramid[row][collum].setAsPlaceholder();

	clearedPyramid[row][collum] = true;
}

bool PyramidSolitaire::canCardBeMatched(int row, int collum) 
{
	if (row == 6 and collum <= 6)
	{
		return true;
	}
	else if (row < 6 and collum <= row) {
		if (clearedPyramid[row + 1][collum] == true and clearedPyramid[row + 1][collum + 1] == true) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
