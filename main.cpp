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
	//���� 1
	ifstream fin("input.txt");
	if (!fin.is_open())
	{
		cerr << "���� ���� ����";
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
		cout << endl << "�׷��� [" << graphNum << "]" << endl;
		//G->showGraph();
		cout << "--------------------------------" << endl;
		cout << "���� �켱 Ž��" << endl;
		CallDFS(G, vertexNum, 1);
		cout << "�ʺ� �켱 Ž��" << endl;
		BFS(G, vertexNum, 1);
		cout << "================================" << endl;
		delete G;
	}
	fin.close();

	//���� 2
	ifstream fin2("input2.txt");
	if (!fin2.is_open())
	{
		cerr << "���� ���� ����";
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
		cout << endl << "�׷��� [" << graphNum << "]" << endl;
		//G->showGraph();
		cout << "--------------------------------" << endl;
		cout << "���ͽ�Ʈ�� �˰���" << endl;
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
		dist[i] = G->getAdjacents(start)[i]; //dist �� �ʱ�ȭ (��������� start�� ����)

	int** route = new int* [vertexNum+1];
	/* route�� start���� �� ĭ���� ��ǥ ������ �ε����� �Ͽ� start�������� �� ��ǥ �������� ���� ��ġ�� edge�� ���� ����
	* �ٸ� ��鿡�� �� �� ��ȣ�� ��ǥ �������� �Ͽ� ���İ��� ��ε��� ���� (ù��° �� route[0]�� ���x)
	* ex) ���� �׷����� 1 -> 2 -> 3 �̸� start = 1�� ��
	* 0 1 2 3
	* 0 x x x x->ù��° ���� ���x
	* 1 x 0 1 2->����[1]�� ���� �ִܰ�δ� 0���� edge ���� / ����[2]�� ���� �ִܰ�δ� 1���� edge ���� / ����[3]�� ���� �ִܰ�δ� 2���� edge ����
	* 2 1 2 0 0->����[2]�� ���� �ִܰ�δ� 1 - 2
	* 3 1 2 3 0->����[3]�� ���� �ִܰ�δ� 1 - 2 - 3 */

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
			if (++route[start][w] > vertexNum) //start�� wĭ�� w�� ���� ����� edge ��++
			{
				cerr << "route �迭 ũ�� �ʰ�";
				exit(0);
			}
			route[w][route[start][w]] = w; //start���� w�� ���� ��θ� �����ϴ� w�� �� �ڿ� w �߰�

			for (int v = 1; v <= vertexNum; v++) {
				if (!(G->checkVisited(v)) && dist[v] > dist[w] + G->getAdjacents(w)[v])
					//each vertex v in V-S && ���� ��κ��� w ������ ��ΰ� ª����
				{
					dist[v] = dist[w] + G->getAdjacents(w)[v]; //�ִܰ�� �Ÿ� ����

					for (int j = 0; j < vertexNum; j++) //�ִܰ�� ���� ����(w���� ��θ� v�࿡ copy&paste)
						route[v][j] = route[w][j];
					route[start][v] = route[start][w]; //start���� vĭ�� wĭ ������ ����
				}
			}
		}
	}

	cout << "������: " << start << endl;
	for (int j = 1; j <= vertexNum; j++)
	{
		if (dist[j] > 0 && dist[j] != INF)
		{
			cout << "����[" << j << "]: ";
			for (int k = 0; k <= route[start][j]; k++)
				cout << route[j][k] << " - ";
			cout << "\b\b\b, ����: " << dist[j] << endl;
		}
	}
}