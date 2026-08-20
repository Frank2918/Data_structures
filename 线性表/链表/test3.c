//!单项循环链表：一种链式数据结构，节点含数据域和单向指针，且尾节点的next指向头节点，形成环。

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




//判断链表是否有环
int isCycle(Node *head){

    Node *fast = head;
    Node *slow = head;

    while(fast != NULL && slow != NULL){
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow){
            return 1;
        }
    }
    return 0;
}


//链表有环寻找入口
Node* findBegin(Node *head){
    Node *fast = head;
    Node *slow = head;

    while(fast != NULL && slow != NULL){
        fast = fast->next->next;
        slow = slow->next;

        if(slow == fast){
            Node *p = fast;
            int count = 1;
            while(p->next != slow){
                count++;
                p = p->next;
            }
            fast = head;
            slow = head;

            for(int i = 0; i < count; i++){
                fast = fast->next;
            }

            while(slow != fast){
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }
    
}



int main(int argc, char const* argv[]){

    Node *list = initList();
    Node *tail = get_tail(list);

    tail = insertTail(tail, 1);
    tail = insertTail(tail, 2);
    tail = insertTail(tail, 3);
    Node *three = tail;

    tail = insertTail(tail, 4);
    tail = insertTail(tail, 5);
    tail = insertTail(tail, 6);
    tail = insertTail(tail, 7);
    tail = insertTail(tail, 8);
    tail->next = three;

    if(isCycle(list)){
        printf("有环\n");
    }else{
        printf("无环\n");
    }

    Node *p = findBegin(list);
    printf("%d\n",p->data);

    return 0;
}