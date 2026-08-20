#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;


//链表——存储结构
typedef struct node{
    ElemType data;
    struct node* next;
}Node;


//单链表——初始化
Node* initList(){
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

//单链表——遍历
void listNode(Node* L){
    Node* p = L->next;
    while (p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//单链表——获取尾节点
Node* get_tail(Node* L){
    Node* p = L;
    while(p->next != NULL){
        p = p->next;
    }
    return p;
}

//单链表——尾插法
Node* insertTail(Node* tail, ElemType e){
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    tail->next = p;
    p->next = NULL;
    return p;
}






//双指针查找倒数第k个节点
int findNodeFS(Node *L, int k ){
    Node *fast = L->next;
    Node *slow = L->next;

    for (int i = 0;i < k;i++){
        fast = fast->next;
    }

    while(fast != NULL){
        fast = fast->next;
        slow = slow->next;
    }

    printf("倒数第%d个节点的值为%的\n", k, slow->data);

    return 1;
}


//查找两个链表共同后缀的起始位置
Node* findIntersectionNode(Node *HeadA, Node *HeadB){

    if(HeadA == NULL || HeadB == NULL){
        return NULL;
    }

    Node *p = HeadA;
    int lenA = 0;
    int lenB = 0;

    //获取A,B的长度
    while(p != NULL){
        p = p->next;
        lenA++;
    }
    p = HeadB;
    while(p != NULL){
        p = p->next;
        lenB++;
    }

    Node *fast;
    Node *slow;
    int step;

    if(lenA > lenB){
        step  = lenA - lenB;
        fast = HeadA;
        slow = HeadB;
    }
    else
    {
         step  = lenB - lenA;
        fast = HeadB;
        slow = HeadA;
    }
    //快指针先走step步
    for(int i = 0; i < step; i++){
        fast = fast->next; 
    }
    //同时走，直到指向同一个节点
    while(fast!=slow){
        fast = fast->next;
        slow = slow->next;
    }

    return fast;
}


//删除绝对值相同的节点(拿空间换时间)
void removeNode(Node *L, int n){
    Node *p = L;
    int index; //作数组下标
    int *q = (int*)malloc(sizeof(int)*(n+1));

    //用指针操作数组，初始化为0
    for(int i = 0; i < n+1; i++){
        *(q+i) = 0;
    }

    while(p->next != NULL){
        index = abs(p->next->data);
        if(*(q+index) == 0){
            *(q+index) == 1;
            p = p->next;
        }
        else
        {
           Node *temp = p->next;
           p->next = temp->next;
           free(temp); 
        }
    }
    free(q);
}


//反转链表
Node* reverseList(Node *head){
    Node *first = NULL;
    Node *second = head->next;
    Node *third;

    while(second != NULL){
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }

    Node *hd = initList();
    hd->next = first;

    return hd;
}


//删除链表中间节点
int delMiddlNode(Node* head){
    Node *fast = head->next;
    Node *slow = head;

    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }

    Node *q = slow->next;
    slow->next = q->next;
    free(q);

    return 1;
}


//链表重新排序
int reOrderList(Node* head){

    Node *fast = head->next;
    Node *slow = head;

    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }

    Node *first = NULL;
    Node *second = slow->next;
    slow->next = NULL;
    Node *third = NULL;

    while(second != NULL){
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }

    Node *p1 = head->next;
    Node *q1 = first;
    Node *p2, *q2;
    while(p1 != NULL && q1 != NULL){
        p2 = p1->next;
        q2 = q1->next;

        p1->next = q1;
        q1->next = p2;

        p1 = p2;
        q1 = q2;
    }
    return 1;

}


int main(int argc, char const* argv[]){

    Node *list = initList();
    Node *tail = get_tail(list);

    tail = insertTail(tail, 1);
    tail = insertTail(tail, 2);
    tail = insertTail(tail, 3);
    tail = insertTail(tail, 4);
    tail = insertTail(tail, 5);
    tail = insertTail(tail, 6);
    
    listNode(list);
    reOrderList(list);
    listNode(list);

    return 0;

}
















