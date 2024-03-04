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

public:
	void displayText(string text, string colorCode);

	void displayAlongLine(vector<string> linesOfText);

	void clearConsole();
};

