//알고리즘-그래프2-크루스칼(Graph-Kruskal)

#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

#define MaxVertices 100
#define INF 1000

int parent[MaxVertices];	//부모노드

void set_init(int n) {	//초기화
	
	for (int i = 0; i < n; i++)
		parent[i] = -1;	//입력받은 값만큼 -1로 초기화
}

//curr 속하는 집합을 반환
int set_find(int curr) {

	if (parent[curr] == -1)	//입력받은 위치가 초기화된 상태면 반환
			return curr;

	while (parent[curr] != -1)curr = parent[curr];	//아닐시 아닌 값 반환
	return curr;
}

//두개의 원소가 속한 집합을 합침
void set_union(int a, int b) {

	int root1 = set_find(a);	//입력받은 a와 b의 위치에 있는 parent 리스트
	int root2 = set_find(b);
	if (root1 != root2)		//값이 같지 않을 경우 합함
		parent[root1] = root2;
}

struct Edge {	//간선을 나타내는 구조체

	int start, end, weight;
	//간선 양끝에 있는 각각의 정점과 간선에 적힌 숫자
};

typedef struct GraphType {

	int vertexNum;	//간선의 개수
	struct Edge edges[2 * MaxVertices];

}GraphType;

//그래프 초기화
void graph_init(GraphType* g) {

	g->vertexNum = 0;	//간선의 개수 0으로 초기화
	for (int i = 0; i < MaxVertices; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

//간선 삽입
void insert_edge(GraphType* g, int Start, int End, int Weight) {

	g->edges[g->vertexNum].start = Start;
	g->edges[g->vertexNum].end = End;
	g->edges[g->vertexNum].weight = Weight;
	g->vertexNum++;
}

//qsort()에 사용되는 함수, 구조체 비교
int compare(const void* a, const void* b) {

	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

//Kruskal 최소 비용 신장 트리 프로그램
void Kruskal(GraphType* g) {
	
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->vertexNum);	//parent 리스트를 간선의 개수만큼 0으로 초기화
	qsort(g->edges, g->vertexNum, sizeof(struct Edge), compare);

	printf("크루스칼 최소 신장 트리 알고리즘\n");
	int i = 0;
	while (edge_accepted< g->vertexNum)
	{
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("간선(%d, %d) %d선택\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}

int main(void) {

	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);

	Kruskal(g);
	free(g);

	return 0;
}