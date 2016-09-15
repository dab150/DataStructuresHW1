/*	Data Structures Homework #1
Daniel Barber-Cironi
September 11, 2016
arrayDatabase.cpp
Functions to manipulate an array based database
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include "arrayDatabase.h"
#include "common.h"

using namespace std;

void array_printEntries()
{
	for (int i = 0; i < numberOfEntries; i++)
	{
		string name = database[i].name;
		double x = database[i].xCoord;
		double y = database[i].yCoord;

		cout << "Name: " << name << ", X Coordinate: " << x << ", Y Coordinate: " << y << "\n";
	}
}

int array_insertRecord(string name, double x, double y) {
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

int array_deleteRecord(string name, double x, double y)
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

void array_searchByName(string name)
{
	bool found = false;
	for (int i = 0; i < numberOfEntries; i++)
	{
		if (name == database[i].name)
		{
			cout << "\n" << database[i].name << ", (" << database[i].xCoord << ", " << database[i].yCoord << ") \n";
			found = true;
		}
	}
	if (found == false)
	{
		cout << "No such record exists in the existing data set. \n";
	}
	showContinueScreen();
}

void array_deleteByName(string name)
{
	int result = -1;

	for (int i = 0; i < numberOfEntries; i++)
	{
		if (name == database[i].name)
		{
			//delete the record
			result = array_deleteRecord(database[i].name, 0, 0);
			if (result == 0)
				cout << "Record deleted successfully! \n";
			else if (result == 1)
				cout << "This entry doesn't exist! \n";
			else if (result == 2)
				cout << "Unknown error occured. You're guess is as good as mine... \n";
		}
	}
}

void array_deleteByCoordinate(double x, double y)
{
	int result = -1;

	for (int i = 0; i < numberOfEntries; i++)
	{
		if (x == database[i].xCoord && y == database[i].xCoord)
		{
			//delete the record
			result = array_deleteRecord("", database[i].xCoord, database[i].yCoord);
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

void array_searchByCoordinate(double x, double y)
{
	bool found = false;
	for (int i = 0; i < numberOfEntries; i++)
	{
		if (x == database[i].xCoord && y == database[i].yCoord)
		{
			cout << "\n" << database[i].name << ", (" << database[i].xCoord << ", " << database[i].yCoord << ") \n";
			found = true;
		}
		if (found == false)
		{
			cout << "No such record exists in the existing data set. \n";
		}
		showContinueScreen();
	}
}

void array_searchWithinDistance(string name, double x, double y)
{

}