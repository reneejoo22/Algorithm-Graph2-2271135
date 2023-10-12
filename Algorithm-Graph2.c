//�˰���-�׷���2-����(Graph-Prim)

#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

#define MaxVertices 100
#define INF 1000L


typedef struct GraphType {

	int n;	//������ ����
	int weight[MaxVertices][MaxVertices];

}GraphType;

int selected[MaxVertices];
int distance[MaxVertices];

//�ּ� dist[v]���� ���� ���� ��ȯ
int getMinVertex(int n) {

	int v = 0, i;
	for(i = 0; i < n; i++)
		if (!selected[i]) {	//������ �ȵ� �� �� �ְ�� ����
			v = i;
			break;
		}
	for (i = 0; i < n; i++)	//���� ���ų� �� Ŭ��
		if (!selected[i] && (distance[i] < distance[v]))v = i;
	return(v);

}

void prim(GraphType* g, int s) {

	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF;
	distance[s] = 0;
	for (i = 0; i < g->n; i++) {	//��� ����ŭ
		u = getMinVertex(g->n);	//������ ��
		selected[u] = True;	//�� 1�� ����
		
		if (distance[u] == INF)return;
		printf("���� %d �߰�\n", u);

		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];
	}
}


int main(void) {

	//������� 
	GraphType g = { 7,
	{{0,29,INF,INF,INF,10,INF},
	{29,0,16,INF,INF,INF,15},
	{INF,16,0,12,INF,INF,INF},
	{INF,INF,12,0,22,INF,18},
	{INF,INF,INF,22,0,27,25},
	{10,INF,INF,INF,27,0,INF},
	{INF,15,INF,18,25,INF,0}}
	};

	prim(&g, 0);

	//return 0;
}
