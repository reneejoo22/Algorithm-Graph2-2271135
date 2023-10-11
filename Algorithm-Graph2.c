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

//curr ���ϴ� ������ ��ȯ
int set_find(int curr) {

	if (parent[curr] == -1)	//�Է¹��� ��ġ�� �ʱ�ȭ�� ���¸� ��ȯ
		return curr;	
	while (parent[curr] != -1)curr = parent[curr];	//�ƴҽ� �ƴ� �� ��ȯ
	return curr;
}

//�ΰ��� ���Ұ� ���� ������ ��ħ
void set_union(int a, int b) {

}