#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <string>
#include <sstream>

#define INF 1234567890

using namespace std;

int n;
vector<vector<int>> matrix, route; // ���� ���, �� ������ �ִܰ��
vector<int> V, S, dist; // V: ��ü ���� ����, S: ����� ���� ����, dist: �� ���� �ִܰŸ�

bool comp(int a, int b) {
	return dist[a] < dist[b];
}

void dijkstra(int start) {

	for (int i = 0; i < n+1; i++) {
		for (int j = 0; j < n+1; j++) {
			if (j == 0)	route[i][j] = start;
			else route[i][j] = 0;
		}
	}

	for (int i = 1; i <= n; i++) {
		if (i != start)
			dist[i] = matrix[start][i]; // D�� �ʱ�ȭ
	}

	for (int i = 1; i <= n - 1; i++) {

		/* Result: V-S ���� ���� */
		vector<int> result;
		result.resize(V.size() + S.size());
		sort(S.begin(), S.end());
		auto it = set_difference(V.begin(), V.end(), S.begin(), S.end(), result.begin()); // ������
		result.erase(it, result.end()); // �������� ����
		sort(result.begin(), result.end(), comp); // �Ÿ��� ����

		int w = result[0];
		S.push_back(w);

		route[start-1][w]++; //route[][]�� ù ��° ���� �� �������� start���� �����ϰ� ������ ��� ���� �Է�
		route[w][route[start - 1][w]] = w; // �ּ� ��� �������� �ڽ� ��� �Է�

		for (int v : result) {
			if (dist[v] > dist[w] + matrix[w][v]) {
				dist[v] = dist[w] + matrix[w][v];
				//path[v] = w;

				for (int k = 0; k < n; k++) {
					route[v][k] = route[w][k];
				}
				route[start - 1][v] = route[start - 1][w];
			}
		}
	}
}

void printRoute(int start, int graphNum) {
	cout << "�׷��� [" << graphNum << "]" << endl << "------------------------------------" << endl;
	printf("������: %d\n", start);
	for (int i = 1; i <= n; i++) {
		if (dist[i] > 0) {
			printf("����[%d]: ", i);
			for (int j = 0; j <= route[start-1][i]; j++) {
				if (j == route[start-1][i])
					printf("%d", route[i][j]);
				else
					printf("%d - ", route[i][j]);
			}
			printf(", ����: %d", dist[i]);
			printf("\n");
		}
	}	
	cout << "------------------------------------" << endl;

}

void init() {
	matrix.clear();
	V.clear();
	S.clear();
	dist.clear();
	route.clear();
}

int main() {

	fstream fin;
	fin.open("input2.txt", ios_base::in);
	int graphNum = 1;

	while (true)
	{
		init();

		if (!fin.fail())
		{
			if (fin.eof())
			{
				break;
			}

			fin >> n;
			dist.resize(n + 1, -1);

			for (int i = 0; i <= n; i++) {
				vector<int> tp(n + 1, INF);
				matrix.push_back(tp);
				route.push_back(tp);
				if (i != 0) V.push_back(i);
			}

			int start = 1;
			dist[start] = 0; // source
			S.push_back(start);

			fin >> ws;

			for (unsigned int i = 1; i <= n; i++)
			{
				std::string temp;
				getline(fin, temp);
				istringstream ss(temp);

				std::string toNum;
				getline(ss, toNum, ' ');
				unsigned int fromNodeNum = static_cast<unsigned int>(std::stoi(toNum));

				for (; getline(ss, toNum, ' ');)
				{
					int toNodeNum = static_cast<int>(std::stoi(toNum));
					getline(ss, toNum, ' ');
					int weight = static_cast<int>(std::stoi(toNum));
					matrix[fromNodeNum][toNodeNum] = weight;
				}
			}

			dijkstra(start);

			printRoute(start, graphNum++);
			cout << endl;
			continue;
		}
		fin.clear();
	}
}