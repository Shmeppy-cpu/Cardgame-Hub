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

void ConsoleManager::displayText(string text, string colorCode) {
	cout << endl;

	int halfSize = size(text) / 2;
	int delay;

	if (count(textOnScreen.begin(), textOnScreen.end(), text) > 0)
	{
		delay = 0;
	}
	else 
	{
		delay = 0;
		textOnScreen.push_back(text);
	}

	string spaces;
	for (int i = 0; i < 56 - halfSize; i++) {
		spaces += " ";
	}

	cout << spaces;

	colorCode = "\033[" + colorCode + "m";
	//cout << colorCode << newText << endl;

	for (auto i : text) {
		Sleep(delay);
		cout << colorCode << i;
	}
}

void ConsoleManager::displayAlongLine(vector<string> linesOfText) {
	int spacePerText = 112 / size(linesOfText) + 0;
	string colorCode = "";

	for (auto text : linesOfText) {
		for (int i = 0; i < (spacePerText - (size(text))) / 2; i++) {
			cout << " ";
		}

		//colorCode = "\033[" + colorCode + "m";
		cout << colorCode << text;

		for (int i = 0; i < (spacePerText - (size(text))) / 2; i++) {
			cout << " ";
		}
	}

	cout << endl;
}

void ConsoleManager::clearConsole() {
	system("cls");
}
