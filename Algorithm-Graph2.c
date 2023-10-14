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
		if (distance[i] < min && !found[i]) {	//0의 정점과 이어진 다른 정점 중 가중치가 가장 작은 것
			min = distance[i];
			minpos = i;	//몇번째 자리에 있는지를 저장하는 위치 값
		}
	//printf("\nminpos: %d\n", minpos);
	return minpos;	//위치 값을 보냄
}

void print_status(GraphType* g) {

	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");

	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)	//값이 없는 경우 * 출력
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

	for (i = 0; i < g->n; i++) {	//정점0의 인접 행렬 값으로 초기화
		distance[i] = g->weight[start][i];	//가중치	
		found[i] = False;	//전부 0으로
	}
	found[start] = True;	// found:  1  0  0  0  0  0  0
	distance[start] = 0;	// distance:  0  7  *  *  3 10  *

	for (i = 0; i < g->n - 1; i++) {	//정점-1만큼, 6번
		print_status(g);	//입력 된 found와 distance값 출력
		u = choose(distance, g->n, found);	//첫번째 정점과 가장 가까운 정점의 위치 값 저장
		found[u] = True;	//위치한 자리에 1 값을 넣음

		
		for (w = 0; w < g->n; w++) {
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					//가장 작은 정점 값과+ 그 정점의 가장 가까운 것들 찾기
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
