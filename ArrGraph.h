#pragma once
#include "Graph.h"
class ArrGraph :
    public Graph
{
private:
    int** Adj; //[u,v]�� dist (�ڽ��� 0, ������ -1) 
public:
    ArrGraph(int V);
    void addEdge(int u, int v, int dist);
    void showGraph();
    int* getAdjacents(int v);
    ~ArrGraph();
};