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
	newHands();
	Sleep(1000);
	listAllPlayersHands(1);
	playersInput();

	hits = 0;
}

void Blackjack::checkForWin() {
	player currentWinner = getPlayersUpForWinning()[0];

	for (auto& player : getPlayersUpForWinning()) {
		if (player.getHandValue(blackjack) > currentWinner.getHandValue(blackjack)) {
			currentWinner = player;
		}
	}

	listAllPlayersHands(blackjack);

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

			while (action != "s" or player.isOut() == true) {

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

					cout << player.getHandValue(blackjack) << endl;
					if (player.getHandValue(blackjack) > 21)
					{
						bustPlayer(player);
					}
					else if (player.getHandValue(blackjack) == 21)
					{
						putPlayerUpForWinning(player);
						checkForWin();
					}

					listAllPlayersHands(blackjack);
				}
			}

			if (action == "s")
			{
				putPlayerUpForWinning(player);
				player.setOutStatus(true);
			}

			listAllPlayersHands(1);
		}
	}

	checkForWin();
}

