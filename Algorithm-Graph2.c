//알고리즘-그래프2-플로이드(Graph-Floyd)

#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

#define MaxVertices 100
#define INF 1000000

typedef struct GraphType {

	int n;	//정점의 개수
	int weight[MaxVertices][MaxVertices];	//가중치 값 저장, 인접행렬
}GraphType;

int A[MaxVertices][MaxVertices];

void printA(GraphType* g) {

	int i, j;
	printf("=======================\n");
	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			if (A[i][j] == INF)
				printf(" * ");
			else printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	printf("=======================\n");
}


void floyd(GraphType* g) {

	int i, j, k;

	for (i = 0; i < g->n; i++)		//가중치 값으로 A를 초기화
		for (j = 0; j < g->n; j++)
			A[i][j] = g->weight[i][j];
	printA(g);

	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
		printA(g);
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

	floyd(&g);

	return 0;
}
