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

}