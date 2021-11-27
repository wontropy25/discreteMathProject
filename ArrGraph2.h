#pragma once
#include "Graph.h"
class ArrGraph2 :
    public Graph
{
private:
    int** Adj; //[u,v]�� dist (�ڽ��� 0, ������ inf)
    int** Route; // �� ������ �ִܰŸ��� ���� ��� ����
    int* Dist; // �� ������ �ִܰŸ��� �����ϴ� dist    
public:
    ArrGraph2(int V);
    void addEdge(int u, int v, int dist);
    void showGraph();
    int* getAdjacents(int v);
    int** getRoute();
    int* getDist();
    ~ArrGraph2();
};

