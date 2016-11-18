// MyPod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Node
{
public:
	Node(string newName)
	{
		name = newName;
		nextNode = NULL;
	}

	string name;
	Node *nextNode;
};


Node* pHeadNode;


void DrawMenu()
{
	cout << "1. Play a song from the music library" << endl;
	cout << "2. Delete a name from the address book" << endl;
	cout << "3. Skip a song from the library" << endl;
	cout << "4. Exit My Pod" << endl;
	cout << "" << endl;
	cout << "You choice: ";
}

Node* FindName(string name)
{
	if (pHeadNode)
	{
		Node *pCurrentNode = pHeadNode;
		while (pCurrentNode && pCurrentNode->name != name)
		{
			if (pCurrentNode->name == name)
				return pCurrentNode;

			pCurrentNode = pCurrentNode->nextNode;
		}
	}
	return NULL;
}


void InsertNewNode(Node* pNewNode)
{
	if (!pNewNode || (pNewNode->name < pHeadNode->name))
	{
		pNewNode->nextNode = pHeadNode;
		pHeadNode = pNewNode;
	}
	else {
		Node *pCurrentNode = pHeadNode;
		Node *pPrevNode = pCurrentNode;
		while (pCurrentNode && pCurrentNode->name < pNewNode->name)
		{
			pPrevNode = pCurrentNode;
			pCurrentNode = pCurrentNode->nextNode;
		}
		pNewNode->nextNode = pPrevNode->nextNode;
		pPrevNode->nextNode = pNewNode;
	}
}

void PlayNewEntry()
{
	string name;
	cout << "Enter name of song to play: ";
	getline(cin, name);
	cin.clear();
	cin.sync();

	getline(cin, name);

	if (pHeadNode)
	{
		if (FindName(name))
		{
			cout << "" << endl;
			cout << "Song is currently playing";
			cout << "" << endl;
			return;
		}
	}


	if (pHeadNode)
	{
		Node* pNewNode = new Node(name);

		InsertNewNode(pNewNode);
	}
	else {
		pHeadNode = new Node(name);
	}

	cout << "" << endl;
	cout << "Song is now playing" << endl;
	cout << "" << endl;
}

void DeleteEntry()
{
	string name;

	if (pHeadNode)
	{
		cin.clear();
		cin.sync();

		cout << "Enter name of the song you want to delete: ";
		getline(cin, name);

		Node *pCurrentNode = pHeadNode;
		Node *pPrevNode = pCurrentNode;
		while (pCurrentNode && pCurrentNode->name != name)
		{
			if (pCurrentNode->name == name)
				break;

			pCurrentNode = pCurrentNode->nextNode;
		}

		if (pCurrentNode)
		{
			if (pCurrentNode == pHeadNode)
			{
				pHeadNode = pCurrentNode->nextNode;
			}
			else {
				pPrevNode->nextNode = pCurrentNode->nextNode;
			}
			delete pCurrentNode;
		}
		else {
			cout << "" << endl;
			cout << "Entry is not found" << endl;
			cout << "" << endl;
		}
	}
	else {
		cout << "" << endl;
		cout << "Library is empty already" << endl;
		cout << "" << endl;
		return;
	}
}

void SkipEntry()
{
	string name;

	if (pHeadNode)
	{
		cin.clear();
		cin.sync();

		cout << "Enter name of song you want to skip: ";
		getline(cin, name);

		Node *pCurrentNode = pHeadNode;
		Node *pPrevNode = pCurrentNode;
		while (pCurrentNode && pCurrentNode->name != name)
		{
			if (pCurrentNode->name == name)
				break;

			pCurrentNode = pCurrentNode->nextNode;
		}

		if (pCurrentNode)
		{
			cin.clear();
			cin.sync();
			cout << "Enter name of song: ";
			getline(cin, name);

			if (pHeadNode)
			{
				if (FindName(name))
				{
					cout << "" << endl;
					cout << "Song is being skipped";
					cout << "" << endl;
					return;
				}
			}

			if (pCurrentNode == pHeadNode)
			{
				pHeadNode = pCurrentNode->nextNode;
			}
			else {
				pPrevNode->nextNode = pCurrentNode->nextNode;
			}
			
}

void SaveListToFile();
{
	ofstream outfile;

	outfile.open("songlist.txt");

	Node* pCurrentNode = pHeadNode;
	while (pCurrentNode)
	{
		Node* pNode = pCurrentNode;
		pCurrentNode = pCurrentNode->nextNode;
		outfile << pNode->name << endl;
	}

	outfile.close();
}

void LoadListFromFile()
{
	ifstream infile;

	infile.open("songlist.txt");

	string name;

	while (getline(infile, name))
	{
		string name;
		getline(infile, name);

		if (!pHeadNode)
		{
			pHeadNode = new Node(name);

		}
		else {
			Node *pCurrentNode = pHeadNode;
			Node *pPrevNode = pCurrentNode;
			while (pCurrentNode)
			{
				pPrevNode = pCurrentNode;
				pCurrentNode = pCurrentNode->nextNode;
			}

		
	}
}

	infile.close();

int main()
{
	int choice;
	bool stop = false;

	LoadListFromFile();
	do
	{
		do
		{
			DrawMenu();
			cin >> choice;
			if (choice<1 || choice>6)
				cout << "Incorrect choice. Try again" << endl << endl;
		} while (choice<1 || choice>6);

		switch (choice)
		{
		case 1:
			PlayNewEntry();
			break;
		case 2:
			DeleteEntry();
			break;
		case 3:
			SkipEntry();
			break;
		case 4:
			stop = true;
			break;
		default:
			break;
		}

	} while (!stop);
	SaveListToFile();

	Node* pCurrentNode = pHeadNode;
	while (pCurrentNode)
	{
		Node* pNode = pCurrentNode;
		pCurrentNode = pCurrentNode->nextNode;
		delete pNode;
	}

	return 0;
}



