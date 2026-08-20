#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int ElemType;


//栈的顺序结构初始化——动态内存分配
typedef struct{
    ElemType *data;
    int top;
}Stack;

Stack* initStack(){

    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = (ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    s->top = -1;

    return s;
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