#include "Node.h"
#include <iostream>

void Node::addNodeEnd(int data, int dist)
{
	Node* temp = this;
	Node* traveler = this->next;
	while (traveler != nullptr)
	{
		temp = traveler;
		traveler = traveler->next;
	}
	temp->next = new Node(data, dist);
}

void Node::addNodeFront(int data, int dist)
{
	Node* temp = this->next;
	this->next = new Node(data, dist);
	this->next->next = temp;
}

void Node::showList()
{
	Node* traveler = this->next;
	while (traveler)
	{
		std::cout << traveler->data << " " << traveler->dist << " ";
		traveler = traveler->next;
	}
}

void Node::deleteList()
{
	Node* traveler = this;
	while (traveler)
	{
		Node* temp = traveler->next;
		delete traveler;
		traveler = temp;
	}
}