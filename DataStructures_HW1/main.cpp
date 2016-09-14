/*	Data Structures Homework #1
	Daniel Barber-Cironi
	September 11, 2016
	Implement a database with an array and a linked list.
*/

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

//global variables
int numberOfEntries = 0;

//function prototypes
void printMenu();
void printEntries();
int insertRecord(string, double, double);
int deleteRecord(string, double, double);
void searchByName(string);
void deleteByName(string);
void deleteByCoordinate(double, double);
void searchByCoordinate(double, double);
void searchWithinDistance(string, double, double);
void handleUserInput(char, int);
void showContinueScreen();


struct entry {
public:
	string name;
	double xCoord;
	double yCoord;
};

//arrays
entry *initialDatabase;
entry *database;

void main()
{
	printMenu();
}

void printMenu() {
	char implementation;
	int operation;

	cout << "\n";
	cout << "**************************************";
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

void printEntries()
{
	for (int i = 0; i < numberOfEntries; i++)
	{
		string name = database[i].name;
		double x = database[i].xCoord;
		double y = database[i].yCoord;

		cout << "Name: " << name << ", X Coordinate: " << x << ", Y Coordinate: " << y << "\n";
	}
}

int insertRecord(string name, double x, double y) {
	try
	{
		numberOfEntries += 1;

		if (numberOfEntries == 1)	//first entry needs to create initial database array and add first item
		{
			initialDatabase = new entry[numberOfEntries];
			initialDatabase[0] = { name, x, y };
			//in this case we make database the same as initialDatabase
			database = new entry[numberOfEntries];
			database[0] = { name, x, y };
			return 0;
		}
		else						//otherwise we need to create a new array AND copy the old array contents over, then add new entry
		{
			if (numberOfEntries > 1)
			{
				//delete previous database array
				delete[]database;
			}

			database = new entry[numberOfEntries];

			for (int i = 0; i < numberOfEntries - 1; i++)
			{
				//copy items
				database[i] = initialDatabase[i];
			}

			//add new item
			database[numberOfEntries - 1] = { name, x, y };

			//delete old array after it is copied over
			delete[]initialDatabase;
			//recreate "old" array with one larger size
			initialDatabase = new entry[numberOfEntries];
			//now repopulate this "old" array with the new data, so we can use it when we insert next time to copy data to new database
			for (int i = 0; i < numberOfEntries; i++)
			{
				initialDatabase[i] = database[i];
			}
			return 0;
		}
	}
	catch (exception& e)
	{
		return 2;
	}

}

int deleteRecord(string name, double x, double y)
{
	bool found = false;
	int indexToDelete = -1;
	try
	{
		//figure out which index the desired entry is located at
		for (int i = 0; i < numberOfEntries; i++)
		{
			if (database[i].name == name || (database[i].xCoord == x && database[i].yCoord == y))
			{
				indexToDelete = i;
				found = true;
			}
		}

		if (!found)
		{
			return 1; //not found
		}

		//this will delete the desired entry by ovewriting its value with the value of the item directly to the right
		//it will then shift all of the other elements after this to the left
		//this leaves us with a double entry at our last entry
		//so we need to delete the last item
		for (int i = indexToDelete; i < numberOfEntries - indexToDelete; i++)
		{
			database[i] = database[i + 1];
		}

		//decrement the number of entries
		numberOfEntries -= 1;

		//delete and recreate the 'initialDatabase' as the correct size so we can use it as a temp database
		//in order to delete and recreate 'database' as the right size with the right items
		delete[]initialDatabase;
		initialDatabase = new entry[numberOfEntries];


		//copy the database (minus the last entry) to our 'initialDatabase'
		for (int i = 0; i < numberOfEntries; i++)
		{
			initialDatabase[i] = database[i];
		}
		
		//now we delete the too big database array and recreate it as the right size
		delete[]database;
		database = new entry[numberOfEntries];

		//copy from 'initialDatabase' to 'database'
		for (int i = 0; i < numberOfEntries; i++)
		{
			database[i] = initialDatabase[i];
		}
		return 0;
	}
	catch (exception& e)
	{
		return 2;
	}


}

void handleUserInput(char implement, int operate)
{
	//variables
	string enteredName;
	double enteredX;
	double enteredY;
	double enteredSearchDistance;
	int returnValue;

	switch (operate) 
	{
		case 1:	//insert a record
			cout << "Enter name of the city: ";
			cin >> enteredName;
			cout << "Enter x coordinate of the city: ";
			cin >> enteredX;
			cout << "Enter y coordinate of the city: ";
			cin >> enteredY;
			
			returnValue = insertRecord(enteredName, enteredX, enteredY);
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
			searchByName(enteredName);
			break;

		case 3:	//Search for a record by coordinate
			cout << "Enter X Coordinate of the city to be searched: ";
			cin >> enteredX;
			cout << "Enter Y Coordinate of the city to be searched: ";
			cin >> enteredY;
			searchByCoordinate(enteredX, enteredY);
			break;

		case 4:	//Delete a record by name
			cout << "Enter name of the city to be deleted: ";
			cin >> enteredName;
			deleteByName(enteredName);
			break;
		
		case 5: //Delete a record by coordinate
			cout << "Enter X Coordinate of the city to be deleted: ";
			cin >> enteredX;
			cout << "Enter Y Coordinate of the city to be deleted: ";
			cin >> enteredY;
			deleteByCoordinate(enteredX, enteredY);
			break;

		case 6:	//Print within a certain distance of entry
			cout << "Enter name of city you would like to search around: ";
			cin >> enteredName;
			cout << "How far would you like to search?: ";
			cin >> enteredSearchDistance;
			break;

		case 7: //print ALL records
			printEntries();

		default:
			break;
	}

	showContinueScreen();
}

void searchByName(string name)
{
	bool found = false;
	for (int i = 0; i < numberOfEntries; i++)
	{
		if (name == database[i].name)
		{
			cout << database[i].name << ", (" << database[i].xCoord << ", " << database[i].yCoord << ") \n";
			found = true;
		}
	}
	if (found == false)
	{
		cout << "No such record exists in the existing data set. \n";
	}
	showContinueScreen();
}

void deleteByName(string name)
{
	int result = -1;

	for (int i = 0; i < numberOfEntries; i++)
	{
		if (name == database[i].name)
		{
			//delete the record
			result = deleteRecord(database[i].name, 0, 0);
			if (result == 0)
				cout << "Record deleted successfully! \n";
			else if (result == 1)
				cout << "This entry doesn't exist! \n";
			else if (result == 2)
				cout << "Unknown error occured. You're guess is as good as mine... \n";
		}
	}
}

void deleteByCoordinate(double x, double y)
{
	int result = -1;

	for (int i = 0; i < numberOfEntries; i++)
	{
		if (x == database[i].xCoord && y == database[i].xCoord)
		{
			//delete the record
			result = deleteRecord("", database[i].xCoord, database[i].yCoord);
			if (result == 0)
				cout << "Record deleted successfully! \n";
			else if (result == 1)
				cout << "This entry doesn't exist! \n";
			else if (result == 2)
				cout << "Unknown error occured. You're guess is as good as mine... \n";
		}
		else
		{
			cout << "This entry doesn't exist! \n";
		}
	}
}

void searchByCoordinate(double x, double y)
{
	bool found = false;
	for (int i = 0; i < numberOfEntries; i++)
	{
		if (x == database[i].xCoord && y == database[i].yCoord)
		{
			cout << database[i].name << ", (" << database[i].xCoord << ", " << database[i].yCoord << ") \n";
			found = true;
		}
		if (found == false)
		{
			cout << "No such record exists in the existing data set. \n";
		}
		showContinueScreen();
	}
}

void searchWithinDistance(string name, double x, double y)
{

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