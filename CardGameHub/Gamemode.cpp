#include "Gamemode.h"
#include "ConsoleManager.h"

Gamemode::Gamemode() {
}

void Gamemode::setUpGamemode(int nPlayers, int nHandCount, string nPlayerOutText, string nLogo) {
	//Assigns how players there are and how many cards they start with
	howManyPlayers = nPlayers;
	howManyCardsPerStartingHand = nHandCount;
	playerOutText = nPlayerOutText;

	deck.shuffleDeck();

	//Creates okayers and assigns them random names
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
	//print the gamemodes logo to the screen followed by a line

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

vector<player>& Gamemode::getAllPlayers() {
	return players;
}

void Gamemode::bustPlayer(player& player) {
	//display the player as out and then set their status as out
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
	//display the win state of the game
	if (tie == true) {
		console.displayText("Tie!", "37");
	}
	else {
		console.displayText(winner.getName() + " won!", "37");
	}
}

void Gamemode::putPlayerUpForWinning(player player) {
	//set the player possible win status to true
	player.setPossibleWinStatus(true);
}

int Gamemode::getMostHeldCards() {
	int mostHeldCards = 0;

	//Checks the size of each players hands agaisnt each otehr to determine which one has the most
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
