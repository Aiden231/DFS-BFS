#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11
#define TRUE 1
#define FALSE 0

typedef struct graphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct graphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;
// �ʱ�ȭ �Լ�
void init_graph(GraphType* g)
{
	g->n = 0;

	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}
// vertex �߰� �Լ�
void insert_vertex(GraphType* g, int n)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷��� : ������ ���� �ʰ� ����\n");
		return;
	}
	g->n++; // ���� ���� �ذ��ؾߵ� 
}
// edge �߰� �Լ�
void insert_edge(GraphType* g, int u,int v)
{
	GraphNode* node;
	if (u >= g || v >= g->n) {
		fprintf(stderr, "�׷��� : ���� ��ȣ ����\n");
		return;
	}

	node = (GraphNode*)malloc(sizeof(GraphNode));

	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}
// ���� ����Ʈ ���
void print_adj_list(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("���� %d�� ���� ����Ʈ", i);
		while (p != NULL) {
			printf("-> %d", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}
// ���� ����ü
#define MAX_STACK_SIZE 100
typedef struct stack {
	int data[MAX_STACK_SIZE];
	int top;
}Stack;
// ���� �ʱ�ȭ �Լ�
init_stack(Stack* s) {
	s->top = -1;
}
// ���� Ȯ�� �Լ�
int is_Empty(Stack* s) {
	return (s->top == -1);
}
// ��ȭ Ȯ�� �Լ�
int is_Full(Stack* s) {
	return (s->top == MAX_STACK_SIZE-1);
}
// ���� ����
void push(Stack* s,int value) {
	if (!is_Full(s)) {
		s->data[++s->top] = value;
	}
}
// ���� ��
int pop(Stack* s) {
	if (!is_Empty(s)) {
		return s->data[s->top--];
	}
	return -1;
}
// ���� �켱 Ž���� ���� search �Լ�
int visit[MAX_VERTICES];
void dfs_search(GraphType* g, int v,int search,int* visit_count)
{
	memset(visit, 0, sizeof(visit)); // visit �ʱ�ȭ

	Stack s;
	init_stack(&s);

	push(&s, v);

	while (!is_Empty(&s)) {
		(*visit_count)++;
		int node = pop(&s);

		if (!visit[node]) {
			visit[node] = TRUE;
			printf("%d ", node);
			
			if (node == search) {
				printf("\nŽ�� ���� : %d\n", search);
				break; // ã���� Ż��
			}

			GraphNode* p = g->adj_list[node];
			while (p != NULL) {
				if (!visit[p->vertex]) {
					push(&s, p->vertex);
				}
				p = p->link;
			}
		}
	}
}
// ť ����
typedef struct Queue {
	int data[MAX_VERTICES];
	int front, rear;
} Queue;
// ť �ʱ�ȭ
void init_Queue(Queue* q) {
	q->front = q->rear = 0;
}
// ť ���� �˻�
int isEmpty(Queue* q) {
	return q->front == q->rear;
}
// enqueue �Լ�
void enqueue(Queue* q, int value) {
	q->data[q->rear++] = value;
}
// dequeue �Լ�
int dequeue(Queue* q) {
	if (!isEmpty(q)) {
		return q->data[q->front++];
	}
	return -1;  // ť�� ������� �� -1 ��ȯ
}
// �ʺ� �켱 Ž���� �̿��� search �Լ�
void bfs_search(GraphType* g, int v, int search, int* visit_count)
{
	memset(visit, 0, sizeof(visit)); // visit �ʱ�ȭ

	GraphNode* w;
	Queue q;

	init_Queue(&q);
	visit[v] = TRUE;

	printf("%d ", v);
	enqueue(&q, v);

	while (!isEmpty(&q)) {
		(*visit_count)++;
		v = dequeue(&q);
		
		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visit[w->vertex]) {
				visit[w->vertex] = TRUE;
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);
				// search �ϸ� Ż��
				if (w->vertex == search) {
					printf("\nŽ�� ���� : %d\n", search);
					break;
				}
			}
		}
	}
}
int main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	// �ʱ�ȭ
	init_graph(g);
	// vertex �߰�
	for (int i = 0; i < MAX_VERTICES; i++) {
		insert_vertex(g, i);
	}
	int menu_input = 0; // �޴� �Է� ����
	do {
		printf("-------------------------\n");
		printf("| 1 : ���� �켱 Ž��    |\n");
		printf("| 2 : �ʺ� �켱 Ž��    |\n");
		printf("| 3 : ����              |\n");
		printf("-------------------------\n");

		printf("\n�޴� �Է� : ");
		scanf_s("%d", &menu_input); // �޴� �Է� �ޱ�

		int start; // ���� vertex ����
		int search; // ã�� �� ����
		int visit_count = 0; // �湮 ī����

		switch (menu_input)
		{
		case 1:
			// edge �߰�
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

			printf("���� ��ȣ�� Ž���� �� �Է�(DFS) : ");
			scanf_s("%d %d", &start, &search);
			dfs_search(g, start, search,&visit_count);
			printf("�湮�� ����� �� : %d\n\n", visit_count);
			break;
		case 2:
			// edge �߰�
			insert_edge(g, 0, 9);
			insert_edge(g, 0, 6);
			insert_edge(g, 0, 5);
			insert_edge(g, 0, 4);
			insert_edge(g, 0, 2);

			insert_edge(g, 1, 10);
			insert_edge(g, 1, 7);
			insert_edge(g, 1, 5);
			insert_edge(g, 1, 4);

			insert_edge(g, 2, 4);
			insert_edge(g, 2, 3);
			insert_edge(g, 2, 0);

			insert_edge(g, 3, 5);
			insert_edge(g, 3, 4);
			insert_edge(g, 3, 2);

			insert_edge(g, 4, 7);
			insert_edge(g, 4, 6);
			insert_edge(g, 4, 5);
			insert_edge(g, 4, 3);
			insert_edge(g, 4, 2);
			insert_edge(g, 4, 1);
			insert_edge(g, 4, 0);

			insert_edge(g, 5, 4);
			insert_edge(g, 5, 3);
			insert_edge(g, 5, 1);
			insert_edge(g, 5, 0);

			insert_edge(g, 6, 8);
			insert_edge(g, 6, 7);
			insert_edge(g, 6, 4);
			insert_edge(g, 6, 0);

			insert_edge(g, 7, 10);
			insert_edge(g, 7, 6);
			insert_edge(g, 7, 4);
			insert_edge(g, 7, 1);

			insert_edge(g, 8, 10);
			insert_edge(g, 8, 9);
			insert_edge(g, 8, 6);

			insert_edge(g, 9, 8);
			insert_edge(g, 9, 0);

			insert_edge(g, 10, 8);
			insert_edge(g, 10, 7);
			insert_edge(g, 10, 1);

			printf("���� ��ȣ�� Ž���� �� �Է�(BFS) : ");
			scanf_s("%d %d", &start, &search);
			bfs_search(g, start, search, &visit_count);
			printf("�湮�� ����� �� : %d\n\n", visit_count);
			break;
		case 3:
			printf("���α׷��� �����մϴ�.\n");
			break;
		default:
			printf("1���� 3 �߿� ���ڸ� �Է����ּ���\n");
			break;
		}
	} while (menu_input != 3); // 3�� �Էµ� �� ����

	free(g);
	return 0;
}