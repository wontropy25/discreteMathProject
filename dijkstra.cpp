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
vector<vector<int>> matrix; // ���� ���
vector<int> V, S, dist, path; // V: ��ü ���� ����, S: ����� ���� ����, dist: �� ���� �ִܰŸ�, path: �� ���� �ִܰ�� 

bool comp(int a, int b) {
	return dist[a] < dist[b];
}

void dijkstra() {

	for (int i = 2; i <= n; i++) {
		dist[i] = matrix[1][i]; // D�� �ʱ�ȭ
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

		for (int v : result) {
			if (dist[v] > dist[w] + matrix[w][v]) {
				dist[v] = dist[w] + matrix[w][v];
				path[v] = w;
			}
		}
	}
}

void printResult(int graphNum) {
	cout << "�׷��� [" << graphNum << "]" << endl << "------------------------------------" << endl;
	cout << "������: 1" << endl;

	for (int i = 2; i <= n; i++) {

		/* �ִܰ�θ� ���ÿ� �����Ͽ� ���������� ��� */
		int u = i, v = 1;
		stack<int> s;
		s.push(u);

		while (u != v) {
			int next = path[u]; // ���� ��� Ž��
			s.push(next);
			u = next;
		}

		cout << "���� [" << i << "] : ";

		while (!s.empty()) {
			if (s.size() > 1)
				cout << s.top() << " - ";
			else
				cout << s.top() << ", ";
			s.pop();
		}
		cout << "����: " << dist[i] << endl;
	}
	cout << "====================================" << endl << endl;
}

void init() {
	matrix.clear();
	V.clear();
	S.clear();
	dist.clear();
	path.clear();
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
			dist.resize(n + 1);
			path.resize(n + 1, 1);

			for (int i = 0; i <= n; i++) {
				vector<int> tp(n + 1, INF);
				matrix.push_back(tp);
				if (i != 0) V.push_back(i);
			}

			dist[1] = 0; // source
			S.push_back(1);

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

			dijkstra();

			printResult(graphNum++);

			continue;
		}
		fin.clear();
	}
}