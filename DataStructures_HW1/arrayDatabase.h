#ifndef arrayDatabase
#define arrayDatabase

/*	Data Structures Homework #1
Daniel Barber-Cironi
September 11, 2016
arrayDatabase.h
Header file with functions to manipulate an array based database
*/

#include "arrayDatabase.cpp"

//function prototypes
void array_printEntries();
int array_insertRecord(string, double, double);
int array_deleteRecord(string, double, double);
void arrray_searchByName(string);
void array_deleteByName(string);
void array_deleteByCoordinate(double, double);
void array_searchByCoordinate(double, double);
void array_searchWithinDistance(string, double, double);

#endif