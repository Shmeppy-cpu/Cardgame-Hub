#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "player.h"
#include "Gamemode.h"
#include "Blackjack.h"
#include "ConsoleManager.h"
#include "PyramidSolitaire.h"

int main()
{
	//Set the seed for random numbers to time to make it different.
	srand(1);
	srand(time(0));

	//set the color for the background
	system("Color 60");

	string playerChoice = "b";
	ConsoleManager console;

	string logo = R"(
 ____                       __       __  __           __        
/\  _`\                    /\ \     /\ \/\ \         /\ \       
\ \ \/\_\     __     _ __  \_\ \    \ \ \_\ \  __  __\ \ \____  
 \ \ \/_/_  /'__`\  /\`'__\/'_` \    \ \  _  \/\ \/\ \\ \ '__`\ 
  \ \ \L\ \/\ \L\.\_\ \ \//\ \L\ \    \ \ \ \ \ \ \_\ \\ \ \L\ \
   \ \____/\ \__/.\_\\ \_\\ \___,_\    \ \_\ \_\ \____/ \ \_,__/
    \/___/  \/__/\/_/ \/_/ \/__,_ /     \/_/\/_/\/___/   \/___/ 
		)";

	while (playerChoice != "") {
		console.clearConsole();


		//display the card hub logo
		cout << logo << endl;

		//display a line under the logo
		for (int i = 0; i < 120; i++) {
			cout << "_";
		}
		cout << endl;

		//ask the player for input on what game to play
		console.displayText("(b) and enter for blackjack, (p) and enter for pyramid solitaire, any other key and enter to close", "37");
		getline(cin, playerChoice);

		if (playerChoice == "b") {
			Blackjack blackjack;
		}
		else if (playerChoice == "p") {
			PyramidSolitaire pyramid;
		}
		else {
			exit(0);
		}
	}
}