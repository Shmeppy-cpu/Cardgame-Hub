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
	listAllPlayersHands(1);
	playersInput();

	hits = 0;
}

void Blackjack::checkForWin() {
	player currentWinner = getPlayersUpForWinning()[0];

	for (auto& player : getPlayersUpForWinning()) {
		if (player.getHandValue() > currentWinner.getHandValue()) {
			currentWinner = player;
		}
	}

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

			while (action != "s")
			{
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
					if (player.getHandValue() <= 14)
					{
						action = "h";
					}
					//Stands if it is higher than 17
					else if (player.getHandValue() >= 18)
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
					if (player.getHandValue() > 21)
					{
						bustPlayer(player);
						action = "s";
					}
					else if (player.getHandValue() == 21)
					{
						win(player);
					}

					listAllPlayersHands(1);
				}
			}

			if (player.isOut() == false)
			{
				putPlayerUpForWinning(player);
			}
		}
	}

	checkForWin();
}

