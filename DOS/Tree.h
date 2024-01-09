#pragma once

#include<iostream>
#include<fstream>

#include"Directory.h"
#include"Global.h"

using namespace std;

class Tree
{
	Directory* Root;
	Directory* CurrentDirectory;

	void PrintTree(Directory* curDirectory, int space)
	{
		if (curDirectory == nullptr)
			return;
		cout << setw(space * 4) << "" << curDirectory->Name << endl;
		for (auto subDirectories : curDirectory->SubDirectories)
		{
			PrintTree(subDirectories, space + 1);
		}
		for (auto file : curDirectory->Files)
		{
			cout << setw((space + 1) * 4) << "-" << file->Name << file->Extension << endl;
		}
	}
	Directory* FindDirectoryByNameInDirectory(Directory* currentFolder, const string& name)
	{
		if (currentFolder == nullptr)
		{
			return nullptr;
		}

		if (currentFolder->Name == name)
		{
			return currentFolder;
		}
		for (auto subfolder : currentFolder->SubDirectories)
		{
			Directory* result = FindDirectoryByNameInDirectory(subfolder, name);
			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}
	Directory* FindDirectoryByNameInSubDirectories(Directory* currentFolder, const string& name)
	{
		for (auto subfolder : currentFolder->SubDirectories)
		{
			Directory* result = FindDirectoryByNameInDirectory(subfolder, name);
			if (result != nullptr)
			{
				return result;
			}
			result = FindDirectoryByNameInSubDirectories(subfolder, name);
			if (result != nullptr)
			{
				return result;
			}
		}

		return nullptr;
	}
public:
	Tree()
	{
		Root = CurrentDirectory = new Directory("V:", DEFAULT_PATH, nullptr);
	}

	void SaveTreeToFile()
	{
		ofstream file("MyTree.txt");

		Directory* temp;
		list<Directory*>savingList;

		savingList.push_back(Root);
		savingList.push_back(nullptr);

		list<Directory*>::iterator iter;

		for (iter = savingList.begin(); iter != savingList.end();iter++)
		{
			if (*iter == nullptr)
				continue;

			temp = *iter;
			file << temp->Name;

			list<Directory*>::iterator it;
			for (it = temp->SubDirectories.begin(); it != temp->SubDirectories.end();it++)
			{
				savingList.push_back(*it);
				file << "Dir" << (*it)->Name << ",";
			}
		}
		cout << endl;
	}
	void PrintTree()
	{
		PrintTree(Root, 0);
	}
	Directory* FindDirectoryByName(const string& name)
	{
		Directory* folderInRoot = FindDirectoryByNameInDirectory(Root, name);

		if (folderInRoot != nullptr)
		{
			return folderInRoot;
		}
		return FindDirectoryByNameInSubDirectories(Root, name);
	}

	friend class DOS;
	friend class Directory;
};