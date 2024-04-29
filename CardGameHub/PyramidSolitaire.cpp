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
}

void PyramidSolitaire::newGame() {
	gameRunning = true;

	getDeck().fillDeck();
	getDeck().shuffleDeck();

	buildPyramid();
	playerInput();
}

void PyramidSolitaire::buildPyramid() {
	Pyramid.clear();
	clearedPyramid.clear();

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
				line.push_back("[ .......... ]");
				colorsOfCards.push_back("37");

				inputs.push_back("              ");
				colorsOfInputs.push_back("37");
			}
			else {
				line.push_back(card.getDisplayForm());
				colorsOfCards.push_back(card.getColorCode());

				inputs.push_back("     (" + to_string(rowI) + "" + to_string(cardI) + ")     ");
				colorsOfInputs.push_back("37");
			}

			cardI++;
		}

		console.displayAlongLineWithSetGap(line, colorsOfCards, 2);
		console.displayAlongLineWithSetGap(inputs, colorsOfInputs,2);

		rowI++;
	}

	cout << endl;
}

void PyramidSolitaire::playerInput() {
	//Card currentCard(Placeholder, 1);
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

		if (howManyMatchesLeft() <= 0) {
			endGame();
		}

		console.displayAlongLineWithSetGap({to_string(getDeck().getSize()), currentCard.getDisplayForm(), "enter code below card to try and match, just press enter for new card "}, {"37", currentCard.getColorCode(), "37"}, 5);
		console.displayText("Potential Matches Left - " + to_string(howManyMatchesLeft()), "37");
		getline(cin, playerInp);


		if ((playerInp != "") and (size(playerInp) == 2)) {
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
	int collum;

	if (size(cardCode) < 2) {
		collum = 0;
	}
	else {
		collum = stoi(cardCode.substr(1, 2), 0);
	}

	//Only checks for match if the card given by the player hasn't already been cleared
	if (clearedPyramid[row][collum] == true) {
		matchState = noMatch;
		console.displayAlongLine({ "No Card There" }, {"37"});
	}
	else {
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
	}

	//Card card = Pyramid[cardCode[0]][cardCode[1]];

	Sleep(2000);

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

int PyramidSolitaire::howManyMatchesLeft() {
	int matchesLeft = 0;
	int row = 0;
	int collum = 0;
	vector<Card> playerCards = getDeck().getDeckOfCardsAsVector();

	playerCards.push_back(currentCard);

	for (vector<Card> collumCards : Pyramid) {
		for (Card Pcard : collumCards) {
			if (canCardBeMatched(row, collum) == true) {
				for (Card card : playerCards) {
					if (clearedPyramid[row][collum] == false) {
						if ((Pcard.getNumValue(solitaire) + card.getNumValue(solitaire) == 13) or (Pcard.getNumValue(solitaire) == 13)) {
							//cout << Pcard.getDisplayForm() << " MATCH " << card.getDisplayForm() << endl;
							matchesLeft++;
						}
					}
				}
			}

			collum++;
		}

		row++;
		collum = 0;
	}

	return matchesLeft;
}

void PyramidSolitaire::endGame() {
	string playerInp;

	gameRunning = false;
	console.displayText("No Matches Left!", "37");

	displayText("y to play again, n to return to menu", "37");
	getline(cin, playerInp);

	if (playerInp == "y") {
		newGame();
	}
	else {

	}
}
