#pragma once
#include <vector>
#include <iostream>

struct Node
{
public:
	Node(const int nodeNumber):
		mNodeNumber(nodeNumber),
		mNextNodes(nullptr),
		curSize(0)
	{
	}

	~Node()
	{
		delete[] mNextNodes;
		// delete nodes in calling block
	}

	void addNextsNode(Node* nextNode)
	{
		mNextNodes[curSize++] = nextNode;
	}

	void addNextsNode(const std::vector<Node*>& nextNodes)
	{
		if (mNextNodes != nullptr)
		{
			delete[] mNextNodes;
		}
		mNextNodes = new Node * [nextNodes.size()];
		for (auto iter = nextNodes.begin(); iter != nextNodes.end(); iter++)
		{
			mNextNodes[curSize++] = *iter;
		}
	}

	void printInfo()
	{
		std::cout << "Node number : " << mNodeNumber;
		std::cout << " -> " << ": ";
		for (unsigned int i = 0; i < curSize; i++)
		{
			std::cout << mNextNodes[i] -> mNodeNumber << "  ";
		}
		std::cout << std::endl;
		
	}
private:
	const int mNodeNumber;
	Node** mNextNodes;
	unsigned int curSize;
};



