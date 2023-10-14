//알고리즘-그래프2-데이크스트라(Graph-dijkstra)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define True 1
#define False 0
#define MaxVertices 100
#define INF 1000000

typedef struct GraphType {
	int n;	//정점의 개수
	int weight[MaxVertices][MaxVertices];
}GraphType;

int distance[MaxVertices];	//시작정점으로부터 최단경로의 거리
int found[MaxVertices];	//방문한 정점 표시

int choose(int distance[], int n, int found[]) {

	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g) {

	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");

	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
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
	for (i = 0; i < g->n; i++) {	//초기화
		distance[i] = g->weight[start][i];
		found[i] = False;
	}
	found[start] = True;
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = True;
		for (w = 0; w < g->n; w++) {
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
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
