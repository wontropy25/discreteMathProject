#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Graph.h"
#include "Queue.h"

#define INF 1234567890

using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::string;
using std::stringstream;
using std::getline;

void CallDFS(Graph* G, int vertexNum, int v);
void DFS(Graph* G, int vertexNum, int v);
void BFS(Graph* G, int vertexNum, int v);
void dijkstra(Graph* G, int vertexNum, int start);

int main(void)
{
	//문제 1
	ifstream fin("input.txt");
	if (!fin.is_open())
	{
		cerr << "파일 오픈 실패";
		exit(0);
	}
	int vertexNum, graphNum = 0;
	string line;
	stringstream ss;
	while (fin >> vertexNum)
	{
		fin.ignore(255, '\n');
		graphNum++;
		Graph* G = new Graph(vertexNum);
		int u, v;
		for (int i = 0; i < vertexNum; i++)
		{
			getline(fin, line);
			ss.clear();
			ss.str(line);
			ss >> u;
			while (ss >> v) G->addEdge(u, v);
		}
		cout << endl << "그래프 [" << graphNum << "]" << endl;
		//G->showGraph();
		cout << "--------------------------------" << endl;
		cout << "깊이 우선 탐색" << endl;
		CallDFS(G, vertexNum, 1);
		cout << "너비 우선 탐색" << endl;
		BFS(G, vertexNum, 1);
		cout << "================================" << endl;
		delete G;
	}
	fin.close();

	//문제 2
	ifstream fin2("input2.txt");
	if (!fin2.is_open())
	{
		cerr << "파일 오픈 실패";
		exit(0);
	}
	graphNum = 0;
	while (fin2 >> vertexNum)
	{
		fin2.ignore(255, '\n');
		graphNum++;
		Graph* G = new Graph(vertexNum);
		int u, v, dist;
		for (int i = 0; i < vertexNum; i++)
		{
			getline(fin2, line);
			ss.clear();
			ss.str(line);
			ss >> u;
			while (ss >> v)
			{
				ss >> dist;
				G->addEdge(u, v, dist);
			}
		}
		cout << endl << "그래프 [" << graphNum << "]" << endl;
		//G->showGraph();
		cout << "--------------------------------" << endl;
		cout << "다익스트라 알고리즘" << endl;
		dijkstra(G, vertexNum, 1);
		cout << "================================" << endl;
		delete G;
	}
	fin2.close();
}

void CallDFS(Graph* G, int vertexNum, int v)
{
	G->resetVisitArr();
	while (v)
	{
		DFS(G, vertexNum, v);
		v = G->findUnVisited();
		cout << "\b\b\b   " << endl;
	}
}

void DFS(Graph* G, int vertexNum, int v)
{
	G->visit(v);
	cout << v << " - ";
	int* adj = G->getAdjacents(v);
	for (int w = 1; w <= vertexNum; w++)
		if ((adj[w] > 0) && (adj[w] != INF) && !(G->checkVisited(w))) DFS(G, vertexNum, w);
}

void BFS(Graph* G, int vertexNum, int v)
{
	G->resetVisitArr();
	G->visit(v);
	cout << v << " - ";
	Queue Q;
	while (v)
	{
		int* adj = G->getAdjacents(v);
		for (int i = 1; i <= vertexNum; i++)
			if ((adj[i] > 0) && (adj[i] != INF) && !(G->checkVisited(i)))
			{
				G->visit(i);
				cout << i << " - ";
				Q.enQueue(i);
			}
		if ((v = Q.deQueue()) == -1) //Q is empty
		{
			v = G->findUnVisited();
			if (v)
			{
				G->visit(v);
				cout << "\b\b\b   " << endl;
				cout << v << " - ";
			}
		}
	}
	cout << "\b\b\b   " << endl;
}

void dijkstra(Graph* G, int vertexNum, int start)
{
	int* dist = new int[vertexNum+1];
	for (int i = 0; i <= vertexNum; i++)
		dist[i] = G->getAdjacents(start)[i]; //dist 값 초기화 (인접행렬의 start행 복사)

	int** route = new int* [vertexNum+1];
	/* route의 start행의 각 칸에는 목표 정점을 인덱스로 하여 start정점에서 각 목표 정점으로 갈때 거치는 edge의 개수 저장
	* 다른 행들에는 각 행 번호를 목표 정점으로 하여 거쳐가는 경로들을 저장 (첫번째 행 route[0]은 사용x)
	* ex) 방향 그래프가 1 -> 2 -> 3 이면 start = 1일 때
	* 0 1 2 3
	* 0 x x x x->첫번째 행은 사용x
	* 1 x 0 1 2->정점[1]로 가는 최단경로는 0개의 edge 포함 / 정점[2]로 가는 최단경로는 1개의 edge 포함 / 정점[3]로 가는 최단경로는 2개의 edge 포함
	* 2 1 2 0 0->정점[2]로 가는 최단경로는 1 - 2
	* 3 1 2 3 0->정점[3]로 가는 최단경로는 1 - 2 - 3 */

	for (int i = 0; i <= vertexNum+1; i++)
	{
		route[i] = new int[vertexNum+1];
		route[i][0] = start;
		for (int j = 1; j <= vertexNum; j++)
			route[i][j] = 0;
	}

	G->resetVisitArr();
	G->visit(start); // add start to S (visit)
	for (int i = 1; i <= vertexNum; i++)
	{
		int minNum = INF, w = 0;
		for (int j = 1; j <= vertexNum; j++) 
		{ //choose a vertex w in V - S (= Unvisited) such that dist[w] is minimum;
			if (!(G->checkVisited(j)) && minNum > dist[j])
			{ 
				minNum = dist[j];
				w = j;
			}
		}

		if (w != 0) { //if w is chosen
			G->visit(w); //add w to S (visit)
			if (++route[start][w] > vertexNum) //start행 w칸에 w로 가는 경로의 edge 수++
			{
				cerr << "route 배열 크기 초과";
				exit(0);
			}
			route[w][route[start][w]] = w; //start에서 w로 가는 경로를 저장하는 w행 맨 뒤에 w 추가

			for (int v = 1; v <= vertexNum; v++) {
				if (!(G->checkVisited(v)) && dist[v] > dist[w] + G->getAdjacents(w)[v])
					//each vertex v in V-S && 기존 경로보다 w 경유한 경로가 짧으면
				{
					dist[v] = dist[w] + G->getAdjacents(w)[v]; //최단경로 거리 갱신

					for (int j = 0; j < vertexNum; j++) //최단경로 정보 갱신(w행의 경로를 v행에 copy&paste)
						route[v][j] = route[w][j];
					route[start][v] = route[start][w]; //start행의 v칸도 w칸 값으로 변경
				}
			}
		}
	}

	cout << "시작점: " << start << endl;
	for (int j = 1; j <= vertexNum; j++)
	{
		if (dist[j] > 0 && dist[j] != INF)
		{
			cout << "정점[" << j << "]: ";
			for (int k = 0; k <= route[start][j]; k++)
				cout << route[j][k] << " - ";
			cout << "\b\b\b, 길이: " << dist[j] << endl;
		}
	}
}