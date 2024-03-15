#include "Gamemode.h"
#include "ConsoleManager.h"

Gamemode::Gamemode() {
}

void Gamemode::setUpGamemode(int nPlayers, int nHandCount, string nPlayerOutText, string nLogo) {
	howManyPlayers = nPlayers;
	howManyCardsPerStartingHand = nHandCount;
	playerOutText = nPlayerOutText;

	deck.fillDeck();
	deck.shuffleDeck();

	for (int i = 0; i < howManyPlayers; i++) {
		player newPlayer;
		newPlayer.assignRandomName();
		players.push_back(newPlayer);
	}

	//Set the dealer and player pointers to the first 2 players in the list of players
	dealer = &players[1];

	mainPlayer = &players[0];
	players[0].setAsMainPlayer();

	dealer->setName("Dealer");
	mainPlayer->setName("You");
	mainPlayer->setAsMainPlayer();

	logo = nLogo;
}

void Gamemode::printLogo() {
	cout << "\033[37m" << logo << endl;

	cout << endl;
	for (int i = 0; i < 120; i++) {
		cout << "_";
	}
	cout << endl;
}

void Gamemode::newHands() {
	gameRunning = true;

	//Return all out players to the game
	for (auto& player : bustPlayers) {
		player.setOutStatus(false);
		//players.push_back(player);
	}	
	for (auto& player : playersUpForWinning) {
		player.setOutStatus(false);
		//players.push_back(player);
	}
	bustPlayers.clear();
	playersUpForWinning.clear();

	//Return all players cards to the deck
	for (auto& player : players) {
		if (player.getSizeOfHand() > 0) {
			for (int i = 0; i < player.getSizeOfHand(); i++) {
				deck.returnCardToDeck(player.getTopCard());
			}
		}
	}

	deck.shuffleDeck();

	//Hand out the correct amount of cards to all players
	if (size(players) > 0) {
		for (auto& player : players) {
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
	bustPlayers.push_back(player);

	player.setOutStatus(true);
}

vector<player>& Gamemode::getBustPlayers() {
	return bustPlayers;
}

void Gamemode::dealCard(player& player) {
	player.giveCard(deck.getTopCard());
}

void Gamemode::displayText(string text, string colorCode) {
	console.displayText(text, colorCode);
}

void Gamemode::win(player winnner) {
	gameRunning = false;
	listAllPlayersHands(0);

	console.displayText(winnner.getName() + " won!", "37");
}

void Gamemode::putPlayerUpForWinning(player player) {
	playersUpForWinning.push_back(player);
}

vector<player>& Gamemode::getPlayersUpForWinning() {
	return playersUpForWinning;
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
