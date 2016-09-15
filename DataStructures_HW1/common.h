#pragma once

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
int numberOfArrayEntries;
int numberOfLLEntries;

//function prototypes
void printMenu();
void handleUserInput(char, int);
void showContinueScreen();

//--------------Array Stuff--------------//
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
//---------------------------------------//

//------------Linked List Stuff----------//
//node structure
struct node {
	string name;
	double xCoord;
	double yCoord;
	node *next;
};

//--------------------------------------//