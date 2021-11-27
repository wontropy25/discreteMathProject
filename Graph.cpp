#include "Graph.h"

Graph::Graph(int V) :V(V)
{
	visited = new bool[V];
	resetVisitArr();
}

void Graph::resetVisitArr()
{
	for (int i = 0; i < V; i++)
		visited[i] = false;
}

void Graph::visit(int v)
{
	visited[v - 1] = true;
}

bool Graph::checkVisited(int v)
{
	return visited[v - 1];
}

int Graph::findUnVisited()
{
	for(int i = 0; i<V; i++)
		if(!visited[i]) return i+1; //방문 안한 노드 발견하면 번호 반환
	return 0; //모두 방문함
}