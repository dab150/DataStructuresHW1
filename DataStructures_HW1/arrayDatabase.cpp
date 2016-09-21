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

int numberOfArrayEntries;
bool displayExecutionTime = true;

//entry structure
struct entry {
public:
	string name;
	double xCoord;
	double yCoord;
};

//entry object initializations
entry *initialDatabase;
entry *database;


void array_printEntries()
{
	auto startTime = chrono::high_resolution_clock::now();
	
	if (numberOfArrayEntries == 0)
	{
		cout << "No entries to display! \n";
	}

	else
	{
		for (int i = 0; i < numberOfArrayEntries; i++)
		{
			string name = database[i].name;
			double x = database[i].xCoord;
			double y = database[i].yCoord;

			cout << "Name: " << name << " X Coordinate: " << x << ", Y Coordinate: " << y << "\n";
		}
	}

	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
	if (displayExecutionTime)
		cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
}

int array_insertRecord(string name, double x, double y) 
{
	auto startTime = chrono::high_resolution_clock::now();

	try
	{
		numberOfArrayEntries += 1;

		if (numberOfArrayEntries == 1)	//first entry needs to create initial database array and add first item
		{
			initialDatabase = new entry[numberOfArrayEntries];
			initialDatabase[0] = { name, x, y };
			//in this case we make database the same as initialDatabase
			database = new entry[numberOfArrayEntries];
			database[0] = { name, x, y };
			auto endTime = chrono::high_resolution_clock::now();
			chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
			if (displayExecutionTime)
				cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
			return 0;
		}
		else						//otherwise we need to create a new array AND copy the old array contents over, then add new entry
		{
			if (numberOfArrayEntries > 1)
			{
				//delete previous database array
				delete[]database;
			}

			database = new entry[numberOfArrayEntries];

			for (int i = 0; i < numberOfArrayEntries - 1; i++)
			{
				//copy items
				database[i] = initialDatabase[i];
			}

			//add new item
			database[numberOfArrayEntries - 1] = { name, x, y };

			//delete old array after it is copied over
			delete[]initialDatabase;
			//recreate "old" array with one larger size
			initialDatabase = new entry[numberOfArrayEntries];
			//now repopulate this "old" array with the new data, so we can use it when we insert next time to copy data to new database
			for (int i = 0; i < numberOfArrayEntries; i++)
			{
				initialDatabase[i] = database[i];
			}
			auto endTime = chrono::high_resolution_clock::now();
			chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
			if (displayExecutionTime)
				cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
			return 0;
		}
	}
	catch (exception& e)
	{
		auto endTime = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
		if (displayExecutionTime)
			cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
		return 2;
	}
}

int array_deleteRecord(string name, double x, double y)
{
	auto startTime = chrono::high_resolution_clock::now();

	bool found = false;
	int indexToDelete = -1;
	try
	{
		//figure out which index the desired entry is located at
		for (int i = 0; i < numberOfArrayEntries; i++)
		{
			if (database[i].name == name || (database[i].xCoord == x && database[i].yCoord == y))
			{
				indexToDelete = i;
				found = true;
			}
		}

		if (!found)
		{
			auto endTime = chrono::high_resolution_clock::now();
			chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
			if (displayExecutionTime)
				cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
			return 1; //not found
		}

		//this will delete the desired entry by ovewriting its value with the value of the item directly to the right
		//it will then shift all of the other elements after this to the left
		//this leaves us with a double entry at our last entry
		//so we need to delete the last item
		for (int i = indexToDelete; i < numberOfArrayEntries - (indexToDelete + 1); i++)
		{
			database[i] = database[i + 1];
		}

		//decrement the number of entries
		numberOfArrayEntries -= 1;

		//delete and recreate the 'initialDatabase' as the correct size so we can use it as a temp database
		//in order to delete and recreate 'database' as the right size with the right items
		delete[]initialDatabase;
		initialDatabase = new entry[numberOfArrayEntries];


		//copy the database (minus the last entry) to our 'initialDatabase'
		for (int i = 0; i < numberOfArrayEntries; i++)
		{
			initialDatabase[i] = database[i];
		}

		//now we delete the too big database array and recreate it as the right size
		delete[]database;
		database = new entry[numberOfArrayEntries];

		//copy from 'initialDatabase' to 'database'
		for (int i = 0; i < numberOfArrayEntries; i++)
		{
			database[i] = initialDatabase[i];
		}
		auto endTime = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
		if (displayExecutionTime)
			cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
		return 0;
	}
	catch (exception& e)
	{
		auto endTime = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
		if (displayExecutionTime)
			cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
		return 2;
	}
}

void array_searchByName(string name)
{
	auto startTime = chrono::high_resolution_clock::now();

	bool found = false;
	for (int i = 0; i < numberOfArrayEntries; i++)
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

	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
	if (displayExecutionTime)
		cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
}

void array_deleteByName(string name)
{
	auto startTime = chrono::high_resolution_clock::now();

	int result = -1;

	for (int i = 0; i < numberOfArrayEntries; i++)
	{
		if (name == database[i].name)
		{
			//delete the record
			result = array_deleteRecord(database[i].name, 0, 0);
			if (result == 0)
				cout << "\nRecord deleted successfully! \n";
			else if (result == 1)
				cout << "\nThis entry doesn't exist! \n";
			else if (result == 2)
				cout << "\nUnknown error occured. You're guess is as good as mine... \n";
		}
		else
		{
			cout << "\nThis entry doesn't exist! \n";
		}
	}

	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
	if (displayExecutionTime)
		cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
}

void array_deleteByCoordinate(double x, double y)
{
	auto startTime = chrono::high_resolution_clock::now();

	int result = -1;

	for (int i = 0; i < numberOfArrayEntries; i++)
	{
		if (x == database[i].xCoord && y == database[i].xCoord)
		{
			//delete the record
			result = array_deleteRecord("", database[i].xCoord, database[i].yCoord);
			if (result == 0)
				cout << "\nRecord deleted successfully! \n";
			else if (result == 1)
				cout << "\nThis entry doesn't exist! \n";
			else if (result == 2)
				cout << "\nUnknown error occured. You're guess is as good as mine... \n";
		}
	}

	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
	if (displayExecutionTime)
		cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
}

void array_searchByCoordinate(double x, double y)
{
	auto startTime = chrono::high_resolution_clock::now();

	bool found = false;
	for (int i = 0; i < numberOfArrayEntries; i++)
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
	}

	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
	if (displayExecutionTime)
		cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
}

void array_searchWithinDistance(string name, double requestedDistance)
{
	auto startTime = chrono::high_resolution_clock::now();

	bool found = false;
	double centerXRad = 0;
	double centerYRad = 0;
	double compareXRad = 0;
	double compareYRad = 0;


	if (numberOfArrayEntries == 0)
	{
		cout << "No entries to display! \n";
	}
	else
	{
		//start by finding coordinates of requested center location
		for (int i = 0; i < numberOfArrayEntries; i++)
		{
			if (database[i].name == name)
			{
				//convert coordinates to radians
				centerXRad = database[i].xCoord * (3.1415926535 / 180.0);
				centerYRad = database[i].yCoord * (3.1415926535 / 180.0);
			}
		}

		//now determine if any of the other database entries are within 'distance' of center
		for (int i = 0; i < numberOfArrayEntries; i++)
		{
			compareXRad = database[i].xCoord * (3.1415926535 / 180.0);
			compareYRad = database[i].yCoord * (3.1415926535 / 180.0);
			//perform distance calculation
			double e = acos(sin(centerYRad)*sin(compareYRad) + cos(centerYRad)*cos(compareYRad)*cos(compareXRad - centerXRad));
			//multiply by radius of equator
			double distance = e * 3963.191;

			if (distance < requestedDistance && database[i].name != name)
			{
				cout << "Name: " << database[i].name << " X Coord: " << database[i].xCoord << ", Y Coord: " << database[i].yCoord << "\n";
				found = true;
			}
		}

		if (found != true)
		{
			cout << "No records found  \n";
		}
	}

	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
	if (displayExecutionTime)
		cout << "Execution Time: " << time_span.count() * 1000 << " milliseconds";
}