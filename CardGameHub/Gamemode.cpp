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

	dealer = &players[1];

	mainPlayer = &players[0];

	//dealer = &players.front();
	//mainPlayer = &players.back();

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
	string playersNames;

	for (auto player : players) {
		playersNames += "          ";
		playersNames += player.getName();
	}

	console.displayText(playersNames, "37");

	string currentCardLine;

	for (int i = 0; i < 2; i++) {
		currentCardLine == "";
		currentCardLine += "          ";

		for (auto player : players) {

		}
	}

	*/
}

vector<player>& Gamemode::getAllPlayers() {
	return players;
}

void Gamemode::bustPlayer(player& player) {
	console.displayText(player.getName() + playerOutText, "37");
	bustPlayers.push_back(player);

	player.beaten();
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
