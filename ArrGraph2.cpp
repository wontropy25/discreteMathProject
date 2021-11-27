#include "ArrGraph2.h"
#include <iostream>

using std::cout;
using std::endl;

#define INF 1234567890

ArrGraph2::ArrGraph2(int V) :Graph(V)
{
	Adj = new int* [V + 1];
	Route = new int* [V + 1];
	Dist = new int[V + 1];
	for (int i = 0; i <= V; i++)
	{
		Adj[i] = new int[V + 1];
		for (int j = 0; j <= V; j++)
			Adj[i][j] = INF;
		Adj[i][i] = 0;

		Route[i] = new int[V + 1];

		Dist[i] = -1;
	}
}

void ArrGraph2::addEdge(int u, int v, int dist)
{
	Adj[u][v] = dist;
}

void ArrGraph2::showGraph()
{
	for (int i = 1; i <= V; i++)
	{
		cout << i << " ";
		for (int j = 1; j <= V; j++)
			if (Adj[i][j] > 0) cout << j << " " << Adj[i][j] << " ";
		cout << endl;
	}
}

int* ArrGraph2::getAdjacents(int v)
{
	return Adj[v];
}

int** ArrGraph2::getRoute()
{
	return Route;
}

int* ArrGraph2::getDist()
{
	return Dist;
}

ArrGraph2::~ArrGraph2()
{
	for (int i = 0; i < V + 1; i++)
		delete[] Adj[i];
	delete[] Adj;
	Adj = nullptr;
}