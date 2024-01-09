#pragma once

#include<iostream>
#include<queue>

#include"Directory.h"
#include"Tree.h"
#include"File.h"

using namespace std;

class DOS
{
	Tree T;
	string COMMAND;
	File file;
	File* copiedFile;
public:
	DOS()
	{
		COMMAND = "";
	}
	void Execute()
	{
		cout << endl << T.CurrentDirectory->Path << DEFAULT_PROMPT;
		getline(cin >> ws, COMMAND);
		COMMAND = PreSpaces(COMMAND);
		COMMAND = PostSpaces(COMMAND);

		if (GetAsyncKeyState(VK_ESCAPE)) { Instructions(); }
		else if (Version()) {}
		else if (ClearScreen()) {}
		else if (Exit()) {}
		else if (Prompt()) {}
		else if (Attrib()) {}
		else if (ToRoot()) {}
		else if (ToParent()) {}
		else if (PrintCurrentDirectory()) {}
		else if (PrintWorkingDirectory()) {}
		else if (PrintTree()) {}
		else if (MakeDirectory()) {}
		else if (PrintDirectory()) {}
		else if (ChangeDirectory()) {}
		else if (DeleteDirectory()) {}
		else if (RemoveFile()) {}
		else if (FindFile()) {}
		else if (FormatDirectory()) {}
		else if (Copy()) {}
		else if (Move()) {}
		else if (Rename()) {}
		else if (createFile()) {}
		else if (EditFile()) {}
		else if (FindFile()) {}
		else if (FindSTR()) {}
		else if (AddToPrintQueue()) {}
		else if (AddToPriorityQueue()) {}
		else if (Queue()) {}
		else if (PQueue()) {}
		else if (SaveTree()) {}
		else if (LoadTree()) {}
		else if (Error()) {}
	}
	bool CopyRight()
	{
		gotoXY(0, 25);
		cout << "ABDULLAH AZHER CHAUDHARY | 2022-CS-204" << endl;
		return true;
	}
	bool Error()
	{
		cout << "'" << COMMAND << "' is not recognized as an internal or external command," << endl;
		cout << "operable program or batch file.";
		return true;
	}
	bool Version()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "ver")
		{
			cout << VERSION << endl;
			return true;
		}
		return false;
	}
	bool ClearScreen()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "cls")
		{
			system("cls");
			CopyRight();
			return true;
		}
		return false;
	}
	bool Exit()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "exit")
		{
			exit(69);
		}
		return false;
	}
	bool Prompt()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "prompt")
		{
			char symbol;
			cout << "Enter Symbol : ";
			cin >> symbol;
			DEFAULT_PROMPT = symbol;
			return true;
		}
		return false;
	}
	bool ToRoot()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "cd\\")
		{
			T.CurrentDirectory = T.Root;
			return true;
		}
		return false;
	}
	bool ToParent()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "cd..")
		{
			T.CurrentDirectory = T.CurrentDirectory->Parent;
			return true;
		}
		return false;
	}
	bool PrintCurrentDirectory()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "cd.")
		{
			cout << "Current directory is : " << T.CurrentDirectory->Name;
			return true;
		}
		return false;
	}
	bool PrintWorkingDirectory()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "pwd")
		{
			cout << "Current working directory is: " << T.CurrentDirectory->Name;
			return true;
		}
		return false;
	}
	bool PrintTree()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "tree")
		{
			T.PrintTree();
			return true;
		}
		return false;
	}
	bool MakeDirectory()
	{
		string input = COMMAND.substr(0, 5);
		input = ToLower(input);
		if (COMMAND.length() > 6)
		{
			if (input == "mkdir")
			{
				string name = COMMAND.substr(6, COMMAND.length());
				if (T.CurrentDirectory->FindDirectory(name))
				{
					cout << "This folder already exists in current directory";
					return true;
				}
				T.CurrentDirectory->InsertSubDirectory(name);
				return true;
			}
		}
		return false;
	}
	bool PrintDirectory()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "dir")
		{
			T.CurrentDirectory->PrintSubDirectory();
			T.CurrentDirectory->PrintFiles();
			return true;
		}
		return false;
	}
	bool ChangeDirectory()
	{
		string input = COMMAND.substr(0, 2);
		input = ToLower(input);
		if (input == "cd")
		{
			string name = COMMAND.substr(3, COMMAND.length());
			Directory* D = T.CurrentDirectory->FindDirectory(name);
			if (D)
				T.CurrentDirectory = D;
			else
				cout << "NO Such Directory" << endl;
			return true;
		}
		return false;
	}
	bool DeleteDirectory()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "rmdir")
		{
			if (T.CurrentDirectory == T.Root)
			{
				cout << "You CAN NOT delete Root Directory";
				return true;
			}
			T.CurrentDirectory->DeleteDirectory();
			T.CurrentDirectory = T.Root;
			return true;
		}
		return false;
	}
	bool RemoveFile()
	{
		string input = COMMAND.substr(0, 3);
		input = ToLower(input);
		if (input == "del")
		{
			string name = COMMAND.substr(4, COMMAND.length());
			if (T.CurrentDirectory->FindFile(name))
			{
				T.CurrentDirectory->RemoveFile(name);
				return true;
			}
			cout << "NO such file exists in the current directory";
			return true;
		}
		return false;
	}
	bool FindFile()
	{
		string input = COMMAND.substr(0, 4);
		input = ToLower(input);
		if (input == "search")
		{
			string name = COMMAND.substr(5, COMMAND.length());
			File* item = T.CurrentDirectory->FindFile(name);
			if (item != nullptr)
			{
				cout << "Found: " << item->Name << endl;
			}
			else
			{
				cout << "File NOT found" << endl;
			}
			return true;
		}
		return false;
	}
	bool FormatDirectory()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "format")
		{
			string name = T.CurrentDirectory->Name;
			cout << name;
			Directory* found = T.CurrentDirectory->Parent;
			if (found)
			{
				found->RemoveSubDirectory(name);
				T.CurrentDirectory = found;
			}
			else
			{
				cout << "Directory Doesn't exist";
			}
			return true;
		}
		return false;
	}
	bool Attrib()
	{
		string name = COMMAND.substr(0, 6);
		name = ToLower(name);
		if (name == "attrib")
		{
			name = COMMAND.substr(7, COMMAND.length());
			File* newFile = T.CurrentDirectory->FindFile(name);
			if (newFile != nullptr)
			{
				cout << "Attributes of file " << newFile->Name << " are: " << endl;
				cout << "Creation time:                " << newFile->Time << endl;
				cout << "Hidden property:              " << newFile->ReadOnly << endl;
				cout << "Extension:                    " << newFile->Extension << endl;
				return true;
			}
			return false;
		}
		return false;
	}
	bool createFile()
	{
		if (COMMAND.length() < 8)
			return false;
		string createFile = COMMAND.substr(0, 6);
		createFile = ToLower(createFile);
		if (createFile == "create")
		{
			createFile = COMMAND.substr(7, COMMAND.length());
			createFile = PostSpaces(createFile);
			createFile = PreSpaces(createFile);
			if (CheckForBackSlashes(createFile))
			{
				if (T.CurrentDirectory->FindFileBool(createFile))
				{
					cout << "This file already exist in the current directory";
					return true;
				}
				T.CurrentDirectory->InsertFile(createFile);
				return true;
			}
			else
			{
				cout << "File name can't contain Slashes :)";
				return true;
			}
		}
		return false;
	}
	bool EditFile()
	{
		if (COMMAND.length() < 6)
			return false;
		string name = COMMAND.substr(0, 4);
		name = ToLower(name);
		if (name == "edit")
		{
			name = COMMAND.substr(5, COMMAND.length());
			name = PostSpaces(name);
			if (T.CurrentDirectory->FindFileBool(name))
			{
				file.NavigateAndEditFile(name + ".txt");
				ClearScreen();
				return true;
			}
			else
				return false;
		}
		return false;
	}
	bool Copy()
	{
		if (COMMAND.length() < 6)
			return false;
		Directory F;
		istringstream iss(COMMAND);
		string action, source, destination;
		iss >> action >> source >> destination;
		action = ToLower(action);
		if (action != "copy")
			return false;
		destination = T.CurrentDirectory->GetLastDirectory(destination);
		Directory* copiedPath = T.FindDirectoryByName(destination);
		Directory* oldPath = T.CurrentDirectory;
		if (copiedPath != nullptr)
		{
			T.CurrentDirectory = copiedPath;
			T.CurrentDirectory->InsertFile(source);
			T.CurrentDirectory = oldPath;
			return true;
		}
		return false;
	}
	bool Move()
	{
		if (COMMAND.length() < 7)
			return false;
		Directory F;
		istringstream iss(COMMAND);
		string action, source, destination;
		iss >> action >> source >> destination;
		action = ToLower(action);
		if (action != "move")
			return false;
		destination = T.CurrentDirectory->GetLastDirectory(destination);
		Directory* copiedPath = T.FindDirectoryByName(destination);
		Directory* oldPath = T.CurrentDirectory;
		T.CurrentDirectory->RemoveFile(source);
		if (copiedPath != nullptr)
		{
			T.CurrentDirectory = copiedPath;
			T.CurrentDirectory->InsertFile(source);
			T.CurrentDirectory = oldPath;
			return true;
		}
		return false;
	}
	bool ChangeExtension()
	{
		string extension1, extension2;
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "convert")
		{
			cout << "Enter first extension: ";
			cin >> extension1;
			extension1 = "." + extension1;
			cout << "Enter second extension: ";
			cin >> extension2;
			extension2 = "." + extension2;
			T.CurrentDirectory->ChangeExtension(extension1, extension2);
			return true;
		}
		return false;
	}
	bool Rename()
	{
		string input = COMMAND.substr(0, 6);
		COMMAND = ToLower(COMMAND);
		if (input == "rename")
		{
			string name = COMMAND.substr(7, COMMAND.length());
			string newName;
			cout << "Enter new name of file: ";
			cin >> newName;
			if (T.CurrentDirectory->FindFile(name))
			{
				T.CurrentDirectory->RenameFile(name, newName);
				return true;
			}
			else
				cout << "Such file doesn't exist";
		}
		return false;
	}
	bool FindF()
	{
		string s_name, f_name;
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "findf")
		{
			cout << "Enter the string you want to search: ";
			getline(cin, s_name);
			cout << "Enter the name of file in which you want to search: ";
			cin >> f_name;
			if (file.SearchInFile(s_name, f_name + ".txt"))
			{
				cout << "String found";
				return true;
			}
			else
				return false;
		}
		return false;
	}
	bool FindSTR()
	{
		string s_name;
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "findstr")
		{
			cout << "Enter the string you want to search: ";
			getline(cin, s_name);
			for (auto file : T.CurrentDirectory->Files)
			{
				if (file->SearchInFile(s_name, file->Name + file->Extension))
				{
					cout << "String found in file: " << file->Name << file->Extension << endl;
					return true;
				}
			}
			cout << "String not found in any file in the current directory." << endl;
			return true;
		}
		return false;
	}
	bool AddToPrintQueue()
	{
		string name = COMMAND.substr(0, 5);
		name = ToLower(name);
		if (name == "print")
		{
			name = COMMAND.substr(6, COMMAND.length());
			name = PostSpaces(name);
			name = PreSpaces(name);
			T.CurrentDirectory->AddToPrintQueue(name);
			T.CurrentDirectory->DisplayPrintQueue();
			return true;
		}
		return false;
	}
	bool AddToPriorityQueue()
	{
		string name = COMMAND.substr(0, 6);
		name = ToLower(name);
		if (name == "pprint")
		{
			name = COMMAND.substr(7, COMMAND.length());
			name = PostSpaces(name);
			name = PreSpaces(name);
			T.CurrentDirectory->AddToPriorityPrintQueue(name);
			return true;
		}
		return false;
	}
	bool PQueue()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "pqueue")
		{
			T.CurrentDirectory->DisplayPriorityPrintQueueWithTime();
			return true;
		}
		return false;
	}
	bool Queue()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND == "queue")
		{
			T.CurrentDirectory->DisplayPrintQueueWithTime();
			return true;
		}
		return false;
	}
	bool LoadTree()
	{
		T.CurrentDirectory->SubDirectories.clear();
		T.CurrentDirectory->Files.clear();
		COMMAND = ToLower(COMMAND);
		if (COMMAND != "load")
			return false;
		ifstream file("Tree.txt");
		if (file.is_open())
		{
			string s;
			while (getline(file, s))
			{
				stringstream path = stringstream(s);
				string directory;
				Directory* DirectoryTraversal = T.Root;
				int count = 0;
				for (char c : s)
				{
					if (c == '\\')
						count++;
				}
				for (int i = 0; i < count; i++)
				{
					getline(path, directory, '\\');
					DirectoryTraversal = DirectoryTraversal->FindDirectory(directory);
				}
				getline(path, directory, '\\');
				Directory* loaded = new Directory(directory, "", DirectoryTraversal);
				DirectoryTraversal->SubDirectories.push_back(loaded);
			}
		}
		else
			return false;
		file.close();
		LoadFiles();
		return true;
	}
	void LoadFiles()
	{
		ifstream file("Files.txt");
		string s;
		while (getline(file, s))
		{
			stringstream path = stringstream(s);
			string directory;
			Directory* directoryTraversal = T.Root;
			int count = 0;
			for (char c : s)
			{
				if (c == '\\')
					count++;
			}
			for (int i = 0; i < count; i++)
			{
				getline(path, directory, '\\');
				directoryTraversal = directoryTraversal->FindDirectory(directory);
			}
			getline(path, directory, '\\');
			File* file = new File(directory);
			directoryTraversal->Files.push_back(file);
		}
	}
	bool SaveTree()
	{
		COMMAND = ToLower(COMMAND);
		if (COMMAND != "save")
			return false;
		SaveFile();
		auto x = T.Root;
		queue<string> st;
		preOrderTraversal(x, st);
		ofstream file("Tree.txt");
		while (!st.empty())
		{
			string i = st.front();
			st.pop();
			if (i.length() < 3)
				continue;
			i = i.substr(3);
			file << i << endl;
		}
		file.close();
	}
	bool SaveFile()
	{
		if (COMMAND != "save")
			return false;
		auto x = T.Root;
		queue<string> st;
		preOrderTraversalFiles(x, st);
		ofstream file("Files.txt");
		while (!st.empty())
		{
			string i = st.front();
			st.pop();
			if (i.length() < 3)
				continue;
			i = i.substr(3);
			file << i << endl;
		}
		file.close();
	}
	void preOrderTraversal(Directory* directory, queue<string>& st)
	{
		if (directory == nullptr)
			return;
		st.push(directory->Path);
		for (auto i : directory->SubDirectories)
		{
			preOrderTraversal(i, st);
		}
	}
	void preOrderTraversalFiles(Directory* directory, queue<string>& st)
	{
		if (directory == nullptr)
			return;
		for (auto i : directory->Files)
		{
			st.push(directory->Path + "\\" + i->Name);
		}
		for (auto i : directory->SubDirectories)
		{
			preOrderTraversalFiles(i, st);
		}
	}

	friend class Tree;
	friend class Directory;
};