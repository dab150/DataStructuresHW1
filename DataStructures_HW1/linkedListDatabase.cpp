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
	if (temp != NULL) //make sure we dont have an empty list first
	{
		if (temp->name != "")
		{
			cout << "Name: " << root->name << " X: " << root->xCoord << ", Y: " << root->yCoord << "\n";
		}
		while (temp->next != NULL)
		{
			temp = temp->next;
			cout << "Name: " << temp->name << " X: " << temp->xCoord << ", Y: " << temp->yCoord << "\n";
		}
	}
	else
	{
		cout << "No entries to display! \n";
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
		node *temp = root;
		node *previous = NULL;
		node *next = root->next;

		while (temp != NULL)
		{
			if (temp->name == name || (temp->xCoord == x && temp->yCoord == y))
			{
				//delete node
				delete temp;
				//direct pointer of the item just before deleted node to the node just after the delete node
				if (previous != NULL) //make sure there is a previous and we aren't deleting the first node
					previous->next = next;
				else if (next != NULL)
					root = next;	//if we are deleting the first node, set next as root
				else
					root = NULL;	//we are deleting the only node so root = NULL
				return 0;
			}
			previous = temp;
			temp = previous->next;
			next = temp->next;
		}

		return 1;
	}
	catch (exception& e)
	{
		return 2;
	}


}

void linkedList_searchByName(string name)
{
	node *temp = root;
	bool found = false;

	while (temp != NULL)
	{
		if (temp->name == name)
		{
			cout << "Name: " << temp->name << " X: " << temp->xCoord << ", Y: " << temp->yCoord << "\n";
			found = true;
		}
		temp = temp->next;
	}

	if (found == false)
	{
		cout << "No such record exists in the existing data set. \n";
	}
}

void linkedList_searchByCoordinate(double x, double y)
{
	node *temp = root;
	bool found = false;

	while (temp != NULL)
	{
		if (temp->xCoord == x && temp->yCoord)
		{
			cout << "Name: " << temp->name << " X: " << temp->xCoord << ", Y: " << temp->yCoord << "\n";
			found = true;
		}
		temp = temp->next;
	}

	if (found == false)
	{
		cout << "No such record exists in the existing data set. \n";
	}
}

void linkedList_searchWithinDistance(string name, double requestedDistance)
{
	//latitude is Y
	//longitude is X

	node *temp = root;
	node *center;
	bool found = false;
	double centerXRad = 0;
	double centerYRad = 0;
	double compareXRad = 0;
	double compareYRad = 0;

	//first find coordinates of our 'center' node
	while (temp != NULL)
	{
		if (temp->name == name)
		{
			center = temp;
			//convert center points coordinates to radians
			centerXRad = center->xCoord * (3.1415926535 / 180);
			centerYRad = center->yCoord * (3.1415926535 / 180);
		}
		temp = temp->next;
	}

	//now that we found center, set temp back to root so we can use it to navigate our list again
	temp = root;

	//now search through each item in the list and see if its coordinates are within 'distance' of the center
	while (temp != NULL)
	{
		//convert center points coordinates to radians
		compareXRad = temp->xCoord * (3.1415926535/180.0);
		compareYRad = temp->yCoord * (3.1415926535/180.0);

		//perform distance calculation
		double e = acos(sin(centerYRad)*sin(compareYRad) + cos(centerYRad)*cos(compareYRad)*cos(compareXRad - centerXRad));
		//multiply by radius of equator
		double distance = e * 3963.191;

		if (distance <= requestedDistance && temp->name != name)
		{
			cout << "Name: " << temp->name << " X Coord: " << temp->xCoord << ", Y Coord: " << temp->yCoord << "\n";
			found = true;
		}

		//check next node
		temp = temp->next;
	}

	if (found == false)
	{
		cout << "No records found  \n";
	}
}
