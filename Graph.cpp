#include "Graph.h"
#include <iostream>
using std::cout;
using std::endl;
#define INF 1234567890
Graph::Graph(int vertexNum) :vertexNum(vertexNum)
{
	//배열 인덱스는 1부터 VertexNum까지 사용하는것으로 통일
	//인덱스 0은 사용하지 x

	visited = new bool[vertexNum + 1];
	resetVisitArr();

	Adj = new int* [vertexNum + 1];
	for (int i = 1; i <= vertexNum; i++)
	{
		Adj[i] = new int[vertexNum + 1];
		for (int j = 1; j <= vertexNum; j++)
			Adj[i][j] = INF; //연결x
		Adj[i][i] = 0;
	}
}

void Graph::addEdge(int u, int v, int dist)
{
	Adj[u][v] = dist;
}

int* Graph::getAdjacents(int v)
{
	return Adj[v];
}

void Graph::showGraph()
{
	for (int i = 1; i <= vertexNum; i++)
	{
		cout << i << " ";
		for (int j = 1; j <= vertexNum; j++)
			if (Adj[i][j] > 0) cout << j << " " << Adj[i][j] << " ";
		cout << endl;
	}
}

void Graph::resetVisitArr()
{
	for (int i = 1; i <= vertexNum; i++)
		visited[i] = false;
}

void Graph::visit(int v)
{
	visited[v] = true;
}

bool Graph::checkVisited(int v)
{
	return visited[v];
}

int Graph::findUnVisited()
{
	for(int i = 1; i <= vertexNum; i++)
		if(!visited[i]) return i; //방문 안한 정점 발견하면 바로 반환
	return 0; //모두 방문함
}

Graph::~Graph()
{
	for (int i = 1; i <= vertexNum; i++)
		delete[] Adj[i];
	delete[] Adj;
	Adj = nullptr;

	delete[] visited;
	visited = nullptr;
}