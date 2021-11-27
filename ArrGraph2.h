#pragma once
#include "Graph.h"
class ArrGraph2 :
    public Graph
{
private:
    int** Adj; //[u,v]의 dist (자신은 0, 없으면 inf)
    int** Route; // 각 정점별 최단거리로 가는 경로 저장
    int* Dist; // 각 정점별 최단거리를 저장하는 dist    
public:
    ArrGraph2(int V);
    void addEdge(int u, int v, int dist);
    void showGraph();
    int* getAdjacents(int v);
    int** getRoute();
    int* getDist();
    ~ArrGraph2();
};

