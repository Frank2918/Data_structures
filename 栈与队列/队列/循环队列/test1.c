//!循环队列

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int ElemType;

typedef struct{
    ElemType *data;
    int front;
    int rear;
}Queue;

//初始化
Queue* initQueue(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = (ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    q->front = 0;
    q->rear = 0;
    return q;
}

//循环队列——入队
int enqueue(Queue *Q, ElemType e){
    if((Q->rear+1) % MAXSIZE == Q->front){
        printf("队满\n");
        return 0;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear+1) % MAXSIZE;
    return 1;
}


//循环队列——出队
int dequeue(Queue *Q, ElemType *e){
    if(Q->front == Q->rear){
        printf("队空\n");
        return 0;
    }
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return 1;
}


//队列的顺序结构——获取队头元素
int getFront(Queue *Q, ElemType *e){
    if(Q->front == Q->rear){
        printf("队空\n");
        return 0;
    }
    *e = Q->data[Q->front];
    return 1; 
}



int main(int argc, char const *argv[]){
    Queue* q = initQueue();

    
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);

    ElemType e;
    dequeue(q, &e);
    printf("%d\n", e);

    getFront(q, &e);
    printf("%d\n", e);

    return 0;
}