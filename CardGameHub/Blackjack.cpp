#include "Blackjack.h"

Blackjack::Blackjack() {
	setUpGamemode(2, 2, " has gone bust!",
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
}

void Blackjack::playersInput() {
	string action;

	for (auto &player : getAllPlayers())
	{
		action = "";

		while (action != "s" or "b")
		{
			if (&player == mainPlayer)
			{
				displayText(player.getName() + ", Do you want to stand(s)? or hit(h)?", "37");
				getline(cin, action);
			}
			else
			{
				displayText(player.getName() + " is thinking...", "37");
				Sleep(2000);

				//Hits if NPCs value is lower than 12
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
				}
				else if (player.getHandValue() == 21)
				{
					win(player);
					break;
				}

				listAllPlayersHands(1);
			}
		}
	}

	checkForWin();
}

