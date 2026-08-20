//!链栈：1.链栈是基于链表实现的栈结构，具有动态内存分配的特点，可以根据需要动态调整栈的大小。
//!   2.链栈的基本操作包括：入栈（push）、出栈（pop）和获取栈顶元素（top）。
//!3.链栈的实现通常使用单链表或双链表来存储栈中的元素。
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

//链栈——存储结构
typedef struct stack{
    ElemType data;
    struct stack *next;
}Stack;


//链栈——初始化
Stack* initStack(){
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = 0;
    s->next = NULL;
    return s;
}


//链栈——判断栈是否为空
int isEmpty(Stack *s){
    if(s->next == NULL){
        printf("空栈\n");
        return 1;
    }else{
        return 0;
    }
}


//链栈——入栈
int push(Stack *s, ElemType e){
    Stack *p = (Stack*)malloc(sizeof(Stack));
    p->data = e;

    p->next = s->next;
    s->next = p;

    return 1;
}


//链栈——出栈
int pop(Stack *s, ElemType *e){
    if(s->next == NULL){
        printf("空栈\n");
        return 0;
    }

    *e = s->next->data;
    Stack *q = s->next;
    s->next = q->next;
    free(q);

    return 1;
}


//链栈——获取栈顶元素
int getTop(Stack *s, ElemType *e){
    if(s->next == NULL){
        printf("空栈\n");
        return 0;
    }

    *e = s->next->data;
    return 1;
}




int main(int argc, char const *argv[]){

    Stack *s = initStack();
    
    push(s, 10);
    push(s, 20);
    push(s, 30);

    ElemType e1, e2;

    pop(s, &e1);
    printf("%d\n", e1);

    getTop(s, &e2);
    printf("%d\n", e2);

    return 0;
}