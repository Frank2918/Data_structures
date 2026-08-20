#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;   /* 顶点（事件）的数据类型 */
typedef int EdgeType;      /* 边的权值（活动持续时间）类型 */

#define MAXSIZE 100

/* ==================== 边结点（弧） ==================== */
/* AOE 网中，边代表"活动"，边上的权值代表活动的持续时间 */
typedef struct EdgeNode{
    int edge_vex;             /* 弧头顶点（活动指向的事件）下标 */
    EdgeType weight;          /* 弧的权值 = 该活动的持续时间 */
    struct EdgeNode *next;    /* 指向下一条出边 */
}EdgeNode;

/* ==================== 顶点结点（事件） ==================== */
typedef struct VertexNode{
    int in;                   /* 入度（用于拓扑排序） */
    VertexType data;          /* 顶点数据 */
    EdgeNode *head;           /* 出边链表头指针 */
}VertexNode;

typedef VertexNode Adj_List[MAXSIZE];

/* ==================== 邻接表表示的有向图（AOE 网） ==================== */
typedef struct{
    Adj_List adj_list;
    int vertex_num;           /* 顶点（事件）数 */
    int edge_num;             /* 边（活动）数 */
}Adj_Graph;

/* ==================== 顺序栈（用于拓扑排序保存入度为0的顶点） ==================== */
typedef struct{
    int data[MAXSIZE];        /* 栈中存放的是顶点在数组中的下标 */
    int top;                  /* 栈顶指针，-1表示空栈 */
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
 * 创建 AOE 网（邻接表表示，带权有向图）
 * 顶点代表"事件"，边代表"活动"，边的权值代表活动的持续时间
 * 边输入格式：弧尾 弧头 权值（弧尾事件 -> 弧头事件，权值为活动耗时）
 */
void create_adj_graph(Adj_Graph *g){
    printf("请输入顶点数（事件数）和边数（活动数，用空格隔开）：");
    scanf("%d %d", &g->vertex_num, &g->edge_num);

    /* 1. 初始化各个顶点：读入数据，入度置0，出边链表置空 */
    for(int i = 0; i < g->vertex_num; i++){
        printf("请输入第%d个顶点（事件）的数据：", i + 1);
        scanf(" %c", &g->adj_list[i].data);   /* %c前加空格以跳过空白字符 */
        g->adj_list[i].in = 0;                /* 入度初始化为0 */
        g->adj_list[i].head = NULL;           /* 出边链表初始为空 */
    }

    /* 2. 依次读入各条边（活动），用头插法建立邻接表 */
    for(int i = 0; i < g->edge_num; i++){
        VertexType v1, v2;
        EdgeType w;
        printf("请输入第%d条边（活动）的 弧尾 弧头 权值：", i + 1);
        scanf(" %c %c %d", &v1, &v2, &w);

        int j = locate_vex(g, v1);   /* 弧尾顶点（活动起点事件）下标 */
        int k = locate_vex(g, v2);   /* 弧头顶点（活动终点事件）下标 */

        /* 头插法：新建边结点，记录权值，挂到弧尾顶点的出边链表头部 */
        EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));
        p->edge_vex = k;                       /* 边指向弧头顶点 k */
        p->weight = w;                         /* 记录活动持续时间 */
        p->next = g->adj_list[j].head;         /* 新结点指向原来的表头 */
        g->adj_list[j].head = p;               /* 链表头指向新结点 */

        /* 弧头顶点的入度 +1 */
        g->adj_list[k].in++;
    }
}

/*
 * 拓扑排序（Kahn 算法）
 * 作用：为求关键路径服务——
 *   1. 正序（拓扑序）求各事件最早发生时间 ve[]；
 *   2. 保存拓扑序列，方便后续逆序求各事件最迟发生时间 vl[]。
 *
 * 参数：
 *   g     —— AOE 网（邻接表）
 *   topo  —— 用于存放拓扑序列的数组（按顺序记录顶点下标）
 *   ve    —— 存放各事件的最早发生时间（在排序过程中同步求出）
 * 返回值：
 *   1 表示排序成功；0 表示图中存在环（AOE 网不允许有环），无法求关键路径
 */
int topological_sort(Adj_Graph *g, int *topo, int *ve){
    Stack s;
    init_stack(&s);

    /* 第一步：把所有入度为 0 的顶点入栈 */
    for(int i = 0; i < g->vertex_num; i++){
        if(g->adj_list[i].in == 0)
            push(&s, i);
    }

    /* 初始化各事件最早发生时间 ve 为 0 */
    for(int i = 0; i < g->vertex_num; i++)
        ve[i] = 0;

    int count = 0;   /* 记录已输出的顶点个数 */

    /* 第二步：循环处理栈中的顶点 */
    while(!is_empty(&s)){
        int i = pop(&s);              /* 弹出一个入度为 0 的顶点 */
        topo[count++] = i;            /* 记录到拓扑序列中 */

        /* "删除"顶点 i 的所有出边：相邻顶点入度减 1，变为 0 则入栈 */
        EdgeNode *p = g->adj_list[i].head;
        while(p != NULL){
            int k = p->edge_vex;      /* 出边指向的顶点 */

            /* 【关键】利用拓扑序递推事件最早发生时间：
             * 事件 k 最早发生时间 = max(所有前驱事件 j 的最早时间 + 活动<j,k>的权值)
             * 这里只需比较"经过当前顶点 i 这条路径"的时间是否更大即可，
             * 因为对每个前驱都会执行一次本操作，最终 ve[k] 自然取到最大值 */
            if(ve[i] + p->weight > ve[k])
                ve[k] = ve[i] + p->weight;

            g->adj_list[k].in--;      /* 该顶点入度减 1 */
            if(g->adj_list[k].in == 0)
                push(&s, k);          /* 入度变为 0，满足拓扑条件，入栈 */
            p = p->next;              /* 处理下一条出边 */
        }
    }

    /* 第三步：判断是否有环 */
    if(count < g->vertex_num){
        printf("该有向图存在环，无法进行拓扑排序，也不存在关键路径！\n");
        return 0;
    }
    return 1;
}

/*
 * 求关键路径（核心算法）
 *
 * 相关概念回顾：
 *   AOE 网：顶点 = 事件，边 = 活动，边权 = 活动持续时间。
 *   关键路径：从源点（入度为0）到汇点（出度为0）的最长路径，
 *             它决定了整个工程的最短完成时间；路径上的活动称为关键活动。
 *
 * 四个重要量：
 *   ve[i]：事件 i 的最早发生时间（正序，取各前驱路径的最大值）
 *   vl[i]：事件 i 的最迟发生时间（逆序，取各后继路径的最小值）
 *   ee ：活动的最早开始时间 = ve[弧尾]（活动不开始，后面事件无法发生）
 *   el ：活动的最迟开始时间 = vl[弧头] - 权值（再晚就影响后续事件按时发生）
 *
 * 判定：若某活动 ee == el（时间余量 el - ee == 0），则该活动是关键活动，
 *       所有关键活动组成的路径即为关键路径。
 *
 * 参数：
 *   g    —— AOE 网（邻接表）
 *   topo —— 拓扑排序得到的序列（顶点下标）
 *   ve   —— 各事件最早发生时间（由拓扑排序阶段求出）
 */
void critical_path(Adj_Graph *g, int *topo, int *ve){
    int vl[MAXSIZE];   /* vl[i]：事件 i 的最迟发生时间 */

    /* ========== 第一步：求各事件的最迟发生时间 vl（按逆拓扑序） ========== */
    /* 汇点的最迟发生时间 = 汇点的最早发生时间（整个工程最短工期） */
    for(int i = 0; i < g->vertex_num; i++)
        vl[i] = ve[g->vertex_num - 1];

    /* 从汇点往前倒推：按拓扑序列的逆序处理每个事件 i */
    for(int i = g->vertex_num - 1; i >= 0; i--){
        int j = topo[i];   /* 当前事件 j */

        /* 事件 j 的最迟发生时间 = min(所有后继事件 k 的最迟时间 - 活动<j,k>的权值) */
        EdgeNode *p = g->adj_list[j].head;
        while(p != NULL){
            int k = p->edge_vex;
            if(vl[k] - p->weight < vl[j])
                vl[j] = vl[k] - p->weight;   /* 取最小值，保证任何后继都不被耽误 */
            p = p->next;
        }
    }

    /* ========== 第二步：遍历所有活动，判断哪些是关键活动 ========== */
    printf("\n===== 各活动的最早/最迟开始时间及关键活动判定 =====\n");
    printf("%-4s %-6s %-6s %-6s %-4s\n", "活动", "耗时", "最早ee", "最迟el", "关键?");

    /* 遍历每个顶点的出边链表，逐条活动进行判断 */
    for(int i = 0; i < g->vertex_num; i++){
        EdgeNode *p = g->adj_list[i].head;
        while(p != NULL){
            int k = p->edge_vex;               /* 弧头事件 */
            int ee = ve[i];                    /* 活动最早开始时间 = 弧尾事件最早发生时间 */
            int el = vl[k] - p->weight;        /* 活动最迟开始时间 = 弧头事件最迟时间 - 耗时 */

            /* 时间余量 = el - ee；余量为 0 的活动即关键活动 */
            if(ee == el){
                printf("%c->%c  %-6d %-6d %-6d   ★关键活动\n",
                       g->adj_list[i].data, g->adj_list[k].data, p->weight, ee, el);
            }else{
                printf("%c->%c  %-6d %-6d %-6d\n",
                       g->adj_list[i].data, g->adj_list[k].data, p->weight, ee, el);
            }
            p = p->next;
        }
    }

    /* ========== 第三步：输出结果汇总 ========== */
    printf("\n整个工程的最短完成时间（关键路径长度）为：%d\n", ve[g->vertex_num - 1]);

    printf("\n各事件时间信息：\n");
    printf("%-6s %-10s %-10s\n", "事件", "最早ve", "最迟vl");
    for(int i = 0; i < g->vertex_num; i++){
        printf("%-6c %-10d %-10d\n", g->adj_list[i].data, ve[i], vl[i]);
    }
}

/* ==================== 测试主函数 ==================== */
int main(void){
    Adj_Graph g;
    int topo[MAXSIZE];   /* 保存拓扑序列（顶点下标） */
    int ve[MAXSIZE];     /* 保存各事件的最早发生时间 */

    create_adj_graph(&g);

    printf("\n----- 拓扑排序（并求各事件最早发生时间） -----\n");
    if(topological_sort(&g, topo, ve)){
        /* 排序成功，输出拓扑序列 */
        printf("\n拓扑序列为：");
        for(int i = 0; i < g.vertex_num; i++)
            printf("%c ", g.adj_list[topo[i]].data);
        printf("\n");

        /* 基于拓扑序列求关键路径 */
        printf("\n----- 关键路径 -----\n");
        critical_path(&g, topo, ve);
    }
    return 0;
}
