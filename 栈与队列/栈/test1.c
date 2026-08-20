//?栈: 一种特殊的线性表，只允许在表尾进行插入和删除操作，遵循后进先出（LIFO）的原则。
//?栈的基本操作包括：入栈（push）、出栈（pop）和获取栈顶元素（top）。
//?表尾被称为栈顶，表头被称为栈底。

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int ElemType;

//栈的顺序存储结构
typedef struct{
    ElemType data[MAXSIZE];
    int top;
}Stack;


//栈的顺序结构——初始化
void initStack(Stack *s){
    s->top = -1;
}


//栈的顺序结构——判断栈是否为空
int isEmpty(Stack *s){
    if(s->top == -1){
        printf("空栈\n");
        return 1;
    }else{
        return 0;
    }
}


//栈的顺序结构——入栈/压栈
int push(Stack *s, ElemType e){
    if(s->top >= MAXSIZE-1){
        printf("栈满\n");
        return 0;
    }
    
    s->top++;
    s->data[s->top] = e;
    return 1;
}


//栈的顺序结构——出栈
int pop(Stack *s, ElemType *e){
    if(s->top == -1){
        printf("空栈\n");
        return 0;
    }

    *e = s->data[s->top];
    s->top--;

    return 1;
}


//栈的顺序结构——获取栈顶元素
int getTop(Stack *s, ElemType *e){
    if(s->top == -1){
        printf("空栈\n");
        return 0;
    }

    *e = s->data[s->top];

    return 1;
}




int main(int argc, char const *argv[]){
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    ElemType e1, e2;

    pop(&s, &e1);
    printf("%d\n", e1);

    getTop(&s, &e2);
    printf("%d\n", e2);

    return 0;
}