#include "ArrGraph.h"
#include <iostream>
using std::cout;
using std::endl;

ArrGraph::ArrGraph(int V):Graph(V)
{
	Adj = new int* [V];
	for (int i = 0; i < V; i++)
	{
		Adj[i] = new int[V];
		for (int j = 0; j < V; j++)
			Adj[i][j] = -1; //����x
		Adj[i][i] = 0;
	}

	//int** Route; // �� ������ �ִܰŸ��� ���� ��� ����
	//int* Dist; // �� ������ �ִܰŸ��� �����ϴ� dist    

}

void ArrGraph::addEdge(int u, int v, int dist)
{
	Adj[u - 1][v - 1] = dist;
}

void ArrGraph::showGraph()
{
	for (int i = 1; i <= V; i++)
	{
		cout << i << " ";
		for (int j = 1; j <= V; j++)
			if (Adj[i - 1][j - 1] > 0) cout << j << " " << Adj[i - 1][j - 1] << " ";
		cout << endl;
	}
}

int* ArrGraph::getAdjacents(int v)
{
	return Adj[v-1];
}

ArrGraph::~ArrGraph()
{
	for (int i = 0; i < V; i++)
		delete[] Adj[i];
	delete[] Adj;
	Adj = nullptr;
}