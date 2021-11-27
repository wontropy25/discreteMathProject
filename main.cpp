#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Graph.h"
#include "ArrGraph.h"
#include "ArrGraph2.h"
#include "Queue.h"

#define INF 1234567890

using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::getline;
using std::min;
using std::vector;

void CallDFS(Graph* G, int VertexNum, int v);
void DFS(Graph* G, int VertexNum, int v);
void BFS(Graph* G, int VertexNum, int v);
void dijkstra(Graph* G, int VertexNum, int start);
void printRoute(Graph* G, int VertexNum, int start);

int main(void)
{
	//���� 1
	ifstream fin("input.txt");
	if (!fin.is_open())
	{
		cerr << "���� ���� ����";
		exit(0);
	}
	int VertexNum, graphNum = 0;
	while (fin >> VertexNum)
	{
		fin.ignore(255, '\n');
		graphNum++;
		Graph* G = new ArrGraph(VertexNum);
		string line;
		stringstream ss;
		int u, v;
		for (int i = 0; i < VertexNum; i++)
		{
			getline(fin, line);
			ss.clear();
			ss.str(line);
			ss >> u;
			while (ss >> v) G->addEdge(u, v);
		}
		cout << endl << "�׷��� [" << graphNum << "]" << endl;
		G->showGraph();
		cout << "--------------------------------" << endl;
		cout << "���� �켱 Ž��" << endl;
		CallDFS(G, VertexNum, 1);
		cout << "�ʺ� �켱 Ž��" << endl;
		BFS(G, VertexNum, 1);
		cout << "================================" << endl;
		delete G;
	}

	//���� 2
	ifstream fin2("input2.txt");
	if (!fin2.is_open())
	{
		cerr << "���� ���� ����";
		exit(0);
	}
	//int VertexNum
	graphNum = 0;
	while (fin2 >> VertexNum)
	{
		fin2.ignore(255, '\n');
		graphNum++;
		Graph* G = new ArrGraph2(VertexNum);
		string line;
		stringstream ss;
		int u, v, dist;
		for (int i = 0; i < VertexNum; i++)
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
		cout << endl << "�׷��� [" << graphNum << "]" << endl;
		//G->showGraph();
		cout << "--------------------------------" << endl;
		cout << "���ͽ�Ʈ�� �˰���" << endl;
		dijkstra(G, VertexNum, 1);
		printRoute(G, VertexNum, 1);
		cout << "================================" << endl;
		delete G;
	}
}

void CallDFS(Graph* G, int VertexNum, int v)
{
	G->resetVisitArr();
	while (v)
	{
		DFS(G, VertexNum, v);
		v = G->findUnVisited();
		cout << "\b\b\b   " << endl;
	}
}

void DFS(Graph* G, int VertexNum, int v)
{
	G->visit(v);
	cout << v << " - ";
	int* adj = G->getAdjacents(v);
	for (int w=1; w <= VertexNum; w++)
		if ((adj[w-1] > 0) && !(G->checkVisited(w))) DFS(G, VertexNum, w);
}

void BFS(Graph* G, int VertexNum, int v)
{
	G->resetVisitArr();
	G->visit(v);
	cout << v << " - ";
	Queue Q;
	while (v)
	{
		int* adj = G->getAdjacents(v);
		for (int i = 1; i <= VertexNum; i++)
			if ((adj[i - 1] > 0) && !(G->checkVisited(i)))
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


void dijkstra(Graph* G, int VertexNum, int start) {
	int n = VertexNum;
	ArrGraph2* AG = (ArrGraph2*)G;
	int** route = AG->getRoute();
	int* dist = AG->getDist();

	dist[start] = 0;
	AG->visit(start - 1);

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			if (j == 0)	route[i][j] = start;
			else route[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (i != start)
			dist[i] = AG->getAdjacents(start)[i]; // D�� �ʱ�ȭ
	}

	for (int i = 1; i <= n; i++) {
		int minNum = INF, w = 0;
		for (int v = 1; v <= n; v++) {
			if (!(AG->checkVisited(v - 1))) {
				if (minNum > dist[v]) {
					minNum = dist[v];
					w = v;
				}
			}
		}

		if (w > 0) {
			G->visit(w-1);

			route[start - 1][w]++; //route[][]�� ù ��° ���� �� �������� start���� �����ϰ� ������ ��� ���� �Է�
			route[w][route[start - 1][w]] = w; // �ּ� ��� �������� �ڽ� ��� �Է�

			for (int v = 1; v <= n; v++) {
				if (!(AG->checkVisited(v - 1))) {
					if (dist[v] > dist[w] + AG->getAdjacents(w)[v]) {
						dist[v] = dist[w] + AG->getAdjacents(w)[v];

						for (int k = 0; k < n; k++) {
							route[v][k] = route[w][k];
						}
						route[start - 1][v] = route[start - 1][w];
					}
				}
			}
		}
		
	}
}

void printRoute(Graph* G, int VertexNum, int start) {
	int n = VertexNum;
	ArrGraph2* AG = (ArrGraph2*)G;
	int** route = AG->getRoute();
	int* dist = AG->getDist();

	printf("������: %d\n", start);
	for (int i = 1; i <= n; i++) {
		if ( dist[i] > 0 && dist[i] != INF) {
			printf("����[%d]: ", i);
			for (int j = 0; j <= route[start - 1][i]; j++) {
				if (j == route[start - 1][i])
					printf("%d", route[i][j]);
				else
					printf("%d - ", route[i][j]);
			}
			printf(", ����: %d", dist[i]);
			printf("\n");
		}
	}

}