#include <stdio.h>
#include <stdlib.h>


/*链表
链表：由一系列节点组成的线性表，每个节点包含数据元素和一个指向下一个节点的指针。
链表的特点是：支持动态内存分配，插入和删除操作效率较高；访问效率较低，因为需要从头节点开始逐个访问。
*/


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


//单链表——头插法(插入数据的顺序与输入顺序相反)
int insertHead(Node* L, ElemType e){
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->next = L->next;
    L->next = p;
    return 1;
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


//单链表——在指定位置插入数据
int insertNode(Node* L, int pos, ElemType e){

    //用来保存插入位置的前驱节点
    Node* p = L;
    int i = 0;

    //遍历链表找到插入位置的前驱节点
    while(i < pos-1){
        p = p->next;
        i++;
        if (p == NULL){
            return 0;
        }

    }

    //插入新节点
    Node* q = (Node*)malloc(sizeof(Node));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 1;
}


//单链表——删除节点
int deleteNode(Node* L, int pos){

    //保存要删除节点的前驱
    Node* p = L;
    int i = 0;

    //遍历链表找到要删除节点的前驱
    while(i < pos-1){
        p = p->next;
        i++;

        /*if判断的作用是检查在移动指针p时是否已经达到链表末尾,防止在遍历链表时越界,这是一个安全边界检查*/                   
        if (p == NULL){
            return 0;
        }
    }

    if (p->next == NULL){
        printf("要删除的位置错误\n");
        return 0;
    }

    //q指向要删除的节点
    Node* q = p->next;
    //让要删除节点的前驱指向要删除节点的后继
    p->next = q->next;
    //释放要删除节点的内存空间
    free(q);
    return 1;
}


//单链表——获取链表长度
int listLength(Node* L){
    Node* p = L;
    int len = 0;

    while(p != NULL){
        p = p->next;
        len++;    
    }
    return len;
}


//单链表——释放链表
void freeNode(Node* L){
    Node* p = L->next;
    Node* q;

    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}
















int main(int argc, char const *argv[]){
    //创建单链表并初始化
    Node* list = initList();

    //头插法插入数据
    insertHead(list, 10);
    insertHead(list, 15);

    //遍历
    listNode(list);

    //尾插法插入数据并遍历
    Node* tail = get_tail(list);
    tail = insertTail(tail, 20);
    tail = insertTail(tail, 30);
    listNode(list);

    //在指定位置插入数据
    insertNode(list, 2, 12);
    listNode(list);

    //删除数据
    deleteNode(list, 2);
    listNode(list);

    //获取链表长度
    printf("%d\n",listLength(list));

    //释放链表
    freeNode(list);
    printf("%d\n",listLength(list));

    return 0;

}