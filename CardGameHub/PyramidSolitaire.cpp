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

	//fill and shuffle the deck for each new game
	getDeck().fillDeck();
	getDeck().shuffleDeck();

	buildPyramid();
	playerInput();
}

void PyramidSolitaire::buildPyramid() {
	Pyramid.clear();
	clearedPyramid.clear();

	//build the pyramid by adding cards to the collums, with one less card for each collum, the first collum has 7 cards, the next has 6, etc...
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

	//reverse the vectors so it displays as pyramid rather than inverted pyramid
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

	//iterate through the collums to get the individual row vectors
	for (vector<Card> Row : Pyramid) {
		cardI = 0;
		line.clear();
		colorsOfCards.clear();
		colorsOfInputs.clear();
		inputs.clear();

		//iterate through each card in the row 
		for (Card card : Row) {
			//if that spot in the cleared pyramid is true, add string to the line as an empty card box and add an empty input prompt below it
			if (clearedPyramid[rowI][cardI] == true)
			{
				line.push_back("[ .......... ]");
				colorsOfCards.push_back("37");

				inputs.push_back("              ");
				colorsOfInputs.push_back("37");
			}
			//otherwise dadd string to the line of card in its display form and add an input prompt with its row and collum codes below it.
			else {
				line.push_back(card.getDisplayForm());
				colorsOfCards.push_back(card.getColorCode());

				inputs.push_back("     (" + to_string(rowI) + "" + to_string(cardI) + ")     ");
				colorsOfInputs.push_back("37");
			}

			cardI++;
		}

		//display the line of cards with their prompts
		console.displayAlongLineWithSetGap(line, colorsOfCards, 2);
		console.displayAlongLineWithSetGap(inputs, colorsOfInputs,2);

		rowI++;
	}

	cout << endl;
}

void PyramidSolitaire::playerInput() {
	string playerInp;

	match_state matchState;

	bool newCard = true;
	bool returnCurrentCardToDeck = false;

	while (gameRunning == true) {
		//freshly display the pyramid
		console.clearConsole();
		displayPyramid();

		//if new card is true, then get a new card, if return current card to deck is true than return it to the deck
		if (newCard == true) {
			if (returnCurrentCardToDeck == true)
			{
				returnCardToDeck(currentCard);
			}

			currentCard = getDeckTopCard();
		}

		//if there are no possible matches left end the game
		if (howManyMatchesLeft() <= 0) {
			endGame();
		}

		//display how many cards the player has, along with the current card followed by the amount of matches left
		console.displayAlongLineWithSetGap({to_string(getDeck().getSize()), currentCard.getDisplayForm(), "enter code below card to try and match, just press enter for new card "}, {"37", currentCard.getColorCode(), "37"}, 5);
		console.displayText("Potential Matches Left - " + to_string(howManyMatchesLeft()), "37");
		getline(cin, playerInp);

		//if the players input isnt empty and has the 2 characters required to try and match a card
		if ((playerInp != "") and (size(playerInp) == 2)) {
			//cout << matchCards(playerInp, currentCard) << endl;

			//run the players current card and their input through the match function
			matchState = matchCards(playerInp, currentCard);

			switch (matchState)
			{
			case(matchedBoth):
			{
				//if the cards match with each other than set new card to true so the player gets a new card, and set return current card to deck to false since its been matched out and shouldn't be returned
				newCard = true;
				returnCurrentCardToDeck = false;
				break;
			}
			case(matchedPlayerCard):
			{
				//if only the players card matches (E.G. it is a king) than set new card to true
				newCard = true;
				returnCurrentCardToDeck = false;
				break;
			}
			case(matchedPyramidCard):
			{
				//if only the pyramid card matches (E.G. it is a king) than set new card to false
				newCard = false;
				returnCurrentCardToDeck = false;
				break;
			}
			case(noMatch):
			{
				//if there is no match than set new card to false
				newCard = false;
				returnCurrentCardToDeck = false;
				break;
			}
				break;
			}
		}
		else {
			//if the player just presses enter to geta  new card, set new card to true and return their current card to the deck
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
		//only check if the given card can be matched at all
		if (canCardBeMatched(row, collum))
		{
			//create a card variable to store the card at the given position
			Card card = Pyramid[row][collum];

			if (card.getNumValue(solitaire) + playerCard.getNumValue(solitaire) == 13)
			{
				//if the cards combined value is 13 than they are both matched
				console.displayAlongLineWithSetGap({ playerCard.getDisplayForm(), " and ", card.getDisplayForm(), " match!" }, 
					{ playerCard.getColorCode(), "37", card.getColorCode(), "37" }, 2);
				removeCardFromPyramid(row, collum);
				matchState = matchedBoth;
			}
			else
			{
				if (card.getNumValue(solitaire) == 13)
				{
					//if the value of the pyramid card is 13(king), then it its matched
					console.displayAlongLineWithSetGap({ card.getDisplayForm(), " clears itself!" }, 
						{ card.getColorCode(), "37" }, 2);
					removeCardFromPyramid(row, collum);
					matchState = matchedPyramidCard;
				}

				if (playerCard.getNumValue(solitaire) == 13)
				{
					//if the value of the players card is 13(king), then it is matched
					console.displayAlongLineWithSetGap({ playerCard.getDisplayForm(), " clears itself!" }, { playerCard.getColorCode(), "37" }, 2);


					if (matchState == matchedPyramidCard) {
						//if the pyramid card was also matched than they are both matched
						matchState = matchedBoth;
					}
					else {
						matchState = matchedPlayerCard;
					}
				}

				//if the cards don't match together and don't match individually either then there is no match
				if ((playerCard.getNumValue(solitaire) != 13) and (card.getNumValue(solitaire) != 13)) {
					console.displayAlongLineWithSetGap({ playerCard.getDisplayForm(), " and ", card.getDisplayForm(), " don't match..." }, 
						{ playerCard.getColorCode(), "37", card.getColorCode(), "37" }, 2);
					matchState = noMatch;
				}
			}
		}
		else
		{
			//if the given card is within bounds but can't be matched with let the player know
			if (row < 7 and collum <= row) {
				Card card = Pyramid[row][collum];
				console.displayAlongLineWithSetGap({ "Can't match with ", card.getDisplayForm(), " yet..." }, { "37", card.getColorCode(), "37" }, 2);
			}
			else {
				//if the given card is out of bounds or already matched let the player know
				console.displayText("No card there to match with", "37");
			}
		}
	}

	//short delay to allow the player to read
	Sleep(2000);

	return matchState;
}

void PyramidSolitaire::removeCardFromPyramid(int row, int collum) {
	//set the given pyramid position to true in the clearedPyramid
	clearedPyramid[row][collum] = true;
}

bool PyramidSolitaire::canCardBeMatched(int row, int collum) 
{
	if (row == 6 and collum <= 6)
	{
		//if the card is on the final row and within the bounds return true 
		return true;
	}
	else if (row < 6 and collum <= row) {
		//if the card is already cleared return false
		if (clearedPyramid[row][collum] == true) {
			return false;
		}
		else {
			if (clearedPyramid[row + 1][collum] == true and clearedPyramid[row + 1][collum + 1] == true) {
				//if the two cards below the given one are cleared than return true
				return true;
			}
			else {
				return false;
			}
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

	//iterate through each card in the pyramid
	for (vector<Card> collumCards : Pyramid) {
		for (Card Pcard : collumCards) {
			//if the pyramid card can be matched then loop throigh all the players cards to compare
			if (canCardBeMatched(row, collum) == true) {
				for (Card card : playerCards) {
					//if the players card and pyramid card add to 13 or the pyramind card is equal to 13, add 1 to the amount of matches left
					if ((Pcard.getNumValue(solitaire) + card.getNumValue(solitaire) == 13) or (Pcard.getNumValue(solitaire) == 13)) {
						matchesLeft++;
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

	//display no matches left
	gameRunning = false;
	console.displayText("No Matches Left!", "37");

	//ask for players input on whether they want to play again or not
	displayText("y to play again, n to return to menu", "37");
	getline(cin, playerInp);

	if (playerInp == "y") {
		newGame();
	}
	else {

	}
}
