//�˰���-�׷���2-ũ�罺Į(Graph-Kruskal)

#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

#define MaxVertices 100
#define INF 1000

int parent[MaxVertices];	//�θ���

void set_init(int n) {	//�ʱ�ȭ
	
	for (int i = 0; i < n; i++)
		parent[i] = -1;	//�Է¹��� ����ŭ -1�� �ʱ�ȭ
}

//curr ���ϴ� ������ ��ȯ// parent�� ��ġ���� ��ȯ��
int set_find(int curr) {

	if (parent[curr] == -1)	//�Է¹��� ��ġ�� �ʱ�ȭ�� ���¸� ��ȯ
		return curr;

	while (parent[curr] != -1)curr = parent[curr];	//�ƴҽ� �ƴ� �� ��ȯ
	return curr;
}

//�ΰ��� ���Ұ� ���� ������ ��ħ
void set_union(int a, int b) {

	int root1 = set_find(a);	//�Է¹��� a�� b�� ��ġ�� �ִ� parent ����Ʈ
	int root2 = set_find(b);
	
	if (root1 != root2)		//���� ��ġ�� �ƴ� ��� ����
		parent[root1] = root2;	//root2�� ��ǥ��尡 ��
	//���� ������ parent �迭���� ��ǥ ������ ��ġ�� ����Ŵ

	/*
	printf("parent\n");
	for (int i = 0; i < 4; i++) {
		printf("%d ", parent[i]);
	}
	printf("\n");
	*/
}

struct Edge {	//������ ��Ÿ���� ����ü

	int start, end, weight;
	//���� �糡�� �ִ� ������ ������ ������ ���� ����
};

typedef struct GraphType {

	int n;	//������ ����
	int nvertex;	//������ ����
	struct Edge edges[2 * MaxVertices];

}GraphType;

//�׷��� �ʱ�ȭ
void graph_init(GraphType* g) {

	g->n = g->nvertex = 0;	//������ ���� 0���� �ʱ�ȭ
	for (int i = 0; i < MaxVertices; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;	//1000
	}
}

//���� ����
void insert_edge(GraphType* g, int Start, int End, int Weight) {

	g->edges[g->n].start = Start;
	g->edges[g->n].end = End;
	g->edges[g->n].weight = Weight;
	g->n++;	//n�� ������ ����
}

//qsort()�� ���Ǵ� �Լ�, ����ü ��, ����
int compare(const void* a, const void* b) {

	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);	//�ΰ��� ����ġ �� �� ����
}

//Kruskal �ּ� ��� ���� Ʈ�� ���α׷�
void Kruskal(GraphType* g) {
	
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->nvertex);	//parent ����Ʈ�� ������ ������ŭ 0���� �ʱ�ȭ
	qsort(g->edges, g->n, sizeof(struct Edge), compare);	//�������� ����

	printf("ũ�罺Į �ּ� ���� Ʈ�� �˰���\n");
	int i = 0;
	while (edge_accepted< (g->nvertex-1))	//������ Ʈ�� �����Ǽ�
	{
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);		//��ġ�� ������ ���������� �θ��带 ����Ŵ

		//
		//printf("\nuset = %d, vset = %d", uset, vset);
		//printf("\n");
		//
		
		if (uset != vset) {	//���� ���� ������ �ٸ��ٸ�
			printf("����(%d, %d) %d����\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	//�ΰ��� ������ ����
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
		printf("\n parent �迭 Ȯ��\n");
		for (int i = 0; i < g->nvertex; i++) {
			printf("%d ", parent[i]);
		}
		*/

		free(g);
	}
	else printf("g�� �޸𸮰� �������� �Ҵ���� �ʾҽ��ϴ�.");

	return 0;
}

/*
	   2
	0 �Ѥ� 1_
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

kruskal �˰��� ���� �� parent �迭

 0  1  2  3
-1 -1 -1 -1

===============Kruskal �˰��� ����==================

-first round

2�� 3 ��� ����(weight�� 1��, weight�� ���� ����)

2____ 3
   1

parent �迭 ��ȭ

 0  1  2  3
-1 -1  3 -1

root1 = 2, root2 = 3
parent[root1] = root2

-----------------------------------------------------

-Second round

1�� 2 ��� ����(weight�� 2��, weight�� �ι�°�� ����)

		   1
		 /
	  2 / 
	   /
	   2_____ 3
		  1

parent �迭 ��ȭ

 0  1  2  3
-1  3  3 -1

root1 = 1, root2 = 3
parent[root1] = root2

-----------------------------------------------------

-Third round

0�� 1 ��� ����(weight�� 2��, weight�� �ι�°�� ����)

		2
	0 �Ѥ� 1
		  /
	   2 /
		/
	   /
	   2_____ 3
		  1

parent �迭 ��ȭ

 0  1  2  3
 3  3  3 -1

root1 = 0, root2 = 3
parent[root1] = root2



*/