#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
    ElemType *data;
    int top;
} Stack;

Stack *initStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
    s->top = -1;
    return s;
}

// 栈的顺序结构——判断栈是否为空
int isEmpty(Stack *s)
{
    if (s->top == -1)
    {
        printf("空栈\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

// 栈的顺序结构——入栈/压栈
int push(Stack *s, ElemType e)
{
    if (s->top >= MAXSIZE - 1)
    {
        printf("栈满\n");
        return 0;
    }

    s->top++;
    s->data[s->top] = e;
    return 1;
}

// 栈的顺序结构——出栈
int pop(Stack *s, ElemType *e)
{
    if (s->top == -1)
    {
        printf("空栈\n");
        return 0;
    }

    *e = s->data[s->top];
    s->top--;

    return 1;
}

// 栈的顺序结构——获取栈顶元素
int getTop(Stack *s, ElemType *e)
{
    if (s->top == -1)
    {
        printf("空栈\n");
        return 0;
    }

    *e = s->data[s->top];

    return 1;
}

//*后缀表达式求值
typedef enum
{
    // todo:左，右括号
    LEFT_PARE,
    RIGHT_PARE,
    // todo:加，减，乘，除，取余
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    // todo:字符串末尾反斜杠0（\0),数字
    EOS,
    NUM,
} contentType;

char expr1[] = "82/2+56*-";

contentType getToken(char *symbol, int *index, const char *expr)
{
    *symbol = expr[*index];
    *index = *index + 1;

    switch (*symbol)
    {
    case '(':
        return LEFT_PARE;
    case ')':
        return RIGHT_PARE;
    case '+':
        return ADD;
    case '-':
        return SUB;
    case '*':
        return MUL;
    case '/':
        return DIV;
    case '%':
        return MOD;
    case '\0':
        return EOS;
    default:
        return NUM;
    }
}

int eval(Stack *s)
{
    char symbol;
    int op1, op2;
    int index = 0;
    contentType token;
    token = getToken(&symbol, &index, expr1);
    ElemType result;
    while (token != EOS)
    {
        if (token == NUM)
        {
            push(s, symbol - '0');
        }
        else
        {
            pop(s, &op2);
            pop(s, &op1);

            switch (token)
            {
            case ADD:
                push(s, op1 + op2);
                break;
            case SUB:
                push(s, op1 - op2);
                break;
            case MUL:
                push(s, op1 * op2);
                break;
            case DIV:
                push(s, op1 / op2);
                break;
            case MOD:
                push(s, op1 % op2);
                break;
            default:
                break;
            }
        }
        token = getToken(&symbol, &index, expr1);
    }

    pop(s, &result);
    printf("%d\n", result);

    return 1;
}

//*中缀表达式——————>后缀表达式
char expr2[] = "x/(i-j)*y";

int print_token(contentType token){
    switch(token){
        case ADD:
            printf("+");
            break;
        case SUB:
            printf("-");
            break;
        case MUL:
            printf("*");
            break;
        case DIV:
            printf("/");
            break;
        case MOD:
            printf("%%");
            break;
        default:
            return 0;
    }
    return 1;
}

void postfix(Stack *s)
{
    int in_stack[] = {0, 19, 12, 12, 13, 13, 13, 0};
    int out_stack[] = {20, 19, 12, 12, 13, 13, 13, 0};
    contentType token;
    int index2 = 0;
    s->top = 0;
    s->data[0] = EOS;
    char _symbol;
    ElemType e;

    token = getToken(&_symbol, &index2, expr2);
    while (token != EOS)
    {
        if (token == NUM)
        {
            printf("%c", _symbol);
        }
        else if (token == RIGHT_PARE)
        {
            while (s->data[s->top] != LEFT_PARE)
            {
                pop(s, &e);
                print_token(e);
            }
            pop(s, &e);
        }
        else
        {
            while (in_stack[s->data[s->top]] >= out_stack[token])
            {
                pop(s, &e);
                print_token(e);
            }
            push(s, token);
        }
        token = getToken(&_symbol, &index2, expr2);
    }
    // 弹出剩余运算符
    pop(s, &e);
    token = e;
    while(token != EOS){
        print_token(token);
        pop(s, &e);
        token = e;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    Stack *s1 = initStack();

    eval(s1);

    Stack *s2 = initStack();
    printf("%s\n", &expr2);
    postfix(s2);
    return 0;
}