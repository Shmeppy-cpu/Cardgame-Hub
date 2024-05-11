#include "ConsoleManager.h"
#include <Windows.h>

/*
TEXT
	Black - 30
	Red - 31
	Green - 32
	Yellow - 33
	Blue - 34
	Magneta - 35
	Cyan - 36
	White - 37

BACKGROUND
	Black - 40
	Red - 41
	Green - 42
	Yellow - 43
	Blue - 44
	Magneta - 45
	Cyan - 46
	White - 47

*/

ConsoleManager::ConsoleManager() {
}

void ConsoleManager::displayText(string text, string colorCode) {
	cout << endl;

	int halfSize = size(text) / 2;
	int delay = 0;

	//adds the correct number of spaces to the screen so the text displays in the middle of the screen
	string spaces;
	for (int i = 0; i < 56 - halfSize; i++) {
		spaces += " ";
	}

	cout << spaces;

	//add the extra funky elements needed for the colorcode to work
	colorCode = "\033[" + colorCode + "m";

	//add each character of the text to the screen indivudally incase I decided to add a delay between them
	for (auto i : text) {
		Sleep(delay);
		cout << colorCode << i;
	}

	cout << endl;
}

void ConsoleManager::displayAlongLine(vector<string> linesOfText, vector<string> colorCodes) {
	//divides the size of the screen by how many lines of text need to be added too it so it knows how much space each one has
	int spacePerText = 112 / size(linesOfText);

	string colorCode = "";
	int colorCodeIndex = 0;

	for (auto text : linesOfText) {
		//adds the spaces required to center it in the middle of its block of the screen
		for (int i = 0; i < (spacePerText - (size(text))) / 2; i++) {
			cout << " ";
		}

		//adds the text to screen with corresponding colorCode
		colorCode = "\033[" + colorCodes[colorCodeIndex] + "m";
		cout << colorCode << text;

		//adds the rest of the spaces to fill out its block of the screen before the next live of text
		for (int i = 0; i < (spacePerText - (size(text))) / 2; i++) {
			cout << " ";
		}

		colorCodeIndex++;
	}

	cout << endl;
}

void ConsoleManager::displayAlongLineWithSetGap(vector<string> linesOfText, vector<string> colorCodes, int gap) {
	//divides the size of the screen by how many lines of text need to be added too it so it knows how much space each one has
	int spacePerText = 112 / size(linesOfText) + 0;

	string colorCode = "";
	int colorCodeIndex = 0;

	//loop to determine the size of all the text its adding to the screen, including the set gap
	int sizeOfString = 0;
	for (string text : linesOfText) {
		sizeOfString += size(text) + gap;
	}

	//adds the required spaces to center that group of text
	for (int i = 0; i < (56 - sizeOfString / 2) + gap; i++) {
		cout << " ";
	}
		 
	for (auto text : linesOfText) {
		//displays a line of text
		colorCode = "\033[" + colorCodes[colorCodeIndex] + "m";
		cout << colorCode << text;

		//adds the set gap after the text
		for (int i = 0; i < gap; i++) {
			cout << " ";
		}

		colorCodeIndex++;
	}

	cout << endl;
}

void ConsoleManager::clearConsole() {
	//clears the screen
	system("cls");
}
