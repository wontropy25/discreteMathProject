#include "GetInput.h"

using namespace std;
void readFile_1(std::istream& in)
{
	unsigned int numOfNodes;
	while (true)
	{
		std::map<int, Node*> mapNodeWholeNodes;
		in >> numOfNodes;
		if (!in.fail())
		{
			for (unsigned int i = 0; i < numOfNodes; i++)
			{
				//read line
				in >> ws;
				std::string temp;
				getline(in, temp);
				istringstream ss(temp);

				std::string toNum;
				getline(ss, toNum, ' ');
				unsigned int fromNodeNum = static_cast<unsigned int>(std::stoi(toNum));

				std::vector<unsigned int> nextNums;
				for (; getline(ss, toNum, ' ');)
				{
					nextNums.push_back(static_cast<unsigned int>(std::stoi(toNum)));
				}

				Node* fromNode;
				if (mapNodeWholeNodes.find(fromNodeNum) != mapNodeWholeNodes.end())
				{
					fromNode = mapNodeWholeNodes.find(fromNodeNum)->second;
				}
				else
				{
					fromNode = new Node(fromNodeNum);
					mapNodeWholeNodes.insert(std::pair<int, Node*>(fromNodeNum, fromNode));
				}

				Node* nextNode;
				std::vector<Node*> nextNodeVector;
				for (auto nextIter = nextNums.begin(); nextIter != nextNums.end(); nextIter++)
				{
					if (mapNodeWholeNodes.find(*nextIter) != mapNodeWholeNodes.end())
					{
						nextNode = mapNodeWholeNodes.find(*nextIter)->second;
					}
					else
					{
						nextNode = new Node(*nextIter);
						mapNodeWholeNodes.insert(std::pair<int, Node*>(*nextIter, nextNode));
					}
					nextNodeVector.push_back(nextNode);
				}
				fromNode->addNextsNode(nextNodeVector);
			}

			//test
			std::cout << "-----------------------------" << std::endl;
			for (auto iter = mapNodeWholeNodes.begin(); iter != mapNodeWholeNodes.end(); iter++)
			{
				iter->second->printInfo();
			}
			for (auto iter = mapNodeWholeNodes.begin(); iter != mapNodeWholeNodes.end(); iter++)
			{
				delete iter->second;
			}
			mapNodeWholeNodes.clear();
			continue;
		}
		if (in.eof())
		{
			break;
		}
		in.clear();
	}
}