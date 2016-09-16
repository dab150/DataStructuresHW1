/*	Data Structures Homework #1
Daniel Barber-Cironi
September 11, 2016
linkedListDatabase.cpp
Functions to manipulate a linked list based database
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include "linkedListDatabase.h"
#include "common.h"

using namespace std;

int numberOfLLEntries;
/*/
class LinkedList {
	// Struct inside the class LinkedList
	// This is one node which is not needed by the caller. It is just
	// for internal work.
	struct Node {
		string name;
		double xCoord;
		double yCoord;
		Node *next;
	};

public:
	// constructor
	LinkedList() {
		head = NULL; // set head to NULL
	}

	// This prepends a new value at the beginning of the list
	void addValue(string name, double x, double y) {
		// create new Node
		Node *n = new Node();   
		// set value
		n->name = name;
		n->xCoord = x;
		n->yCoord = y;

		n->next = head;         // make the node point to the next node.
								//  If the list is empty, this is NULL, so the end of the list --> OK
		head = n;               // last but not least, make the head point at the new node.
	}

	// returns the first element in the list and deletes the Node.
	// caution, no error-checking here!
	int popValue() {
		Node *n = head;
		int ret = n->x;

		head = head->next;
		delete n;
		return ret;
	}

	// private member
private:
	Node *head; // this is the private member variable. It is just a pointer to the first Node
};*/

//node structure
struct node {
public:
	string name;
	double xCoord;
	double yCoord;
	node *next;
};

node *root;
node *temp;
node *head;

void linkedList_printEntries()
{
	temp = root;
	if (temp->name != "")
	{
		cout << "Name: " << root->name << " X: " << root->xCoord << ", Y: " << root->xCoord << "\n";
	}
	while (temp->next != NULL)
	{
		temp = temp->next;	
		cout << "Name: " << temp->name << " X: " << temp->xCoord << ", Y: " << temp->xCoord << "\n";
	}
}

int linkedList_insertRecord(string name, double x, double y) {
	try
	{
		numberOfLLEntries += 1;

		//setup initial node
		if (numberOfLLEntries == 1)
		{
			root = new node;
			root->next = NULL;	//null pointer

			//fill in data
			root->name = name;
			root->xCoord = x;
			root->yCoord = y;

			return 0;
		}
		if (numberOfLLEntries > 1)
		{
			node *n = new node; //the new node to be added
			node *temp = root; //used to traverse the list

			//fill in data
			n->name = name;
			n->xCoord = x;
			n->yCoord = y;
			n->next = NULL;

			while (temp->next != NULL) //this will find the previous last node and set its pointer to the new node 'n'
					temp = temp->next;

			temp->next = n;

			if (numberOfLLEntries == 2)
			{
				root->next = n;
			}

			return 0;
		}

	}
	catch (exception& e)
	{
		return 2;
	}

}

int linkedList_deleteRecord(string name, double x, double y)
{
	try
	{

	}
	catch (exception& e)
	{
		return 2;
	}


}

void linkedList_searchByName(string name)
{
}

void linkedList_deleteByName(string name)
{

}

void linkedList_deleteByCoordinate(double x, double y)
{
	
}

void linkedList_searchByCoordinate(double x, double y)
{
	
}

void linkedList_searchWithinDistance(string name, double x, double y)
{

}
