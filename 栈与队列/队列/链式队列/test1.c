#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

//队列的链式存储结构
typedef struct QueueNode{
    ElemType data;
    struct QueueNode *next;
}QueueNode;

typedef struct{
    QueueNode *front;
    QueueNode *rear;
}Queue;


//链队——初始化
Queue* initQueue(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));

    node->data = 0;
    node->next = NULL;

    q->front = node;
    q->rear = node;

    return q;
}


//链队——判断队列是否为空
int isEmpty(Queue *Q){
    if(Q->front == Q->rear){
        printf("队空\n");
        return 1;
    }else{
        return 0;
    }
}


//链队——入队
void enqueue(Queue *q, ElemType e){
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = e;
    node->next = NULL;

    q->rear->next = node;
    q->rear = node;
}


//链队——出队
int dequeue(Queue *q, ElemType *e){
    QueueNode *node = q->front->next;
    *e = node->data;
    q->front->next = node->next;

    if(node == q->rear){
        q->rear = q->front;
    }
    free(node);
    return 1;
}


//链队——获取队头元素
ElemType getFront(Queue *q){
    if(isEmpty(q)){
        printf("队空\n");
        return 0;
    }
    return q->front->next->data;
}



int main(int argc, char const *argv[]){
    Queue* q = initQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);

    ElemType e;
    dequeue(q, &e);
    printf("出队元素：%d\n", e);

    printf("获取队头元素：%d\n", getFront(q));

    return 0;
}