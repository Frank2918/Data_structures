//!邻接表
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100   //最大顶点数
#define NAME_LEN 20   //顶点名的最大长度

typedef char VertexType[NAME_LEN];  //顶点类型（字符串形式的名字）

//1.边结点（弧结点）：描述一条边
typedef struct EdgeNode {
    int adjvex;             //邻接点域：这条边指向的顶点在数组中的下标
    int weight;             //权值域：边的权值（不带权图可以去掉）
    struct EdgeNode *next;  //链域：指向下一条边结点
} EdgeNode;

//2.顶点结点：一个顶点 = 顶点数据 + 一条边链表
typedef struct VertexNode {
    VertexType data;        //顶点信息（名字）
    EdgeNode *firstedge;    //边表头指针：指向该顶点的第一条边
} VertexNode, AdjList[MAXSIZE];

//3.图的邻接表结构体定义
typedef struct {
    AdjList vertices;       /*顶点数组（数组下标就是顶点编号）*/
    int vertex_num;         //顶点个数
    int edge_num;           //边的个数
} ALGraph;


//头插法：在顶点 i 的边表头部插入一条指向 j 的边
void add_edge(ALGraph *G, int i, int j){
    EdgeNode *p = (EdgeNode*)malloc(sizeof(EdgeNode));
    p->adjvex = j;
    p->weight = 1;          //默认权值为 1
    p->next = G->vertices[i].firstedge;
    G->vertices[i].firstedge = p;
}


//创建图的邻接表（无向图）
void create_graph(ALGraph *G){
    G->vertex_num = 4;
    G->edge_num = 5;

    //顶点命名
    strcpy(G->vertices[0].data, "v0");
    strcpy(G->vertices[1].data, "v1");
    strcpy(G->vertices[2].data, "v2");
    strcpy(G->vertices[3].data, "v3");

    //初始化边表头指针为 NULL
    for(int i = 0; i < G->vertex_num; i++){
        G->vertices[i].firstedge = NULL;
    }

    //添加边（无向图：一条边要在两个顶点各存一次）
    add_edge(G, 0, 1); add_edge(G, 1, 0);
    add_edge(G, 0, 2); add_edge(G, 2, 0);
    add_edge(G, 0, 3); add_edge(G, 3, 0);
    add_edge(G, 1, 2); add_edge(G, 2, 1);
    add_edge(G, 2, 3); add_edge(G, 3, 2);
}


//输出邻接表
void print_graph(ALGraph G){
    printf("邻接表表示如下：\n");
    for(int i = 0; i < G.vertex_num; i++){
        printf("%s -> ", G.vertices[i].data);
        EdgeNode *p = G.vertices[i].firstedge;
        while(p){
            printf("%s(%d) ", G.vertices[p->adjvex].data, p->adjvex);
            p = p->next;
        }
        printf("^NULL\n");
    }
}


int main(){
    ALGraph G;          //创建一个邻接表结构体变量
    create_graph(&G);   //初始化邻接表
    print_graph(G);     //输出邻接表

    return 0;
}

