#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100

typedef struct{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Graph;

typedef struct EdgeNode{
    int edge_vex;
    struct EdgeNode *next;   
}EdgeNode;

typedef struct VertexNode{
    int in;
    VertexType data;
    EdgeNode *head;
}VertexNode;

typedef VertexNode Adj_List[MAXSIZE];

typedef struct{
    Adj_List adj_list;
    int vertex_num;
    int edge_num;
}Adj_Graph;

/* ==================== 顺序栈（用于保存入度为0的顶点） ==================== */
typedef struct{
    int data[MAXSIZE];   /* 栈中存放的是顶点在数组中的下标 */
    int top;             /* 栈顶指针，-1表示空栈 */
}Stack;

/* 初始化栈 */
void init_stack(Stack *s){
    s->top = -1;
}

/* 入栈 */
void push(Stack *s, int x){
    s->data[++s->top] = x;
}

/* 出栈 */
int pop(Stack *s){
    return s->data[s->top--];
}

/* 判断栈是否为空：空返回1，非空返回0 */
int is_empty(Stack *s){
    return s->top == -1;
}

/* ==================== 图的基本操作 ==================== */

/* 根据顶点数据 x 查找其在邻接表中的下标，找不到返回 -1 */
int locate_vex(Adj_Graph *g, VertexType x){
    for(int i = 0; i < g->vertex_num; i++){
        if(g->adj_list[i].data == x)
            return i;
    }
    return -1;
}

/*
 * 创建有向图（邻接表表示，同时统计每个顶点的入度）
 * 边输入格式：弧尾 弧头，表示有一条从弧尾指向弧头的弧
 */
void create_adj_graph(Adj_Graph *g){
    printf("请输入顶点数和边数（用空格隔开）：");
    scanf("%d %d", &g->vertex_num, &g->edge_num);

    /* 1. 初始化各个顶点：读入数据，入度置0，出边链表置空 */
    for(int i = 0; i < g->vertex_num; i++){
        printf("请输入第%d个顶点的数据：", i + 1);
        scanf(" %c", &g->adj_list[i].data);   /* %c前加空格以跳过空白字符 */
        g->adj_list[i].in = 0;                /* 入度初始化为0 */
        g->adj_list[i].head = NULL;           /* 出边链表初始为空 */
    }

    /* 2. 依次读入各条边，用头插法建立邻接表 */
    for(int i = 0; i < g->edge_num; i++){
        VertexType v1, v2;
        printf("请输入第%d条边的两个顶点（弧尾 弧头）：", i + 1);
        scanf(" %c %c", &v1, &v2);

        int j = locate_vex(g, v1);   /* 弧尾顶点下标 */
        int k = locate_vex(g, v2);   /* 弧头顶点下标 */

        /* 头插法：新建边结点，挂到弧尾顶点的出边链表头部 */
        EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->edge_vex = k;                       /* 边指向弧头顶点 k */
        p->next = g->adj_list[j].head;         /* 新结点指向原来的表头 */
        g->adj_list[j].head = p;               /* 链表头指向新结点 */

        /* 弧头顶点的入度 +1 */
        g->adj_list[k].in++;
    }
}

/* ==================== 拓扑排序（Kahn 算法） ==================== */
/* 算法思想： */
/*   1. 将所有入度为 0 的顶点入栈； */
/*   2. 栈不空时循环：出栈一个顶点 i 并输出， */
/*      然后"删除"顶点 i 的所有出边——即把每条出边指向的顶点入度减 1， */
/*      若某顶点入度减为 0，则将其入栈； */
/*   3. 若最终输出的顶点数 < 总顶点数，说明图中存在环，排序失败。 */
/* */
/* 参数： */
/*   g    —— 待排序的有向图（邻接表） */
/*   topo —— 用于存放拓扑序列的数组（按顺序记录顶点下标） */
/* 返回值： */
/*   1 表示排序成功；0 表示图中存在环，无法拓扑排序 */
int topological_sort(Adj_Graph *g, int *topo){
    Stack s;
    init_stack(&s);

    /* 第一步：把所有入度为 0 的顶点入栈 */
    for(int i = 0; i < g->vertex_num; i++){
        if(g->adj_list[i].in == 0)
            push(&s, i);
    }

    int count = 0;   /* 记录已输出的顶点个数 */

    /* 第二步：循环处理栈中的顶点 */
    while(!is_empty(&s)){
        int i = pop(&s);              /* 弹出一个入度为 0 的顶点 */
        topo[count++] = i;            /* 记录到拓扑序列中 */
        printf("输出顶点：%c\n", g->adj_list[i].data);

        /* "删除"顶点 i 的所有出边：相邻顶点入度减 1，变为 0 则入栈 */
        EdgeNode *p = g->adj_list[i].head;
        while(p != NULL){
            int k = p->edge_vex;      /* 出边指向的顶点 */
            g->adj_list[k].in--;      /* 该顶点入度减 1 */
            if(g->adj_list[k].in == 0)
                push(&s, k);          /* 入度变为 0，满足拓扑条件，入栈 */
            p = p->next;              /* 处理下一条出边 */
        }
    }

    /* 第三步：判断是否有环 */
    if(count < g->vertex_num){
        printf("该有向图存在环，无法进行拓扑排序！\n");
        return 0;
    }
    return 1;
}

/* ==================== 测试主函数 ==================== */
int main(void){
    Adj_Graph g;
    int topo[MAXSIZE];   /* 保存拓扑序列（顶点下标） */

    create_adj_graph(&g);

    printf("\n----- 拓扑排序过程 -----\n");
    if(topological_sort(&g, topo)){
        /* 排序成功，输出最终拓扑序列 */
        printf("\n拓扑序列为：");
        for(int i = 0; i < g.vertex_num; i++)
            printf("%c ", g.adj_list[topo[i]].data);
        printf("\n");
    }
    return 0;
}