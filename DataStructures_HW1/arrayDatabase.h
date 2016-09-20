#pragma once

/*	Data Structures Homework #1
Daniel Barber-Cironi
September 11, 2016
arrayDatabase.h
Header file with functions to manipulate an array based database
*/

using namespace std;

//function prototypes
void array_printEntries();
int array_insertRecord(string name, double x, double y);
int array_deleteRecord(string name, double x, double y);
void array_searchByName(string name);
void array_deleteByName(string name);
void array_deleteByCoordinate(double x, double y);
void array_searchByCoordinate(double x, double y);
void array_searchWithinDistance(string name, double requestedDistance);
