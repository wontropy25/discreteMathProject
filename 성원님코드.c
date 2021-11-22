#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INF 10000;

int number;//��� ����
int** arr; //���� ���� ����ġ�� ������ 2���� �迭
int** route;//�� ������ �ִ� ��θ� ������ 2���� �迭
int* D;//���� ������ �� ����� ���� �Ÿ�
bool* V;//���õ� �������� index�� true�� ��ȯ... ���� ���õǾ��� ������ false.

int readfile(FILE* fp);
int getSmallIndex(int number);
void printRoute(int start);
void dijkstra(int start);

int main() {
    FILE* fp;
    fp = fopen("input2.txt", "r");
    int count;//�׷��� ����
    int start;
    while (!feof(fp)) {
        count = 1;
        printf("�׷��� [%d]\n", count);
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
    /* �� ���� ù ��°�� ������(1)���� �����ϰ� �������� 0���� �ʱ�ȭ*/
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number; j++) {
            if (j == 0)
                route[i][j] = start;
            else
                route[i][j] = 0;
        }
    }

    /* D,V �ʱ�ȭ */
    for (int i = 0; i < number; i++) {
        D[i] = arr[start - 1][i];
        V[i] = false;
    }

    V[start - 1] = true; //������ true

    for (int i = 0; i < number - 1; i++) {
        int minIndex = getSmallIndex(number);
        V[minIndex] = true;
        route[0][minIndex]++; //route[][]�� ù ��° ���� �� �������� start���� �����ϰ� ������ ��� ���� �Է�
        route[minIndex][route[0][minIndex]] = minIndex + 1; // �ּ� ��� �������� �ڽ� ��� �Է�

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

/* D���� �ּҰ��� ���� index ã��*/
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
    printf("������: %d", start);
    for (int i = 0; i < number; i++) {
        if ((start - 1) != i) {
            printf("����[%d]: ", i + 1);
            for (int j = 0; j <= route[0][i]; j++) {
                if (j == route[0][i])
                    printf("%d", route[i][j]);
                else
                    printf("%d - ", route[i][j]);
            }
            printf(", ����: %d", D[i]);
        }
        printf("\n\n");
    }
}

int readfile(FILE* fp) {
    int number; //��� ����
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