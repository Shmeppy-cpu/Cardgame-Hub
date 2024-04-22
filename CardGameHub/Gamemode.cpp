#include "Gamemode.h"
#include "ConsoleManager.h"

Gamemode::Gamemode() {
}

void Gamemode::setUpGamemode(int nPlayers, int nHandCount, string nPlayerOutText, string nLogo) {
	howManyPlayers = nPlayers;
	howManyCardsPerStartingHand = nHandCount;
	playerOutText = nPlayerOutText;

	deck.shuffleDeck();

	for (int i = 0; i < howManyPlayers; i++) {
		player newPlayer;
		newPlayer.assignRandomName();
		players.push_back(newPlayer);
	}

	//Set the dealer and player pointers to the first 2 players in the list of players
	players[0].setAsMainPlayer();
	mainPlayer = &players[0];
	mainPlayer->setName("You");

	if (howManyPlayers > 1) {
		dealer = &players[size(players) - 1];

		dealer->setName("Dealer");
	}

	logo = nLogo;
}

void Gamemode::printLogo() {
	cout << "\033[37m" << logo << endl;

	for (int i = 0; i < 120; i++) {
		cout << "_";
	}
	cout << endl;
}

void Gamemode::newHands() {
	gameRunning = true;

	//Return all out players to the game
	for (player& player : getAllPlayers()) {
		player.setOutStatus(false);
		player.setPossibleWinStatus(false);
	}

	//Return all players cards to the deck
	int handSize;
	for (player& player : players) {
		handSize = player.getSizeOfHand();
		for (int i = 0; i < handSize; i++) {
			deck.returnCardToDeck(player.getTopCard());
		}
	}

	deck.shuffleDeck();

	//Hand out the correct amount of cards to all players
	if (size(players) > 0) {
		for (player& player : players) {
			for (int i = 0; i < howManyCardsPerStartingHand; i++) {
				dealCard(player);
			}
		}
	}
}

void Gamemode::listAllPlayersHands(int hiddenCards) {
	console.clearConsole();
	printLogo();

	//hiddenCards = 0;
	
	for (auto& player : players) {
		//hides any cards it needs to for all the players except the user
		if (&player != mainPlayer) {
			player.listHand(hiddenCards);
		}
		else {
			player.listHand(0);
		}
	}
	
	/*
	vector<vector<string>> lines;

	vector<vector<Card>> playerCards;
	vector<vector<string>> playerCardsVisual;

	lines.push_back({});
	for (auto player : getAllPlayers()) {
		lines[0].push_back(player.getName() + " - " + player.handValueDisplay());
		playerCards.push_back(player.getHand());
	}

	string lineText;
	int playersHiddenCards = 0;

	int playerCardsIndex = 0;
	for (vector<Card> cards : playerCards) {
		playerCardsVisual.push_back({});
		playersHiddenCards = hiddenCards;

		for (Card card : cards) {
			if (playersHiddenCards > 0 and playerCardsIndex != 0) {
				playerCardsVisual[playerCardsIndex].push_back("-<HIDDEN>-");
				playersHiddenCards--;
			}
			else {
				playerCardsVisual[playerCardsIndex].push_back(card.getDisplayForm());
			}

			reverse(playerCardsVisual[playerCardsIndex].begin(), playerCardsVisual[playerCardsIndex].end());
		}

		playerCardsIndex++;
	}

	for (int i = 0; i <= getMostHeldCards(); i++) {
		vector<string> newLine;

		for (vector<string> cards : playerCardsVisual) {
			if (i >= size(cards)) {
				newLine.push_back("");
			}
			else {
				newLine.push_back(cards[i]);
			}
		}

		lines.push_back(newLine);
	}

	for (auto line : lines) {
		console.displayAlongLine(line);
	}

	*/
}

vector<player>& Gamemode::getAllPlayers() {
	return players;
}

void Gamemode::bustPlayer(player& player) {
	console.displayText(player.getName() + playerOutText, "37");
	player.setOutStatus(true);
}

void Gamemode::dealCard(player& player) {
	player.giveCard(deck.getTopCard());
}

void Gamemode::displayText(string text, string colorCode) {
	console.displayText(text, colorCode);
}

void Gamemode::win(player winner, bool tie) {
	//listAllPlayersHands(0);

	if (tie == true) {
		console.displayText("Tie!", "37");
	}
	else {
		console.displayText(winner.getName() + " won!", "37");
	}
}

void Gamemode::putPlayerUpForWinning(player player) {
	player.setPossibleWinStatus(true);
}

int Gamemode::getMostHeldCards() {
	int mostHeldCards = 0;

	for (auto player : getAllPlayers()) {
		if (player.getSizeOfHand() > mostHeldCards) {
			mostHeldCards = player.getSizeOfHand();
		}
	}

	return mostHeldCards;
}

Deck& Gamemode::getDeck() {
	return deck;
}

Card Gamemode::getDeckTopCard() {
	return deck.getTopCard();
}

void Gamemode::returnCardToDeck(Card card) {
	deck.returnCardToDeck(card);
}
