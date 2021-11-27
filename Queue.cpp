#include "Queue.h"

void Queue::enQueue(int data)
{
	Node* newNode = new Node(data);
	if (front)
	{
		rear->next = newNode;
		rear = newNode;
	}
	else //empty
	{
		front = newNode;
		rear = newNode;
	}
}

int Queue::deQueue()
{
	if (!front) //empty
		return -1;
	Node* temp = front;
	int data = front->data;
	front = front->next;
	if (!front) rear = nullptr;
	delete temp;
	return data;
}

Queue::~Queue()
{
	front->deleteList();
	front = nullptr;
	rear = nullptr;
}