#pragma once

/*	Data Structures Homework #1
Daniel Barber-Cironi
September 11, 2016
arrayDatabase.h
Header file with functions to manipulate a linked list based database
*/

using namespace std;

//function prototypes
void linkedList_printEntries();
int linkedList_insertRecord(string name, double x, double y);
int linkedList_deleteRecord(string name, double x, double y);
void linkedList_searchByName(string name);
void linkedList_deleteByName(string name);
void linkedList_deleteByCoordinate(double x, double y);
void linkedList_searchByCoordinate(double x, double y);
void linkedList_searchWithinDistance(string name, double enteredDistance);
