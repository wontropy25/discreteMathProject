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
		G->showGraph();
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
		G->showGraph();
		cout << "--------------------------------" << endl;
		cout << "다익스트라 알고리즘" << endl;
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
		dist[i] = G->getAdjacents(start)[i]; // D값 초기화(Adj[start] 복사해옴)
		//if (i != start)
		//dist[start] = 0;
		//Graph 생성자에서 Adj[i][i] = 0; 로 자신->자신의 dist는 0으로 초기화해 뒀으므로 필요x

	int** route = new int* [vertexNum + 1];
	
	/*	route는 V*V짜리 2차원배열
	* route의 start행의 각 칸에는 목표 정점을 인덱스로 하여 start정점에서 각 목표 정점으로 갈때 거치는 edge의 개수 저장
	* //start-1행으로 하면 start가 1이 아닐 때 해당 목적정점의 행과 start-1행이 겹쳐서 수정!
	* 다른 행들에는 각 행 번호를 목표 정점으로 하여 거쳐가는 경로들을 저장
	* 첫번째 행 route[0]은 사용하지x
	*
	* ex) 방향 그래프가 1 -> 2 -> 3 이면 start=1일 때
	*   0 1 2 3
	* 0 x x x x -> 첫번째 행은 사용x
	* 1 x 0 1 2 -> 정점[1]로 가는 최단경로는 0개의 edge 포함 / 정점[2]로 가는 최단경로는 1개의 edge 포함 / 정점[3]로 가는 최단경로는 2개의 edge 포함
	* 2 1 2 0 0 -> 정점[2]로 가는 최단경로는 1 - 2
	* 3 1 2 3 0 -> 정점[3]로 가는 최단경로는 1 - 2 - 3	*/
	for (int i = 0; i <= vertexNum; i++)
	{
		route[i] = new int[vertexNum + 1];
		route[i][0] = start; //route의 0열은 start로 초기화(경로에 start도 포함되므로)
		for (int j = 1; j <= vertexNum; j++)
			route[i][j] = 0; //route 칸들 0으로 초기화
	}

	G->visit(start); //S에 start 추가

	for (int r = 1; r <= vertexNum; r++)
	{
		int minNum = INF, w = 0;
		for (int i = 1; i <= vertexNum; i++) {
			if (!(G->checkVisited(i)) && minNum > dist[i])//방문 안한 노드 중//minNum보다 거리 짧으면 (이중if문 하나로 수정)
			{ 
				minNum = dist[i]; //minNum갱신
				w = i; //minNum인 정점 w에 저장
			}
		}

		if (w > 0) { //w가 갱신됐으면
			G->visit(w); //w방문(S에 추가)
			if (++route[start][w] > vertexNum) //start행 w칸에 w로 가는 경로의 edge 수++
			{
				cerr << "route 배열 크기 초과"; //예외처리추가(경고메세지 계속떠서...ㅎ)
				exit(0);
			}
			route[w][route[start][w]] = w; //start에서 w로 가는 경로를 저장하는 w행 맨 뒤에 w 추가

			for (int i = 1; i <= vertexNum; i++) {
				if (!(G->checkVisited(i)) && dist[i] > dist[w] + G->getAdjacents(w)[i]) { //방문 안한 노드이고 //기존 경로보다 w를 거쳐가는게 가까우면(거쳐갈 때 연결되지 않은 노드면 INF가 더해지니까 커서 알아서 제껴짐)
					//이중 if문 하나로 수정
					dist[i] = dist[w] + G->getAdjacents(w)[i]; //dist 갱신

					for (int k = 0; k < vertexNum; k++)
						route[i][k] = route[w][k]; //dist 갱신한 i의 route 행에 w의 것을 가져와 복붙교체
					route[start][i] = route[start][w];
				}
			}
		}
		
	}

	//print
	cout << "시작점: " << start << endl;
	for (int i = 1; i <= vertexNum; i++)
	{
		if (dist[i] > 0 && dist[i] != INF)
		{
			cout << "정점[" << i << "]: ";
			for (int j = 0; j <= route[start][i]; j++)
				cout << route[i][j] << " - ";
			cout << "\b\b\b, 길이: " << dist[i] << endl;
		}
	}
}

//void printRoute(DijkstraGraph* G, int vertexNum, int start) {
//	int n = vertexNum;
//	int** route = G->getRoute();
//	int* dist = G->getDist();
//
//	cout << "시작점: " << start << endl;
//	for (int i = 1; i <= n; i++) {
//		if ( dist[i] > 0 && dist[i] != INF) { //본인 제외 && 무한대경로(이어지지못함)도 제외
//			cout << "정점[" << i << "]: ";
//			for (int j = 0; j <= route[start - 1][i]; j++) {
//				//route의 start행에는 경로에 포함된 정점 개수가 도착 정점 인덱스마다 저장되어있음
//				//j는 '도착 정점'행을 경로의 개수만큼 순회
//				cout << route[i][j] << " - "; //route의 '도착 정점' 행에는 방문 경로 정점들이 순서대로 저장되어 있음
//				//if (j == route[start - 1][i]) //마지막에 인데 for문 끝나고 해도 동일결과
//				//	cout << "\b\b\b";
//			}
//			cout << "\b\b\b, 길이: " << dist[i] << endl;
//		}
//	}
//}