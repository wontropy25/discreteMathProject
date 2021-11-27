#pragma once
class Graph
{
protected:
	int V; //vertex ¼ö
	bool* visited;
public:
	Graph(int V);
	virtual void addEdge(int u, int v, int dist=1) = 0;
	virtual void showGraph()=0;
	int getV() { return V; }
	void resetVisitArr();
	void visit(int v);
	bool checkVisited(int v);
	int findUnVisited();
	virtual int* getAdjacents(int v) = 0;
	//virtual ~Graph()=0;
};