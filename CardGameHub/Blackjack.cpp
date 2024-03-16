#include "Blackjack.h"

Blackjack::Blackjack() {
	setUpGamemode(3, 2, " has gone bust!",
		R"(                                                                                                      
    ,---,.    ,--,                                   ,-.                 .-- -.' \                                ,-.  
  ,'  .'  \ ,--.'|                               ,--/ /|                 |    |   :                           ,--/ /|  
,---.' .' | |  | :                             ,--. :/ |                 :    ;   |                         ,--. :/ |  
|   |  |: | :  : '                             :  : ' /                  :        |                         :  : ' /   
:   :  :  / |  ' |       ,--.--.       ,---.   |  '  /                   |    :   :   ,--.--.       ,---.   |  '  /    
:   |    ;  '  | |      /       \     /     \  '  |  :                   :           /       \     /     \  '  |  :    
|   :     \ |  | :     .--.  .-. |   /    / '  |  |   \                  |    ;   | .--.  .-. |   /    / '  |  |   \   
|   |   . | '  : |__    \__\/: . .  .    ' /   '  : |. \             ___ l           \__\/: . .  .    ' /   '  : |. \  
'   :  '; | |  | '.'|   ," .--.; |  '   ; :__  |  | ' \ \          /    /\    J   :  ," .--.; |  '   ; :__  |  | ' \ \ 
|   |  | ;  ;  :    ;  /  /  ,.  |  '   | '.'| '  : |--'          /  ../  `..-    , /  /  ,.  |  '   | '.'| '  : |--'  
|   :   /   |  ,   /  ;  :   .'   \ |   :    : ;  |,'             \    \         ; ;  :   .'   \ |   :    : ;  |,'     
|   | ,'     ---`-'   |  ,     .-./  \   \  /  '--'                \    \      ,'  |  ,     .-./  \   \  /  '--'       
`----'                 `--`---'       `----'                        "---....--'     `--`---'       `----'         
)"
		);

	newRound();
}

void Blackjack::newRound() {
	gameRunning = true;
	newHands();
	displayPlayersHands(1);
	playersInput();

	hits = 0;
}

void Blackjack::checkForWin() {
	gameRunning = false;
	player currentWinner;
	int currentHighestHand = 0;

	for (player player : getAllPlayers()) 
	{
		if (player.isUpForWinning() == true and player.getHandValue(blackjack) > currentHighestHand)
		{
			currentWinner = player;
			currentHighestHand = player.getHandValue(blackjack);
		}
	}

	displayPlayersHands(1);

	win(currentWinner);

	string playAgain;
	displayText("Do you want to play again? y/n", "37");
	getline(cin, playAgain);

	if (playAgain == "n") {
		exit(0);
	}
	else {
		newRound();
	}
}

void Blackjack::playersInput() {
	string action;

	for (auto &player : getAllPlayers())
	{
		if (gameRunning == true)
		{
			action = "";

			while (action != "s") {
				if (player.getHandValue(blackjack) == 21)
				{
					putPlayerUpForWinning(player);
					checkForWin();
				}

				if (&player == mainPlayer)
				{
					displayText(player.getName() + ", Do you want to stand(s)? or hit(h)?", "37");
					getline(cin, action);
				}
				else
				{
					displayText(player.getName() + " is thinking...", "37");
					Sleep(5000);

					//Hits if NPCs value is lower than 14
					if (player.getHandValue(blackjack) <= 14)
					{
						action = "h";
					}
					//Stands if it is higher than 17
					else if (player.getHandValue(blackjack) >= 18)
					{
						action = "s";
					}
					//If inbetween there is 50% chance whether it will hit or stand
					else
					{
						if ((0 + rand() % 1) == 1) {
							action = "h";
						}
						else
						{
							action = "s";
						}
					}
				}

				if (action == "h")
				{
					dealCard(player);

					if (player.getHandValue(blackjack) > 21)
					{
						bustPlayer(player);
						action = "s";
					}
					else if (player.getHandValue(blackjack) == 21)
					{
						//putPlayerUpForWinning(player);
						player.setPossibleWinStatus(true);
						checkForWin();
						action = "s";
					}

					displayPlayersHands(1);
				}
			}

			if (action == "s" and player.isOut() == false)
			{
				//putPlayerUpForWinning(player);
				player.setPossibleWinStatus(true);
			}

			displayPlayersHands(1);
		}
	}

	checkForWin();
}

void Blackjack::displayPlayersHands(int shownCards) {
	console.clearConsole();
	printLogo();

	//creates string to store information shown after the players name
	string playerInfo;

	for (player player : getAllPlayers()) {
		//starts off player info with the players name
		playerInfo = ">-" + player.getName();

		if (gameRunning == false) {
			playerInfo += " -" + to_string(player.getHandValue(blackjack));
		}
		else {
			if (player.isUpForWinning()) {
				if (player.getIsMainPlayer()) {
					playerInfo += " -stood -" + to_string(player.getHandValue(blackjack));
				}
				else {
					playerInfo += " -stood -HIDDEN";
				}
			}
			else if (player.isOut()) {
				playerInfo += " -bust -" + to_string(player.getHandValue(blackjack));
			}
			else {
				if (player.getIsMainPlayer()) {
					playerInfo += " -" + to_string(player.getHandValue(blackjack));
				}
				else {
					playerInfo += " -HIDDEN";
				}
			}
		}

		playerInfo += "-<";

		 
		console.displayText(playerInfo, "37");

		vector<string> cardsAsText;
		vector<string> colorCodesOfCards;

		int hiddenCards;

		if (player.getIsMainPlayer() == true or gameRunning == false)
		{
			hiddenCards = 0;
		}
		else
		{
			hiddenCards = player.getSizeOfHand() - shownCards;
		}

		for (Card card : player.getHand())
		{

			if (hiddenCards > 0)
			{
				cardsAsText.push_back(">-HIDDEN-<");
				hiddenCards--;
			}
			else
			{
				cardsAsText.push_back(card.getDisplayForm());
			}

			colorCodesOfCards.push_back("37");
		}

		console.displayAlongLine(cardsAsText, colorCodesOfCards);
	}
}

