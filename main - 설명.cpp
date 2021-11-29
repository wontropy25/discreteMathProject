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
//void printRoute(DijkstraGraph* G, int vertexNum, int start);

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
		G->showGraph();
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
		G->showGraph();
		cout << "--------------------------------" << endl;
		cout << "���ͽ�Ʈ�� �˰���" << endl;
		dijkstra(G, vertexNum, 1);
		//printRoute(G, vertexNum, 1);
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
		if ((adj[w] > 0) && !(G->checkVisited(w))) DFS(G, vertexNum, w);
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
			if ((adj[i] > 0) && !(G->checkVisited(i)))
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


void dijkstra(Graph* G, int vertexNum, int start) {
	
	int* dist = new int[vertexNum + 1];
	for (int i = 0; i <= vertexNum; i++)
		dist[i] = G->getAdjacents(start)[i]; // D�� �ʱ�ȭ(Adj[start] �����ؿ�)
		//if (i != start)
		//dist[start] = 0;
		//Graph �����ڿ��� Adj[i][i] = 0; �� �ڽ�->�ڽ��� dist�� 0���� �ʱ�ȭ�� �����Ƿ� �ʿ�x

	int** route = new int* [vertexNum + 1];
	
	/*	route�� V*V¥�� 2�����迭
	* route�� start���� �� ĭ���� ��ǥ ������ �ε����� �Ͽ� start�������� �� ��ǥ �������� ���� ��ġ�� edge�� ���� ����
	* //start-1������ �ϸ� start�� 1�� �ƴ� �� �ش� ���������� ��� start-1���� ���ļ� ����!
	* �ٸ� ��鿡�� �� �� ��ȣ�� ��ǥ �������� �Ͽ� ���İ��� ��ε��� ����
	* ù��° �� route[0]�� �������x
	*
	* ex) ���� �׷����� 1 -> 2 -> 3 �̸� start=1�� ��
	*   0 1 2 3
	* 0 x x x x -> ù��° ���� ���x
	* 1 x 0 1 2 -> ����[1]�� ���� �ִܰ�δ� 0���� edge ���� / ����[2]�� ���� �ִܰ�δ� 1���� edge ���� / ����[3]�� ���� �ִܰ�δ� 2���� edge ����
	* 2 1 2 0 0 -> ����[2]�� ���� �ִܰ�δ� 1 - 2
	* 3 1 2 3 0 -> ����[3]�� ���� �ִܰ�δ� 1 - 2 - 3	*/
	for (int i = 0; i <= vertexNum; i++)
	{
		route[i] = new int[vertexNum + 1];
		route[i][0] = start; //route�� 0���� start�� �ʱ�ȭ(��ο� start�� ���ԵǹǷ�)
		for (int j = 1; j <= vertexNum; j++)
			route[i][j] = 0; //route ĭ�� 0���� �ʱ�ȭ
	}

	G->visit(start); //S�� start �߰�

	for (int r = 1; r <= vertexNum; r++)
	{
		int minNum = INF, w = 0;
		for (int i = 1; i <= vertexNum; i++) {
			if (!(G->checkVisited(i)) && minNum > dist[i])//�湮 ���� ��� ��//minNum���� �Ÿ� ª���� (����if�� �ϳ��� ����)
			{ 
				minNum = dist[i]; //minNum����
				w = i; //minNum�� ���� w�� ����
			}
		}

		if (w > 0) { //w�� ���ŵ�����
			G->visit(w); //w�湮(S�� �߰�)
			if (++route[start][w] > vertexNum) //start�� wĭ�� w�� ���� ����� edge ��++
			{
				cerr << "route �迭 ũ�� �ʰ�"; //����ó���߰�(���޼��� ��Ӷ���...��)
				exit(0);
			}
			route[w][route[start][w]] = w; //start���� w�� ���� ��θ� �����ϴ� w�� �� �ڿ� w �߰�

			for (int i = 1; i <= vertexNum; i++) {
				if (!(G->checkVisited(i)) && dist[i] > dist[w] + G->getAdjacents(w)[i]) { //�湮 ���� ����̰� //���� ��κ��� w�� ���İ��°� ������(���İ� �� ������� ���� ���� INF�� �������ϱ� Ŀ�� �˾Ƽ� ������)
					//���� if�� �ϳ��� ����
					dist[i] = dist[w] + G->getAdjacents(w)[i]; //dist ����

					for (int k = 0; k < vertexNum; k++)
						route[i][k] = route[w][k]; //dist ������ i�� route �࿡ w�� ���� ������ ���ٱ�ü
					route[start][i] = route[start][w];
				}
			}
		}
		
	}

	//print
	cout << "������: " << start << endl;
	for (int i = 1; i <= vertexNum; i++)
	{
		if (dist[i] > 0 && dist[i] != INF)
		{
			cout << "����[" << i << "]: ";
			for (int j = 0; j <= route[start][i]; j++)
				cout << route[i][j] << " - ";
			cout << "\b\b\b, ����: " << dist[i] << endl;
		}
	}
}

//void printRoute(DijkstraGraph* G, int vertexNum, int start) {
//	int n = vertexNum;
//	int** route = G->getRoute();
//	int* dist = G->getDist();
//
//	cout << "������: " << start << endl;
//	for (int i = 1; i <= n; i++) {
//		if ( dist[i] > 0 && dist[i] != INF) { //���� ���� && ���Ѵ���(�̾���������)�� ����
//			cout << "����[" << i << "]: ";
//			for (int j = 0; j <= route[start - 1][i]; j++) {
//				//route�� start�࿡�� ��ο� ���Ե� ���� ������ ���� ���� �ε������� ����Ǿ�����
//				//j�� '���� ����'���� ����� ������ŭ ��ȸ
//				cout << route[i][j] << " - "; //route�� '���� ����' �࿡�� �湮 ��� �������� ������� ����Ǿ� ����
//				//if (j == route[start - 1][i]) //�������� �ε� for�� ������ �ص� ���ϰ��
//				//	cout << "\b\b\b";
//			}
//			cout << "\b\b\b, ����: " << dist[i] << endl;
//		}
//	}
//}