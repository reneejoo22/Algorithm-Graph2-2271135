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

//curr 속하는 집합을 반환// parent의 위치값을 반환함
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
	
	if (root1 != root2)		//같은 위치가 아닐 경우 합함
		parent[root1] = root2;	//root2가 대표노드가 됨
	//하위 정점은 parent 배열에서 대표 정점의 위치를 가리킴

	/*
	printf("parent\n");
	for (int i = 0; i < 4; i++) {
		printf("%d ", parent[i]);
	}
	printf("\n");
	*/
}

struct Edge {	//간선을 나타내는 구조체

	int start, end, weight;
	//간선 양끝에 있는 각각의 정점과 간선에 적힌 숫자
};

typedef struct GraphType {

	int n;	//간선의 개수
	int nvertex;	//정점의 개수
	struct Edge edges[2 * MaxVertices];

}GraphType;

//그래프 초기화
void graph_init(GraphType* g) {

	g->n = g->nvertex = 0;	//간선의 개수 0으로 초기화
	for (int i = 0; i < MaxVertices; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;	//1000
	}
}

//간선 삽입
void insert_edge(GraphType* g, int Start, int End, int Weight) {

	g->edges[g->n].start = Start;
	g->edges[g->n].end = End;
	g->edges[g->n].weight = Weight;
	g->n++;	//n은 간선의 개수
}

//qsort()에 사용되는 함수, 구조체 비교, 정렬
int compare(const void* a, const void* b) {

	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);	//두개의 가중치 뺀 값 보냄
}

//Kruskal 최소 비용 신장 트리 프로그램
void Kruskal(GraphType* g) {
	
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->nvertex);	//parent 리스트를 간선의 개수만큼 0으로 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);	//오름차순 정렬

	printf("크루스칼 최소 신장 트리 알고리즘\n");
	int i = 0;
	while (edge_accepted< (g->nvertex-1))	//신장의 트리 간선의수
	{
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);		//위치에 갔을때 하위정점이 부모노드를 가르킴

		//
		//printf("\nuset = %d, vset = %d", uset, vset);
		//printf("\n");
		//
		
		if (uset != vset) {	//서로 속한 집합이 다르다면
			printf("간선(%d, %d) %d선택\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	//두개의 집함을 합함
		}
		i++;
	}
}

int main(void) {

	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	if (g) {

		/*
		g->nvertex = 7;
		insert_edge(g, 0, 1, 29);
		insert_edge(g, 1, 2, 16);
		insert_edge(g, 2, 3, 12);
		insert_edge(g, 3, 4, 22);
		insert_edge(g, 4, 5, 27);
		insert_edge(g, 5, 0, 10);
		insert_edge(g, 6, 1, 15);
		insert_edge(g, 6, 3, 18);
		insert_edge(g, 6, 4, 25);
		*/

		g->nvertex = 4;
		insert_edge(g, 0, 1, 2);
		insert_edge(g, 0, 2, 4);
		insert_edge(g, 1, 2, 2);
		insert_edge(g, 1, 3, 3);
		insert_edge(g, 2, 3, 1);

		Kruskal(g);

		/*
		printf("\n parent 배열 확인\n");
		for (int i = 0; i < g->nvertex; i++) {
			printf("%d ", parent[i]);
		}
		*/

		free(g);
	}
	else printf("g에 메모리가 동적으로 할당되지 않았습니다.");

	return 0;
}

/*
	   2
	0 ㅡㅡ 1_
	|     /  |
  4 |  2 /   | 3
	|   /    |
	|_ 2____ 3
		  1

Kruskal

2,3_1
 \
1,2_2
 \
0,1_2


=====================================================

kruskal 알고리즘 실행 전 parent 배열

 0  1  2  3
-1 -1 -1 -1

===============Kruskal 알고리즘 실행==================

-first round

2랑 3 노드 선택(weight가 1임, weight가 제일 작음)

2____ 3
   1

parent 배열 변화

 0  1  2  3
-1 -1  3 -1

root1 = 2, root2 = 3
parent[root1] = root2

-----------------------------------------------------

-Second round

1랑 2 노드 선택(weight가 2임, weight가 두번째로 작음)

		   1
		 /
	  2 / 
	   /
	   2_____ 3
		  1

parent 배열 변화

 0  1  2  3
-1  3  3 -1

root1 = 1, root2 = 3
parent[root1] = root2

-----------------------------------------------------

-Third round

0랑 1 노드 선택(weight가 2임, weight가 두번째로 작음)

		2
	0 ㅡㅡ 1
		  /
	   2 /
		/
	   /
	   2_____ 3
		  1

parent 배열 변화

 0  1  2  3
 3  3  3 -1

root1 = 0, root2 = 3
parent[root1] = root2



*/