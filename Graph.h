#pragma once
class Graph
{
protected:
	int vertexNum; //vertex ��
	bool* visited; //�湮 ���� �迭
	int** Adj; //[u,v]�� dist (�ڽ��� 0, ������ -1) 
public:
	Graph(int vertexNum);

	void addEdge(int u, int v, int dist=1);
	int* getAdjacents(int v); //���� v�� ���� �迭��ȯ
	void showGraph();

	void resetVisitArr();
	void visit(int v);
	bool checkVisited(int v); //���� v�� �湮�ߴ��� ��ȯ
	int findUnVisited(); //�湮 ���� ���� ��ȣ �ϳ� ��ȯ
	
	~Graph();
};