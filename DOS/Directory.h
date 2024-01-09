#pragma once

#include<iostream>
#include<list>

#include "File.h"
#include"Global.h"

using namespace std;

class Directory
{
	string Name;
	string Time;
	string Path;
	Directory* Parent;
	list<Directory*>SubDirectories;
	list<File*>Files;
	bool readOnly;
	list<string>pQueue;
	list<string>printQueue;

public:
	Directory(string name = "/0", string path = "", Directory* parent = nullptr, list<Directory*>subs = list<Directory*>(), list<File*>files = list<File*>(), bool read = false)
	{
		this->Name = name;
		this->Time = date_time();
		this->Path = path;
		this->Parent = parent;
		this->SubDirectories = subs;
		this->Files = files;
		this->readOnly = read;
	}
	//Directory Functions
	void InsertSubDirectory(string name)
	{
		string id;
		if (name != "V:")
			id = "\\";
		Directory* newDirectory = new Directory(name, Path + id + name, this);
		SubDirectories.push_back(newDirectory);
	}
	void RemoveSubDirectory(string name)
	{
		list<Directory*>::iterator iter;
		for (iter = SubDirectories.begin();iter != SubDirectories.end();iter++)
		{
			if ((*iter)->Name == name)
			{
				SubDirectories.erase(iter);
				break;
			}
		}
	}
	void PrintSubDirectory()
	{
		list<Directory*>::iterator iter;
		cout << "Directory of " << Name << " is :\n\n";
		for (iter = SubDirectories.begin(); iter != SubDirectories.end(); iter++)
		{
			cout << left << setw(30) << (*iter)->Time << "  <DIR>  " << (*iter)->Name;
			cout << endl;
		}
	}
	Directory* FindDirectory(string name)
	{
		list<Directory*>::iterator iter;
		for (iter = SubDirectories.begin();iter != SubDirectories.end(); iter++)
		{
			if ((*iter)->Name == name)
				return(*iter);
		}
		return nullptr;
	}
	void DeleteDirectory(Directory* Root)
	{
		if (Root == nullptr)
			return;
		list<Directory*>::iterator iter;
		for (iter = Root->SubDirectories.begin();iter != Root->SubDirectories.end();iter++)
		{
			DeleteDirectory(*iter);
		}
	}
	void DeleteDirectory()
	{
		DeleteDirectory(this);
	}
	string GetLastDirectory(string& path)
	{
		size_t lastSlash = path.find_last_of("\\");
		if (lastSlash != string::npos)
		{
			return path.substr(lastSlash + 1);
		}
		return path;
	}
	//File Functions
	void InsertFile(string name)
	{
		File* newFile = new File(name);
		Files.push_back(newFile);
	}
	void RemoveFile(string name)
	{
		list<File*>::iterator iter;
		for (iter = Files.begin(); iter != Files.end(); iter++)
		{
			if ((*iter)->Name == name)
			{
				Files.erase(iter);
				break;
			}
		}
	}
	void PrintFiles()
	{
		list<File*>::iterator iter;
		for (iter = Files.begin();iter != Files.end();iter++)
		{
			cout << left << setw(38) << (*iter)->Time << (*iter)->Name << (*iter)->Extension;
			cout << endl;
		}
	}
	File* FindFile(string name)
	{
		list<File*>::iterator iter;
		for (iter = Files.begin();iter != Files.end();iter++)
		{
			if ((*iter)->Name == name)
				return (*iter);
		}
		return nullptr;
	}
	bool FindFileBool(string name)
	{
		list<File*>::iterator iter;
		for (iter = Files.begin();iter != Files.end();iter++)
		{
			if ((*iter)->Name == name)
				return true;
		}
		return false;
	}
	void RenameFile(string filename, string newName)
	{
		list<File*>::iterator iter;
		for (iter = Files.begin();iter != Files.end();iter++)
		{
			if ((*iter)->Name == filename)
			{
				(*iter)->Name = newName;
			}
		}
	}
	void ChangeExtension(string name1, string name2)
	{
		list<File*>::iterator i;
		for (i = Files.begin(); i != Files.end(); i++)
		{
			if ((*i)->Extension == name1)
				(*i)->Extension = name2;
			else if ((*i)->Extension == name2)
				(*i)->Extension = name1;
		}
	}
	// Queue Functions
	void AddToQueue(string name)
	{
		pQueue.push_back(name);
	}
	void DisplayQueue()
	{
		if (pQueue.empty())
		{
			cout << "Print queue is empty." << endl;
		}
		else
		{
			cout << "Print Queue:" << endl;
			for (const auto& fileName : pQueue)
			{
				cout << fileName << endl;
			}
		}
	}
	void DisplayPriorityPrintQueueWithTime()
	{
		if (pQueue.empty())
		{
			cout << "Priority print queue is empty." << endl;
		}
		else
		{
			cout << "Priority Print Queue with Time Left:" << endl;
			time_t currentTime = time(nullptr);
			for (const auto& fileName : pQueue)
			{
				int timeLeft = rand() % 60; // Random time left in seconds
				cout << fileName << " - Time Left: " << timeLeft << " seconds" << endl;
			}
		}
	}
	void AddToPriorityPrintQueue(string fileName)
	{
		if (FindFileBool(fileName))
		{
			AddToQueue(fileName);
			DisplayQueue();
			cout << "File '" << fileName << "' added to the priority print queue.\n";
		}
		else
		{
			cout << "File '" << fileName << "' not found in the current directory.\n";
		}
	}
	void AddToPrintQueue(string fileName)
	{
		printQueue.push_back(fileName);
	}
	void DisplayPrintQueue()
	{
		if (printQueue.empty())
		{
			cout << "Print queue is empty." << endl;
		}
		else
		{
			cout << "Print Queue:" << endl;
			for (const auto& fileName : printQueue)
			{
				cout << fileName << endl;
			}
		}
	}
	void DisplayPrintQueueWithTime()
	{
		if (printQueue.empty())
		{
			cout << "Print queue is empty." << endl;
		}
		else
		{
			cout << "Print Queue with Time Left:" << endl;
			time_t currentTime = time(nullptr);
			for (const auto& fileName : printQueue)
			{
				int timeLeft = rand() % 60;
				cout << fileName << " - Time Left: " << timeLeft << " seconds" << endl;
			}
		}
	}

	friend class DOS;
	friend class File;
	friend class Tree;
};