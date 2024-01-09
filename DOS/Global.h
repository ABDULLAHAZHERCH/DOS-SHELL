#pragma once

#include<iostream>
#include<windows.h>
#include<iomanip>
#include<chrono>
#include<ctime>
#include<conio.h>
#include<regex>

using namespace std;

string DEFAULT_PATH = "V:\\";
char DEFAULT_PROMPT = '>';
string VERSION = "CHAUDHARY SHELL SYSTEM [Version 10.0.22631.2861]";
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setCursorPosition(int x, int y, int color)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoXY(int x, int y)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = y;
	scrn.Y = x;
	SetConsoleCursorPosition(hOuput, scrn);
}
void color(int k)
{
	if (k > 255)
	{
		k = 1;
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);

}
string ToLower(string command)
{
	for (int ri = 0; ri < command.size(); ri++)
	{
		if (65 <= command[ri] and command[ri] <= 90)
		{
			command[ri] = command[ri] + 32;
		}
	}
	return command;
}
string date_time()
{
	auto currentTime = chrono::system_clock::now();
	time_t current_time = chrono::system_clock::to_time_t(currentTime);

	tm localTime;
	localtime_s(&localTime, &current_time);

	char buffer[80];
	strftime(buffer, sizeof(buffer), "%d/%m/%Y %I:%M:%S %p", &localTime);

	string time = buffer;

	return time;
}
string PostSpaces(string s)
{
	regex pattern("\\s+$");
	return regex_replace(s, pattern, "");
}
string PreSpaces(string& inputString)
{
	regex pattern("^\\s*");
	return regex_replace(inputString, pattern, "");
}
int GetArrowKey()
{
	int ch = _getch();
	if (ch == 0 || ch == 0xE0)
	{
		return _getch();
	}
	else
	{
		return ch;
	}
}
bool CheckForBackSlashes(string name)
{
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] == '\\')
		{
			return false;
		}
	}
	return true;
}

void Instructions()
{
	system("cls");
	cout << "COMMAND                                            DESCRIPTION" << endl
		<< endl
		<< endl;
	cout << "ATTRIB  "
		<< "                "
		<< "Displays file (name provided as input) attributes." << endl;
	cout << "CD      "
		<< "                "
		<< "Displays the name of or changes the current directory. See details below. " << endl;
	cout << "CD.     "
		<< "                "
		<< "Prints working directory (i.e. your current directory in your tree structure) " << endl;
	cout << "CD..    "
		<< "                "
		<< "Change directory to previous directory " << endl;
	cout << "CD\\    "
		<< "                "
		<< " Changes directory to root directory (i.e. V:\\>)" << endl;
	cout << "CONVERT "
		<< "                "
		<< "Asks two types and converts extension of all files of one type to another type." << endl;
	cout << "COPY    "
		<< "                "
		<< "Copies one file in the current directory to another location (directory). See details below." << endl;
	cout << "CREATE  "
		<< "                "
		<< "Creates a file with the name provided and allows the user to enter contents of the file." << endl;
	cout << "DEL     "
		<< "                "
		<< "Delete a file whose name is provided in input." << endl;
	cout << "DIR     "
		<< "                "
		<< "Displays a list of files and subdirectories in a directory." << endl;
	cout << "EDIT    "
		<< "                "
		<< "Opens a file (loads into a linked list) and allows the user to edit and save the contents of the file." << endl;
	cout << "EXIT    "
		<< "                "
		<< "Quits the program" << endl;
	cout << "FIND    "
		<< "                "
		<< "Searches for a file in your current virtual directory whose name is provided as input." << endl;
	cout << "FINDF   "
		<< "                "
		<< "Searches for a text string in the currently open file or the file whose name is provided as input." << endl;
	cout << "FINDSTR "
		<< "                "
		<< "Searches for strings in all files of your current virtual directory, prints names of files with the string" << endl;
	cout << "FORMAT  "
		<< "                "
		<< "Formats the current virtual directory i.e. empties the current directory and all subdirectories." << endl << endl;
	cout << "HELP    "
		<< "                "
		<< "Provides Help information for all these commands." << endl;
	cout << "LOADTREE"
		<< "                "
		<< "Load a given tree in your tree structure. Given tree is in a file named tree.txt	" << endl;
	cout << "MKDIR   "
		<< "                "
		<< "Creates a virtual directory." << endl;
	cout << "MOVE    "
		<< "                "
		<< "Moves one file (whose name is provided as input) from one directory to another               directory." << endl;
	cout << "PPRINT  "
		<< "                "
		<< "Adds a text file to the priority based print queue, and displays the current priority queue. " << endl;
	cout << "PROMPT  "
		<< "                "
		<< "Changes the Windows command prompt (for example from V:\\> to V$)." << endl;
	cout << "PRINT   "
		<< "                "
		<< "Adds a text file to the print queue, and displays the current queue. " << endl;
	cout << "PQUEUE  "
		<< "                "
		<< "Shows current state of the priority based print queue, with time left for each element" << endl;
	cout << "PWD     "
		<< "                "
		<< "Prints working directory" << endl;
	cout << "QUEUE   "
		<< "                "
		<< "Shows current state of the print queue, with time left for each element" << endl;
	cout << "RENAME  "
		<< "                "
		<< "Renames a file whose current and new name is provided as input." << endl;
	cout << "RMDIR   "
		<< "                "
		<< "Removes a directory along with its contents. Consider setting the respective sibling links " << endl;
	cout << "SAVE    "
		<< "                "
		<< "Saves the currently open file to disk.TREE Displays the complete directory structure.VER Displays the version of your program." << endl;

	cout << endl << "Press ENTER to Go back TO SHELL.....";
	cin.get();
}