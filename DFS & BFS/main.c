#include <stdio.h>
#define MAX_VERTICES 11

typedef struct graphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct graphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

void init_graphTyp(GraphType* g)
{
	g->n = 0;

	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType* g, int n)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점의 개수 초과 오류\n");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int u,int v)
{
	GraphNode* node;
	node = (GraphNode*)malloc(sizeof(GraphNode));

	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void print_adj_list(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 인접 리스트", i);
		while (p != NULL) {
			printf("-> %d", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

int main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));

	init_graphTyp(g);

	for (int i = 0; i < MAX_VERTICES; i++) {
		insert_vertex(g, i);
	}

	insert_edge(g, 0, 2);
	insert_edge(g, 0, 4);
	insert_edge(g, 0, 5);
	insert_edge(g, 0, 6);
	insert_edge(g, 0, 9);

	insert_edge(g, 1, 4);
	insert_edge(g, 1, 5);
	insert_edge(g, 1, 7);
	insert_edge(g, 1, 10);

	insert_edge(g, 2, 0);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);

	insert_edge(g, 3, 2);
	insert_edge(g, 3, 4);
	insert_edge(g, 3, 5);

	insert_edge(g, 4, 0);
	insert_edge(g, 4, 1);
	insert_edge(g, 4, 2);
	insert_edge(g, 4, 3);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 6);
	insert_edge(g, 4, 7);

	insert_edge(g, 5, 0);
	insert_edge(g, 5, 1);
	insert_edge(g, 5, 3);
	insert_edge(g, 5, 4);
	
	insert_edge(g, 6, 0);
	insert_edge(g, 6, 4);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 8);

	insert_edge(g, 7, 1);
	insert_edge(g, 7, 4);
	insert_edge(g, 7, 6);
	insert_edge(g, 7, 10);

	insert_edge(g, 8, 6);
	insert_edge(g, 8, 9);
	insert_edge(g, 8, 10);

	insert_edge(g, 9, 0);
	insert_edge(g, 9, 8);

	insert_edge(g, 10, 1);
	insert_edge(g, 10, 7);
	insert_edge(g, 10, 8);

	print_adj_list(g);

	free(g);

	return 0;
}