#include "GetInput.h"

using namespace std;

size_t index(int row, int col, unsigned int numOfNodes)
{
	return numOfNodes * row + col;
}

void readFile_2(std::istream& in)
{
	unsigned int numOfNodes;
	while (true)
	{
		in >> numOfNodes;
		int** matrix = new int*[numOfNodes];
        for(int i = 0;i<numOfNodes;i++){
            matrix[i] = new int[numOfNodes];
            fill(matrix[i], matrix[i] + (numOfNodes), -1);
        }

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

				for (; getline(ss, toNum, ' ');)
				{
					int toNodeNum = static_cast<int>(std::stoi(toNum));
					getline(ss, toNum, ' ');
					int weight = static_cast<int>(std::stoi(toNum));

					matrix[fromNodeNum - 1][toNodeNum - 1] = weight;
				}
			}

			//test
			std::cout << "-----------------------------" << std::endl;
			for (unsigned int y = 0; y < numOfNodes; y++)
			{
				for (unsigned int x = 0; x < numOfNodes; x++)
				{
					std::cout << setw(3) << matrix[y][x] << " ";
				}
				std::cout << std::endl;
			}

			for(int i = 0;i<numOfNodes;i++){
				delete[] matrix[i];
			}
			delete[] matrix;
			continue;
		}
		if (in.eof())
		{
			break;
		}
		in.clear();
	}
}