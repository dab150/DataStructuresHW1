/*	Data Structures Homework #1
	Daniel Barber-Cironi
	September 11, 2016
	Implement a database with an array and a linked list.
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include "arrayDatabase.h"
#include "linkedListDatabase.h"

using namespace std;

//function prototypes
void printMenu();
void handleUserInput(char, int);
void showContinueScreen();

void main()
{
	printMenu();
}

void printMenu() {
	char implementation;
	int operation;

	cout << "\n";
	cout << "*********************************************************";
	cout << " \n \n \n";
	cout << "Implementation Options: \n";
	cout << "	A.Use an array-based list implementation \n";
	cout << "	B.Use a linked-list implementation \n \n";
	cout << "Operation Options \n";
	cout << "	1. Insert a record \n";
	cout << "	2. Search for a record by name \n";
	cout << "	3. Search for a record by coordinate \n";
	cout << "	4. Delete a record by name \n";
	cout << "	5. Delete a record by coordinate \n";
	cout << "	6. Print records within a given distance of a specified location \n";
	cout << "	7. Print ALL records \n";
	cout << "	8. Exit \n \n";

	cout << "Enter your implementation option: ";
	cin >> implementation;
	while (implementation != 'A' && implementation != 'a'
		&& implementation != 'B' && implementation != 'b')
	{
		cout << "Please enter either 'A' or 'B' for your implementation option \n";
		cout << "Enter your implementation option: ";
		cin >> implementation;
	}	

	cout << "Enter your operation option: ";
	cin >> operation;
	while (operation != 1 && operation != 2 && operation != 3 && operation != 4
		&& operation != 5 && operation != 6 && operation != 7 && operation != 8 && operation)
	{
		cout << "Please choose 1 through 8 for your operation option \n";
		cout << "Enter your operation option: ";
		cin >> operation;
	}
	cout << "\n";

	//handle users input
	handleUserInput(implementation, operation);
}

void handleUserInput(char implement, int operate)
{
	//variables
	string enteredName;
	double enteredX;
	double enteredY;
	double enteredSearchDistance;
	int returnValue;

	if (implement == 'A' || implement == 'a') //implement using array
	{
		switch (operate)
		{
		case 1:	//insert a record
			cout << "Enter name of the city: ";
			cin >> enteredName;
			cout << "Enter x coordinate of the city: ";
			cin >> enteredX;
			cout << "Enter y coordinate of the city: ";
			cin >> enteredY;

			returnValue = array_insertRecord(enteredName, enteredX, enteredY);
			if (returnValue == 0)
				cout << "Record inserted successfully! \n";
			else if (returnValue == 1)
				cout << "This entry already exists \n";
			else if (returnValue == 2)
				cout << "Unknown error occured. You're guess is as good as mine... \n";
			break;

		case 2: //Search for a record by name
			cout << "Enter name of the city to be searched: ";
			cin >> enteredName;
			array_searchByName(enteredName);
			break;

		case 3:	//Search for a record by coordinate
			cout << "Enter X Coordinate of the city to be searched: ";
			cin >> enteredX;
			cout << "Enter Y Coordinate of the city to be searched: ";
			cin >> enteredY;
			array_searchByCoordinate(enteredX, enteredY);
			break;

		case 4:	//Delete a record by name
			cout << "Enter name of the city to be deleted: ";
			cin >> enteredName;
			array_deleteByName(enteredName);
			break;

		case 5: //Delete a record by coordinate
			cout << "Enter X Coordinate of the city to be deleted: ";
			cin >> enteredX;
			cout << "Enter Y Coordinate of the city to be deleted: ";
			cin >> enteredY;
			array_deleteByCoordinate(enteredX, enteredY);
			break;

		case 6:	//Print within a certain distance of entry
			cout << "Enter name of city you would like to search around: ";
			cin >> enteredName;
			cout << "How far would you like to search?: ";
			cin >> enteredSearchDistance;
			break;

		case 7: //print ALL records
			array_printEntries();

		default:
			break;
		}
	}

	if (implement == 'B' || implement == 'b')	//implement using linked list
	{
		switch (operate)
		{
		case 1:	//insert a record
			cout << "Enter name of the city: ";
			cin >> enteredName;
			cout << "Enter x coordinate of the city: ";
			cin >> enteredX;
			cout << "Enter y coordinate of the city: ";
			cin >> enteredY;

			returnValue = linkedList_insertRecord(enteredName, enteredX, enteredY);
			if (returnValue == 0)
				cout << "Record inserted successfully! \n";
			else if (returnValue == 1)
				cout << "This entry already exists \n";
			else if (returnValue == 2)
				cout << "Unknown error occured. You're guess is as good as mine... \n";
			break;

		case 2: //Search for a record by name
			cout << "Enter name of the city to be searched: ";
			cin >> enteredName;
			linkedList_searchByName(enteredName);
			break;

		case 3:	//Search for a record by coordinate
			cout << "Enter X Coordinate of the city to be searched: ";
			cin >> enteredX;
			cout << "Enter Y Coordinate of the city to be searched: ";
			cin >> enteredY;
			linkedList_searchByCoordinate(enteredX, enteredY);
			break;

		case 4:	//Delete a record by name
			cout << "Enter name of the city to be deleted: ";
			cin >> enteredName;
			linkedList_deleteRecord(enteredName, 0, 0);
			break;

		case 5: //Delete a record by coordinate
			cout << "Enter X Coordinate of the city to be deleted: ";
			cin >> enteredX;
			cout << "Enter Y Coordinate of the city to be deleted: ";
			cin >> enteredY;
			linkedList_deleteRecord("",enteredX, enteredY);
			break;

		case 6:	//Print within a certain distance of entry
			cout << "Enter name of city you would like to search around: ";
			cin >> enteredName;
			cout << "How far would you like to search?: ";
			cin >> enteredSearchDistance;
			break;

		case 7: //print ALL records
			linkedList_printEntries();

		default:
			break;
		}
	}

	showContinueScreen();
}

void showContinueScreen()
{
	char input;
	cout << "\n";
	cout << "Would you like to continue with another operation? \n";
	cout << "Enter 'Y' to continue or 'N' to exit the program. \n";
	cin >> input;
	if (input == 'Y' || input == 'y')
	{
		printMenu();
	}
	else if (input == 'N' || input == 'n')
	{
		exit(0);
	}
	else
	{
		cout << " \n Error: Please enter either 'Y' or 'N'. \n";
		showContinueScreen();
	}
}