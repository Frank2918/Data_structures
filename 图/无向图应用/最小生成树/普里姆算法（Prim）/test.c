//! Prim算法 —— 最小生成树（加点法）
// 思想：从某个顶点出发，每次选一个"离已选集合 U 最近"的未选顶点加入，
//       直到所有顶点都被选入，共选出 n-1 条边。
// 适用：稠密图。时间复杂度 O(n²)。

#include <stdio.h>
#include <limits.h>

#define MAX_VERTEX 20   // 最大顶点数
#define INF INT_MAX     // 表示"无穷大"，即两顶点之间没有边

typedef struct {
    int vertex[MAX_VERTEX];              // 顶点表（这里直接用下标当顶点编号）
    int arc[MAX_VERTEX][MAX_VERTEX];     // 邻接矩阵，arc[i][j] 存边 (i,j) 的权值
    int vertexNum, arcNum;               // 顶点数、边数
} MGraph;

// closedge：记录每个未选顶点到"已选集合 U"的最小边
typedef struct {
    int adjvex;   // 最小边在 U 中的那个端点（记录边的来源）
    int lowcost;  // 最小边的权值；0 表示该顶点已经在 U 中
} CloseEdge;

// 在 closedge 中找出 lowcost 最小（且不为 0，即还未入选）的顶点下标
int MinEdge(CloseEdge closedge[], int n) {
    int min = INF, k = -1;
    for (int i = 0; i < n; i++) {
        if (closedge[i].lowcost != 0 && closedge[i].lowcost < min) {
            min = closedge[i].lowcost;
            k = i;
        }
    }
    return k;
}

// Prim 算法：从 start 顶点出发构造最小生成树
void MiniSpanTree_Prim(MGraph G, int start) {
    CloseEdge closedge[MAX_VERTEX];
    int totalWeight = 0;

    // 初始化：start 加入集合 U，其余顶点记录到 U 的最小边
    for (int i = 0; i < G.vertexNum; i++) {
        if (i != start) {
            closedge[i].adjvex  = start;
            closedge[i].lowcost = G.arc[start][i];
        }
    }
    closedge[start].lowcost = 0;   // start 已在 U 中

    printf("最小生成树的边（Prim，从顶点 %d 开始）：\n", start);
    // 还需选出 n-1 条边
    for (int count = 1; count < G.vertexNum; count++) {
        int k = MinEdge(closedge, G.vertexNum);   // 选"离 U 最近"的未选顶点 k
        int u = closedge[k].adjvex;               // 对应最小边在 U 中的端点

        printf("边 (V%d, V%d)   权值 = %d\n", u, k, closedge[k].lowcost);
        totalWeight += closedge[k].lowcost;

        closedge[k].lowcost = 0;                  // 把顶点 k 加入集合 U

        // 用新顶点 k 刷新其余未选顶点到 U 的最小边
        for (int i = 0; i < G.vertexNum; i++) {
            if (G.arc[k][i] < closedge[i].lowcost) {
                closedge[i].adjvex  = k;
                closedge[i].lowcost = G.arc[k][i];
            }
        }
    }
    printf("最小生成树总权值 = %d\n", totalWeight);
}

// 建立示例图（教材经典例题：6 个顶点 9 条边）
void CreateMGraph(MGraph *G) {
    G->vertexNum = 6;
    G->arcNum    = 9;

    for (int i = 0; i < G->vertexNum; i++)
        G->vertex[i] = i;

    // 邻接矩阵初始化为 INF（对角线为 0）
    for (int i = 0; i < G->vertexNum; i++)
        for (int j = 0; j < G->vertexNum; j++)
            G->arc[i][j] = (i == j) ? 0 : INF;

    // 边的数据：{顶点u, 顶点v, 权值}
    int edges[][3] = {
        {0, 1, 34}, {0, 2, 46}, {0, 5, 19},
        {1, 4, 12}, {1, 5, 25},
        {2, 3, 17}, {2, 5, 25},
        {3, 4, 38}, {3, 5, 25}
    };
    for (int i = 0; i < G->arcNum; i++) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        G->arc[u][v] = w;
        G->arc[v][u] = w;   // 无向图，矩阵对称
    }
}

int main(void) {
    MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Prim(G, 0);   // 从顶点 0 开始构造最小生成树
    return 0;
}



