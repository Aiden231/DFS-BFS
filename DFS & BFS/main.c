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
// 초기화 함수
void init_graph(GraphType* g)
{
	g->n = 0;

	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}
// vertex 추가 함수
void insert_vertex(GraphType* g, int n)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점의 개수 초과 오류\n");
		return;
	}
	g->n++; // 오류 있음 해결해야됨 
}
// edge 추가 함수
void insert_edge(GraphType* g, int u,int v)
{
	GraphNode* node;
	if (u >= g || v >= g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류\n");
		return;
	}

	node = (GraphNode*)malloc(sizeof(GraphNode));

	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}
// 인접 리스트 출력
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
// 스택 구조체
#define MAX_STACK_SIZE 100
typedef struct stack {
	int data[MAX_STACK_SIZE];
	int top;
}Stack;
// 스택 초기화 함수
init_stack(Stack* s) {
	s->top = -1;
}
// 공백 확인 함수
int is_Empty(Stack* s) {
	return (s->top == -1);
}
// 포화 확인 함수
int is_Full(Stack* s) {
	return (s->top == MAX_STACK_SIZE-1);
}
// 스택 삽입
void push(Stack* s,int value) {
	if (!is_Full(s)) {
		s->data[++s->top] = value;
	}
}
// 스택 팝
int pop(Stack* s) {
	if (!is_Empty(s)) {
		return s->data[s->top--];
	}
	return -1;
}
// 깊이 우선 탐색을 통한 search 함수
int visit[MAX_VERTICES];
void dfs_search(GraphType* g, int v,int search,int* visit_count)
{
	memset(visit, 0, sizeof(visit)); // visit 초기화

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
				printf("\n탐색 성공 : %d\n", search);
				break; // 찾으면 탈출
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
// 큐 구현
typedef struct Queue {
	int data[MAX_VERTICES];
	int front, rear;
} Queue;
// 큐 초기화
void init_Queue(Queue* q) {
	q->front = q->rear = 0;
}
// 큐 공백 검사
int isEmpty(Queue* q) {
	return q->front == q->rear;
}
// enqueue 함수
void enqueue(Queue* q, int value) {
	q->data[q->rear++] = value;
}
// dequeue 함수
int dequeue(Queue* q) {
	if (!isEmpty(q)) {
		return q->data[q->front++];
	}
	return -1;  // 큐가 비어있을 때 -1 반환
}
// 너비 우선 탐색을 이용한 search 함수
void bfs_search(GraphType* g, int v, int search, int* visit_count)
{
	memset(visit, 0, sizeof(visit)); // visit 초기화

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
				// search 하면 탈출
				if (w->vertex == search) {
					printf("\n탐색 성공 : %d\n", search);
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
	// 초기화
	init_graph(g);
	// vertex 추가
	for (int i = 0; i < MAX_VERTICES; i++) {
		insert_vertex(g, i);
	}
	int menu_input = 0; // 메뉴 입력 변수
	do {
		printf("-------------------------\n");
		printf("| 1 : 깊이 우선 탐색    |\n");
		printf("| 2 : 너비 우선 탐색    |\n");
		printf("| 3 : 종료              |\n");
		printf("-------------------------\n");

		printf("\n메뉴 입력 : ");
		scanf_s("%d", &menu_input); // 메뉴 입력 받기

		int start; // 시작 vertex 변수
		int search; // 찾는 값 변수
		int visit_count = 0; // 방문 카운터

		switch (menu_input)
		{
		case 1:
			// edge 추가
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

			printf("시작 번호와 탐색할 값 입력(DFS) : ");
			scanf_s("%d %d", &start, &search);
			dfs_search(g, start, search,&visit_count);
			printf("방문한 노드의 수 : %d\n\n", visit_count);
			break;
		case 2:
			// edge 추가
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

			printf("시작 번호와 탐색할 값 입력(BFS) : ");
			scanf_s("%d %d", &start, &search);
			bfs_search(g, start, search, &visit_count);
			printf("방문한 노드의 수 : %d\n\n", visit_count);
			break;
		case 3:
			printf("프로그램을 종료합니다.\n");
			break;
		default:
			printf("1부터 3 중에 숫자를 입력해주세요\n");
			break;
		}
	} while (menu_input != 3); // 3이 입력될 시 종료

	free(g);
	return 0;
}