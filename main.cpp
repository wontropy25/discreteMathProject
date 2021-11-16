#include "GetInput.h"

using namespace std;

int main() {
	/* 1. 파일 입출력 처리 */
	string fileName1 = "input.txt";
	string fileName2 = "input2.txt";

	fstream fin;
	fin.open(fileName1, ios_base::in);
	readFile_1(fin);

	fin.close();

	fin.open(fileName2, ios_base::in);
	readFile_2(fin);

	fin.close();


	/* 2. 1번 과제 (관계 행렬) */
	vector<vector<int>> graph1;


	/* 3. 2번 과제 (가중치 행렬) */
	vector<vector<int>> graph2;
	

}

