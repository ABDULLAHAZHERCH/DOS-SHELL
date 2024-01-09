#pragma once

#include<iostream>
#include<fstream>
#include<chrono>
#include<iomanip>
#include<sstream>
#include<stack>

#include"Global.h"

using namespace std;

class File
{
	string Name;
	string Time;
	string Path;
	string Extension;
	bool ReadOnly;

	// Create a TEXT file
	void createFile()
	{
		string fileName = Name + Extension;
		ofstream file(fileName);
		if (file.is_open())
		{
			cout << "Created a File : " << fileName;
			file.close();
		}
		else
			cout << "Error 101 : File NOT created";
	}
public:
	File(string name = "/0", string path = "", string extension = ".txt", bool readOnly = false)
	{
		this->Name = name;
		this->Extension = extension;
		this->Path = path;
		this->ReadOnly = readOnly;
		this->Time = date_time();
		createFile();
	}
	void SaveToFile(const string filename, const string& content)
	{
		ofstream file(filename);
		if (file.is_open())
		{
			file << content;
			file.close();
		}
		else
		{
			cout << "Unable to open file for saving: " << filename << "\n";
		}
	}
	void NavigateAndEditFile(string fileName)
	{
		SetConsoleTextAttribute(hConsole, 240);
		fstream file(fileName);
		if (!file.is_open())
		{
			cout << "File does not exist";
			return;
		}
		string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		file.close();
		int currentPosition = 0;
		int totalCols = 80;
		stack<string> undoStack;
		stack<string> redoStack;
		auto pushToUndoStack = [&undoStack](const string& currentContent)
			{
				undoStack.push(currentContent);
				while (undoStack.size() > 5)
				{
					undoStack.pop();
				}
			};
		while (true)
		{
			system("cls");
			SetConsoleTextAttribute(hConsole, 240);
			for (int i = 0; i < content.length(); i++)
			{
				if (i == currentPosition)
					cout << "|";
				cout << content[i];
			}
			int currentRow = 0;
			int currentCol = 0;
			for (int i = 0; i < currentCol; ++i)
			{
				if (content[i] == '\n' || currentCol == totalCols)
				{
					currentCol = 0;
					currentRow++;
				}
				else
				{
					currentCol++;
				}
			}
			setCursorPosition(currentCol, currentRow, 7);
			int key = GetArrowKey();
			switch (key)
			{
			case 75: // Left arrow
				currentPosition = max(0, currentPosition - 1);
				break;
			case 77: // Right arrow
				currentPosition = min(static_cast<int>(content.size()), currentPosition + 1);
				break;
			case 80: // Down Key
				while (currentPosition < content.size() && content[currentPosition] != '\n')
				{
					currentPosition++;
				}
				if (currentPosition < content.size())
				{
					currentPosition++;
				}
				break;
			case 72: // Up key
				while (currentPosition > 0 && content[currentPosition - 1] != '\n')
				{
					currentPosition--;
				}
				if (currentPosition > 0)
				{
					currentPosition--;
				}
				break;
			case 8: // Backspace key
				if (currentPosition > 0)
				{
					content.erase(content.begin() + currentPosition - 1);
					currentPosition--;
					pushToUndoStack(content);
				}
				break;
			case 27:                           // Escape key
				SaveToFile(fileName, content); // Save changes before exiting
				return;
			case 13: // Enter key
				content.insert(content.begin() + currentPosition, '\n');
				currentPosition++;
				pushToUndoStack(content);
				break; // Exit the function on escape key
			case 26:   // Ctrl + Z key (undo)
				if (!undoStack.empty())
				{
					redoStack.push(content);
					content = undoStack.top();
					undoStack.pop();
					currentPosition = min(currentPosition, static_cast<int>(content.size()));
				}
				break;
			case 25: // Ctrl + Y key (redo)
				if (!redoStack.empty())
				{
					undoStack.push(content);
					content = redoStack.top();
					redoStack.pop();
					currentPosition = min(currentPosition, static_cast<int>(content.size()));
				}
				break;
			default:
				if (isprint(key))
				{
					pushToUndoStack(content);
					content.insert(content.begin() + currentPosition, static_cast<char>(key));
					currentPosition++;
				}
				break;
			}
		}
	}
	bool SearchInFile(string searchString, string fileName)
	{
		ifstream file(fileName);
		if (!file.is_open())
		{
			cout << "File does not exist\n";
			return false;
		}
		string line;
		while (getline(file, line))
		{
			if (line.find(searchString) != string::npos)
			{
				file.close();
				return true;
			}
		}
		cout << "String not found in file: " << Name << Extension << "\n";
		file.close();
		return false;
	}

	friend class Directory;
	friend class DOS;
	friend class Tree;
};