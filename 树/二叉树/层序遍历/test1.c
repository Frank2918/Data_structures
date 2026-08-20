#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef char TreeType;

typedef struct TreeNode
{
    TreeType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

typedef TreeNode *ElemType;

// 存放树节点的队列
typedef struct
{
    ElemType *data;
    int front;
    int rear;
} Queue;

typedef TreeNode *BiTree;

char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

// 构建树（二级指针）
void createTree(BiTree *T)
{
    TreeType ch;
    ch = str[idx++];
    if (ch == '#')
    {
        (*T) = NULL;
    }
    else
    {
        (*T) = (BiTree)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        createTree(&(*T)->lchild);
        createTree(&(*T)->rchild);
    }
}

// 初始化队列
Queue *initQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
    q->front = 0;
    q->rear = 0;
    return q;
}

int isEmpty(Queue *Q)
{
    if (Q->front == Q->rear)
    {
        printf("队空\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

// 循环队列——入队
int enqueue(Queue *Q, ElemType e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
    {
        printf("队满\n");
        return 0;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
}

// 循环队列——出队
int dequeue(Queue *Q, ElemType *e)
{
    if (Q->front == Q->rear)
    {
        printf("队空\n");
        return 0;
    }
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return 1;
}

// 获取队列元素个数
int queueSize(Queue *Q)
{
    if (isEmpty(Q))
    {
        return 0;
    }
    if (Q->rear >= Q->front)
    {
        return Q->rear - Q->front;
    }
    return Q->rear + MAXSIZE - Q->front;
}

int maxDepth(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int depth = 0;
    Queue *q = initQueue();
    enqueue(q, root);

    while (!isEmpty(q))
    {
        int count = queueSize(q);
        while (count > 0)
        {
            TreeNode *curr;
            dequeue(q, &curr);
            if (curr->lchild != NULL)
            {
                enqueue(q, curr->lchild);
            }
            if (curr->rchild != NULL)
            {
                enqueue(q, curr->rchild);
            }
            count--;
        }
        depth++;
    }
    return depth;
}

int main(int argc, char const *argv[])
{
    BiTree T;
    createTree(&T);
    printf("%d\n", maxDepth(T));
    return 0;
}