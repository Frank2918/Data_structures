//? 双向链表：一种链式数据结构，节点含数据域和双向指针，每个节点都有前驱和后继指针。

/*在双向链表中，每个节点包含一个数据域和两个指针：一个指向前一个节点（前驱），另一个指向后一个节点（后继）。
双向链表允许在任意位置进行插入和删除操作，且可以双向遍历链表。
相比单向链表，双向链表在某些操作上更为灵活，但也需要更多的内存空间来存储额外的指针。
单链表查找直接后继的时间复杂度是O(1)，查找直接前驱的时间复杂度是O(n)，而双向链表可以更高效地进行查找操作。*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
    ElemType data;
    struct node *prev, *next;
}Node;


Node* initList(){
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

//遍历
void listNode(Node* L){
    Node* p = L->next;
    while (p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


Node* get_tail(Node* L){
    Node* p = L;
    while(p->next != NULL){
        p = p->next;
    }
    return p;
}



//双向链表——头插法
int insertHead(Node* L, ElemType e){
    Node *p = (Node*)malloc(sizeof(Node*));

    p->data = e;
    p->prev = L;
    p->next = L->next;

    if(L->next != NULL){
        L->next->prev = p;
    }

    L->next = p;

    return 1;
}


//双向链表——尾插法
Node* insertTail(Node *tail, ElemType e){
    Node *p = (Node*)malloc(sizeof(Node*));
    p->data = e;
    p->prev = tail;
    tail->next = p;
    p->next = NULL;

    return p;
}


//双向链表——在指定位置插入数据
int insertNode(Node *L, int pos, ElemType e){
    Node *p = L;
    int i = 0;

    while(i < pos-1){
        p = p->next;
        i++;
        if(p == NULL){
            return 0;
        }
    }

    Node* q = (Node*)malloc(sizeof(Node*));
    q->data = e;
    q->prev = p;
    q->next = p->next;
    p->next->prev = q;
    p->next = q;

    return 1;
}


//双向链表——删除节点
int deleteNode(Node *L, int pos){
    Node *p = L;
    int i = 0;
    while(i < pos-1){
        p = p->next;
        i++;
        if(p == NULL){
            return 0;
        }
    }
    if(p->next == NULL){
        printf("要删除的位置错误\n");
    }
    Node *q = p->next;
    p->next = q->next;
    q->next->prev = p;
    free(q);

    return 1;
}



int main(int argc, char const *argv[]){

    Node *list = initList();

    insertHead(list, 10);
    insertHead(list, 20);
    insertHead(list, 30);
    listNode(list);

    Node *tail = get_tail(list);
    tail = insertTail(tail,40);
    listNode(list);

    insertNode(list, 2, 25);
    listNode(list);

    deleteNode(list, 2);
    listNode(list);
}