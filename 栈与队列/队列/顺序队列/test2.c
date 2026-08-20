#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int ElemType;

//队列的顺序结构——动态内存分配
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


//队列的顺序结构——出队
ElemType dequeue(Queue *Q){
    if(Q->front == Q->rear){
        printf("队空\n");
        return 0;
    }

    ElemType e = Q->data[Q->front];
    Q->front++;

    return e;
}


//队列的顺序结构——调整队列（假溢出：由于出队，导致front队头前面有空间留出）
int queueFull(Queue *Q){
    if(Q->front > 0){
        int step = Q->front;
        for(int i = Q->front; i < Q->rear; i++){
            Q->data[i-step] = Q->data[i];
        }
        Q->front = 0;
        Q->rear = Q->rear - step;

        return 1;
    }else{
        printf("真满了\b");
        return 0;
    }
}


//队列的顺序结构——入队
int enqueue(Queue *Q, ElemType e){
    if(Q->rear >= MAXSIZE){
        if(!queueFull(Q)){
            return 0;
        }
    }
    Q->data[Q->rear] = e;
    Q->rear++;
    return 1;
}


//队列的顺序结构——获取队头元素
int getHead(Queue *Q, ElemType *e){
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

    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));

    ElemType e;
    getHead(q, &e);
    printf("%d", e);

    return 0;
}

