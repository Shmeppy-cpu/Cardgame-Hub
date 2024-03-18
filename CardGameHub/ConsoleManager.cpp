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
	Font.FontWeight = 700;

	//SetCurrentConsoleFontEx(ReadConsoleOutput(), NULL, &Font);
}

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

	cout << endl;
}

void ConsoleManager::displayAlongLine(vector<string> linesOfText, vector<string> colorCodes) {
	int spacePerText = 112 / size(linesOfText) + 0;
	string colorCode = "";
	int colorCodeIndex = 0;

	for (auto text : linesOfText) {
		for (int i = 0; i < (spacePerText - (size(text))) / 2; i++) {
			cout << " ";
		}

		colorCode = "\033[" + colorCodes[colorCodeIndex] + "m";
		cout << colorCode << text;

		for (int i = 0; i < (spacePerText - (size(text))) / 2; i++) {
			cout << " ";
		}

		colorCodeIndex++;
	}

	cout << endl;
}

void ConsoleManager::displayAlongLineWithSetGap(vector<string> linesOfText, vector<string> colorCodes, int gap) {
	int spacePerText = 112 / size(linesOfText) + 0;
	string colorCode = "";
	int colorCodeIndex = 0;

	int sizeOfString = 0;
	for (string text : linesOfText) {
		sizeOfString += size(text) + gap;
	}

	for (int i = 0; i < (56 - sizeOfString / 2) + gap; i++) {
		cout << " ";
	}
		 
	for (auto text : linesOfText) {
		colorCode = "\033[" + colorCodes[colorCodeIndex] + "m";
		cout << colorCode << text;

		for (int i = 0; i < gap; i++) {
			cout << " ";
		}

		colorCodeIndex++;
	}

	cout << endl;
}

void ConsoleManager::clearConsole() {
	system("cls");
}
