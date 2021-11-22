#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INF 10000;

int number;//노드 개수
int** arr; //노드들 간의 가중치를 저장할 2차원 배열
int** route;//각 노드들의 최단 경로를 저장할 2차원 배열
int* D;//시작 노드부터 각 노드의 도달 거리
bool* V;//선택된 정점들의 index를 true로 반환... 아직 선택되었지 않으면 false.

int readfile(FILE* fp);
int getSmallIndex(int number);
void printRoute(int start);
void dijkstra(int start);

int main() {
    FILE* fp;
    fp = fopen("input2.txt", "r");
    int count;//그래프 개수
    int start;
    while (!feof(fp)) {
        count = 1;
        printf("그래프 [%d]\n", count);
        printf("------------------------------\n");
        number = readfile(fp);
        start = 1;
        dijkstra(start);
        printRoute(start);

        free(D);
        for (int i = 0; i < number; i++) {
            free(route[i]);
        }
        free(route);

        for (int i = 0; i < number; i++) {
            free(arr[i]);
        }
        free(arr);
        count++;
    }

    fclose(fp);
    return 0;
}

void dijkstra(int start) {
    D = (int*)malloc(sizeof(int) * number);
    V = (bool*)malloc(sizeof(bool) * number);
    route = (int**)malloc(sizeof(int*) * number);
    for (int i = 0; i < number; i++) {
        route[i] = (int*)malloc(sizeof(int) * number);
    }
    /* 각 행의 첫 번째는 시작점(1)으로 통일하고 나머지는 0으로 초기화*/
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number; j++) {
            if (j == 0)
                route[i][j] = start;
            else
                route[i][j] = 0;
        }
    }

    /* D,V 초기화 */
    for (int i = 0; i < number; i++) {
        D[i] = arr[start - 1][i];
        V[i] = false;
    }

    V[start - 1] = true; //시작점 true

    for (int i = 0; i < number - 1; i++) {
        int minIndex = getSmallIndex(number);
        V[minIndex] = true;
        route[0][minIndex]++; //route[][]의 첫 번째 행은 각 정점들이 start점을 제외하고 지나간 경로 개수 입력
        route[minIndex][route[0][minIndex]] = minIndex + 1; // 최소 경로 마지막에 자신 노드 입력

        for (int j = 0; j < number; j++) {
            if (!V[j]) {
                if (D[minIndex] + arr[minIndex][j] < D[j]) {
                    D[j] = D[minIndex] + arr[minIndex][j];
                    for (int k = 0; k < number; k++) {
                        route[j][k] = route[minIndex][k];
                    }
                    route[0][j] = route[0][minIndex];

                }
            }
        }
    }

    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number; j++) {
            printf("%d ", route[i][j]);
        }
        printf("\n");
    }
    free(V);
}

/* D에서 최소값을 갖는 index 찾기*/
int getSmallIndex(int number) {
    int index = 0;
    int min = INF;
    for (int i = 0; i < number; i++) {
        if (!V[i] && D[i] < min) {
            min = D[i];
            index = i;
        }
    }
    return index;
}

void printRoute(int start) {
    printf("시작점: %d", start);
    for (int i = 0; i < number; i++) {
        if ((start - 1) != i) {
            printf("정점[%d]: ", i + 1);
            for (int j = 0; j <= route[0][i]; j++) {
                if (j == route[0][i])
                    printf("%d", route[i][j]);
                else
                    printf("%d - ", route[i][j]);
            }
            printf(", 길이: %d", D[i]);
        }
        printf("\n\n");
    }
}

int readfile(FILE* fp) {
    int number; //노드 개수
    fscanf(fp, "%d\n", &number);
    arr = (int**)malloc(sizeof(int*) * number);
    for (int i = 0; i < number; i++) {
        arr[i] = (int*)malloc(sizeof(int) * number);
    }

    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number; j++) {
            if (i == j) {
                arr[i][j] = 0;
            }
            else {
                arr[i][j] = INF;
            }
        }
    }
    char line[1024];
    char* token;

    for (int i = 0; i < number; i++) {
        fgets(line, 1024, fp);
        token = strtok(line, " ");
        while ((token = strtok(NULL, " ")) != NULL) {
            int a = atoi(token);
            token = strtok(NULL, " ");
            int b = atoi(token);
            arr[i][a - 1] = b;
        }
    }
    return number;
}