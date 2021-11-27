#pragma once
class Node
{
public:
	int data;
	int dist;
	Node* next = nullptr;
	Node() = default;
	Node(int data, int dist = -1) :data(data) {}
	void addNodeEnd(int data, int dist = -1);
	void addNodeFront(int data, int dist = -1);
	void showList();
	void deleteList();
};