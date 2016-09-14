/*	Data Structures Homework #1
Daniel Barber-Cironi
September 11, 2016
common.h
Contains variables needed throughout the various files in this program
*/

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

//global variables
extern int numberOfEntries = 0;

//function prototypes
void printMenu();
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