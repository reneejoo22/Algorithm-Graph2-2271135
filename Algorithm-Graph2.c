//�˰���-�׷���2-����ũ��Ʈ��(Graph-dijkstra)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define True 1
#define False 0
#define MaxVertices 100
#define INF 1000000

typedef struct GraphType {
	int n;	//������ ����
	int weight[MaxVertices][MaxVertices];
}GraphType;

int distance[MaxVertices];	//�����������κ��� �ִܰ���� �Ÿ�
int found[MaxVertices];	//�湮�� ���� ǥ��

int choose(int distance[], int n, int found[]) {

	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {	//0�� ������ �̾��� �ٸ� ���� �� ����ġ�� ���� ���� ��
			min = distance[i];
			minpos = i;	//���° �ڸ��� �ִ����� �����ϴ� ��ġ ��
		}
	//printf("\nminpos: %d\n", minpos);
	return minpos;	//��ġ ���� ����
}

void print_status(GraphType* g) {

	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");

	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)	//���� ���� ��� * ���
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}

void shortest_path(GraphType* g, int start) {

	int i, u, w;

	for (i = 0; i < g->n; i++) {	//����0�� ���� ��� ������ �ʱ�ȭ
		distance[i] = g->weight[start][i];	//����ġ	
		found[i] = False;	//���� 0����
	}
	found[start] = True;	// found:  1  0  0  0  0  0  0
	distance[start] = 0;	// distance:  0  7  *  *  3 10  *

	for (i = 0; i < g->n - 1; i++) {	//����-1��ŭ, 6��
		print_status(g);	//�Է� �� found�� distance�� ���
		u = choose(distance, g->n, found);	//ù��° ������ ���� ����� ������ ��ġ �� ����
		found[u] = True;	//��ġ�� �ڸ��� 1 ���� ����

		
		for (w = 0; w < g->n; w++) {
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					//���� ���� ���� ����+ �� ������ ���� ����� �͵� ã��
					distance[w] = distance[u] + g->weight[u][w];
		}
	}
}
	
int main(void) {

	GraphType g = { 7,
	{{0,7,INF,INF,3,10,INF},
	{7,0,4,10,2,6,INF},
	{INF,4,0,2,INF,INF,INF},
	{INF,10,2,0,11,9,4},
	{3,2,INF,11,0,INF,5},
	{10,6,INF,9,INF,0,INF},
	{INF,INF,INF,4,5,INF,0}}
	};

	shortest_path(&g, 0);
	
	return 0;
}
