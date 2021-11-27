#pragma once
#include "Node.h"
class Queue
{
private:
	Node* front;
	Node* rear;
public:
	Queue() :front(nullptr), rear(nullptr) {}
	void enQueue(int data);
	int deQueue();
	~Queue();
};