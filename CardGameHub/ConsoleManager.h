#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

#include <vector>

using namespace std;

using namespace std;

class ConsoleManager
{
private:
	vector<string> textOnScreen;

	_CONSOLE_FONT_INFOEX Font;

public:
	ConsoleManager();

	void displayText(string text, string colorCode);

	void displayAlongLine(vector<string> linesOfText, vector<string> colorCodes);

	void displayAlongLineWithSetGap(vector<string> linesOfText, vector<string> colorCodes, int gap);

	void clearConsole();
};

