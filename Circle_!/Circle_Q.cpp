#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
	element* data;
	int capacity;
	int front, rear, count;
}QueueType;

void error(const char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = -1;
	q->count = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear && q->count==0);
}

int is_full(QueueType* q) {
	return (q->count==q->capacity);
}

void queue_print(QueueType* q) {
	printf("QUEUE(front=%d rear=%d count=%d) = ", q->front+1, q->rear+1, q->count);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (q->capacity);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void resize(QueueType* q, element item) {
	int* temp;
	temp = q->data;

	if (is_full(q)) {
		q->capacity *= 2;
		q->data = (int*)realloc(q->data, q->capacity * sizeof(int));
	}
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		resize(q,item);
	}
	q->rear = (q->rear+1) % q->capacity;
	q->data[q->rear] = item;
	q->count++;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % q->capacity;
	q->count--;
	return q->data[q->front];
}

element peek(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % q->capacity];
}

int main(void) {
	QueueType queue;
	int element=1;
	queue.data = (int*)malloc(sizeof(int) * MAX_QUEUE_SIZE);
	queue.capacity = MAX_QUEUE_SIZE;	

	init_queue(&queue);
	printf("--데이터 추가 단계--\n");
	while (queue.count!=100) {
		enqueue(&queue, element);
		queue_print(&queue);
		element += 1;
	}


	printf("--데이터 삭제 단계--\n");
	while (!is_empty(&queue)) {
		element = dequeue(&queue);
		printf("꺼내진 정수: %d \n", element);
		queue_print(&queue);
	}
	printf("큐는 공백상태입니다\n");
	return 0;
}