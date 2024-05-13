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

	//give each player new hands and begin the game again
	newHands();
	displayPlayersHands(1);
	playersInput();

	hits = 0;
}

void Blackjack::checkForWin() {
	gameRunning = false;

	bool tie = false;
	player currentWinner;
	int currentHighestHand = 0;

	//loop through each player, check they are up for winning and check if their habnd is higher than the current highest hand, if it is make them the current winner
	for (player player : getAllPlayers()) 
	{
		if (player.isUpForWinning() == true and player.getHandValue(blackjack) > currentHighestHand and player.getHandValue(blackjack) <= 21)
		{
			currentWinner = player;
			currentHighestHand = player.getHandValue(blackjack);
		} 
		else if (player.isUpForWinning() == true and player.getHandValue(blackjack) == currentHighestHand) {
			//if they are equal, make tie true so the win state is displayed as true
			tie = true;
		}
	}

	displayPlayersHands(1);

	//display win state
	win(currentWinner, tie);

	//get player input to see if they want to play again or try a diffrent game
	string playAgain;
	displayText("Do you want to play again? y/n", "37");
	getline(cin, playAgain);

	if (playAgain == "n") {
	}
	else {
		newRound();
	}
}

void Blackjack::playersInput() {
	//Creates a string to store the next action of the player and opponents
	string action;

	for (auto &player : getAllPlayers())
	{
		if (gameRunning == true)
		{
			//Sets the action to a defualt state for each player
			action = "";

			while (action != "s") {
				//If the players hand is valued at 21 they get set as possible winner before the game checks for a win
				if (player.getHandValue(blackjack) == 21)
				{
					putPlayerUpForWinning(player);
					checkForWin();
				}

				//If the current player is the user than ask for input on whether to hit or stand.
				if (&player == mainPlayer)
				{
					displayText(player.getName() + ", Do you want to hit(enter)? or stand(s & enter)?", "37");
					getline(cin, action);
				}
				//If the current player is the dealer
				else if (&player == dealer)
				{
					//delay for illusion of thought
					displayText(player.getName() + " is thinking...", "37");
					Sleep(5000);

					//Stand if hand is 17 or above like blackjack rules
					if (player.getHandValue(blackjack) >= 17)
					{
						action = "s";
					}
					//hit for anything else
					else 
					{
						action = "";
					}
				}
				//If the player is neither the user or dealer
				else
				{
					//delay for illusion of thought
					displayText(player.getName() + " is thinking...", "37");
					Sleep(5000);

					//Hits if NPCs value is lower than 14
					if (player.getHandValue(blackjack) <= 14)
					{
						action = "";
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
							action = "";
						}
						else
						{
							action = "s";
						}
					}
				}

				//if the players chosen action was hit
				if (action == "")
				{
					dealCard(player);

					//iof the players hand is above 21, defualt their next action to stand so they can't input anymore and bust them.
					if (player.getHandValue(blackjack) > 21)
					{
						bustPlayer(player);
						action = "s";
					}
					//if the players hand is 21, make them a possible winner and check for a win
					else if (player.getHandValue(blackjack) == 21)
					{
						putPlayerUpForWinning(player);
						action = "s";
						checkForWin();
					}

					displayPlayersHands(1);
				}
			}

			//If the player chooses to stand and hasn't been busted, make them a possible winner
			if (action == "s" and player.isOut() == false)
			{
				putPlayerUpForWinning(player);
			}

			displayPlayersHands(1);
		}
	}

	//Once all players have player, check for a win.
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
			//If players are no longer playing, freely show the value of the hand
			playerInfo += " -" + to_string(player.getHandValue(blackjack));
		}
		//for if the game is still running
		else {
			if (player.isUpForWinning()) {
				if (player.getIsMainPlayer()) {
					//if the player is up for winning and it is the player than show they are stood with their value.
					playerInfo += " -stood -" + to_string(player.getHandValue(blackjack));
				}
				else {
					//if the player is up for winning and is an NPC, then show they are stood with a hidden value
					playerInfo += " -stood -HIDDEN";
				}
			}
			else if (player.isOut()) {
				//If the player is out, show theyu are bust with their hand value.
				playerInfo += " -bust -" + to_string(player.getHandValue(blackjack));
			}
			else {
				if (player.getIsMainPlayer()) {
					//If the player is currently neither out or up for winning and is the user than show their hand value
					playerInfo += " -" + to_string(player.getHandValue(blackjack));
				}
				else {
					//If the player is currently neither out or up for winning and is an npc then hide their hand value
					playerInfo += " -HIDDEN";
				}
			}
		}

		playerInfo += "-<";

		//display the player and their info
		console.displayText(playerInfo, "37");

		vector<string> cardsAsText;
		vector<string> colorCodesOfCards;

		int hiddenCards;

		//If the player is the user or the game is over than set hiddenCards to 0 so all can be seen
		if (player.getIsMainPlayer() == true or gameRunning == false)
		{
			hiddenCards = 0;
		}
		else
		{
			//else set it to hiddenCards is equal to the players hand size minus the given amount of cards to be shown
			hiddenCards = player.getSizeOfHand() - shownCards;
		}

		for (Card card : player.getHand())
		{
			if (hiddenCards > 0)
			{
				//if not enough cards have been hidden yet, add hidden and a defualt color to cardTexts and cardColorCodes.
				cardsAsText.push_back(">-HIDDEN-<");
				colorCodesOfCards.push_back("37");
				hiddenCards--;
			}
			else
			{
				//if enough cards have been hidden, add the cards display form and its colorCode to cardTexts and cardColorCodes.
				cardsAsText.push_back(card.getDisplayForm());
				colorCodesOfCards.push_back(card.getColorCode());
			}

		}

		//display the cards of the player
		console.displayAlongLineWithSetGap(cardsAsText, colorCodesOfCards, 2);
	}
}

