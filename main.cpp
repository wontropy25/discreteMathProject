#include "GetInput.h"

using namespace std;

int main() {
	/* 1. ���� ����� ó�� */
	string fileName1 = "input.txt";
	string fileName2 = "input2.txt";

	fstream fin;
	fin.open(fileName1, ios_base::in);
	readFile_1(fin);

	fin.close();

	fin.open(fileName2, ios_base::in);
	readFile_2(fin);

	fin.close();


	/* 2. 1�� ���� (���� ���) */
	vector<vector<int>> graph1;


	/* 3. 2�� ���� (����ġ ���) */
	vector<vector<int>> graph2;
	

}

