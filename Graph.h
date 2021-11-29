#pragma once
class Graph
{
protected:
	int vertexNum; //vertex 수
	bool* visited; //방문 여부 배열
	int** Adj; //[u,v]의 dist (자신은 0, 없으면 -1) 
public:
	Graph(int vertexNum);

	void addEdge(int u, int v, int dist=1);
	int* getAdjacents(int v); //정점 v의 인접 배열반환
	void showGraph();

	void resetVisitArr();
	void visit(int v);
	bool checkVisited(int v); //정점 v를 방문했는지 반환
	int findUnVisited(); //방문 안한 정점 번호 하나 반환
	
	~Graph();
};