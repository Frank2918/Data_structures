//! Floyd（弗洛伊德）算法 —— 多源最短路径
//* 一次求出图中"所有顶点对"之间的最短路径
//*
//* ── 与 Dijkstra 的区别 ──────────────────────────────────
//*   Dijkstra：单源最短路径，求"一个顶点"到其余所有顶点，贪心策略，O(n^2)
//*   Floyd   ：多源最短路径，求"所有顶点对"之间的最短路径，动态规划，O(n^3)
//*
//* ── 核心思想（动态规划）────────────────────────────────
//*   设 D[k][i][j] 表示：只允许把编号为 0~k 的顶点作为中转点时，
//*                       顶点 i 到顶点 j 的最短路径长度。
//*   状态转移方程：
//*       D[k][i][j] = min( D[k-1][i][j] , D[k-1][i][k] + D[k-1][k][j] )
//*   含义：i 到 j 的最短路径要么"不经过顶点 k"（保持原样），
//*         要么"经过顶点 k 中转"（拆成 i->k 和 k->j 两段，两段各取最短）。
//*   实现时 k 这一维可以滚动省略，直接在二维数组 D[i][j] 上迭代更新。
//*
//* ── 两个辅助数组 ──────────────────────────────────────
//*   D[i][j]：i 到 j 的最短路径长度
//*   P[i][j]：i 到 j 的最短路径上记录的"中转顶点"
//*            （P[i][j] == -1 表示 i、j 直达即为最短，无需中转）
//*
//* ── 复杂度 ────────────────────────────────────────────
//*   时间复杂度：O(n^3)   空间复杂度：O(n^2)

#include <stdio.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAXEDGE 200
#define MAX 0x10000   // 自定义"无穷大"，表示两个顶点不直接连通

typedef struct{
    VertexType vertex[MAXSIZE];           // 顶点表
    EdgeType arc[MAXSIZE][MAXSIZE];       // 邻接矩阵，arc[i][j] = 边 <i,j> 的权值
    int vertex_num;                       // 顶点个数
    int edge_num;                         // 边的条数
}Mat_Grph;

//! 创建图：与 Dijkstra 使用同一个无向网，便于对照验证
void create_graph(Mat_Grph *G){
    G->vertex_num = 9;   // 9 个顶点：V0 ~ V8
    G->edge_num = 16;    // 16 条边（无向图）

    // 顶点编号
    for (int i = 0; i < G->vertex_num; i++){
        G->vertex[i] = i;
    }

    // 初始化邻接矩阵：对角线为 0（自己到自己），其余为无穷大
    for (int i = 0; i < G->vertex_num; i++){
        for (int j = 0; j < G->vertex_num; j++){
            if(i == j){
                G->arc[i][j] = 0;
            }else{
                G->arc[i][j] = MAX;
            }
        }
    }

    // 输入各条边的权值（只填上三角，下面统一对称）
    G->arc[0][1] = 1;
    G->arc[0][2] = 5;

    G->arc[1][2] = 3;
    G->arc[1][3] = 7;
    G->arc[1][4] = 5;

    G->arc[2][4] = 1;
    G->arc[2][5] = 7;

    G->arc[3][4] = 2;
    G->arc[3][6] = 3;

    G->arc[4][5] = 3;
    G->arc[4][6] = 6;
    G->arc[4][7] = 9;

    G->arc[5][7] = 5;

    G->arc[6][7] = 2;
    G->arc[6][8] = 7;

    G->arc[7][8] = 4;

    // 无向图：矩阵对称，arc[j][i] = arc[i][j]
    for(int i = 0; i < G->vertex_num; i++){
        for(int j = 0; j < G->vertex_num; j++){
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

//! Floyd 算法核心
//* 参数：
//*   G —— 图的邻接矩阵表示（传值即可，算法不修改图）
//*   D —— 输出：D[i][j] 为 i 到 j 的最短路径长度
//*   P —— 输出：P[i][j] 为 i 到 j 最短路径上的一个中转顶点，-1 表示直达
void floyd(Mat_Grph G, EdgeType D[][MAXSIZE], int P[][MAXSIZE]){
    int n = G.vertex_num;

    // 第一步：初始化
    //   D 初始为邻接矩阵（只允许直达边）
    //   P 全部置 -1（默认任意两点直达即为最短）
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            D[i][j] = G.arc[i][j];
            P[i][j] = -1;
        }
    }

    // 第二步：三重循环，动态规划
    //  k —— 中转点：依次允许路径经过顶点 0, 1, ..., k
    //  i —— 起点
    //  j —— 终点
    for (int k = 0; k < n; k++){              // 第 k 轮：允许经过顶点 k
        for (int i = 0; i < n; i++){          // 枚举所有起点
            for (int j = 0; j < n; j++){      // 枚举所有终点
                // 如果 i -> k 再 k -> j 比当前 i -> j 更短，就更新
                if (D[i][k] + D[k][j] < D[i][j]){
                    D[i][j] = D[i][k] + D[k][j];   // 更新最短距离
                    P[i][j] = k;                   // 记录中转顶点 k
                }
            }
        }
    }
}

//! 递归输出 i 到 j 的最短路径（不含起点，起点由调用处打印）
//* 原理：
//*   若 P[i][j] == -1，说明 i 到 j 直达就是最短，直接输出终点 j；
//*   否则最短路径一定经过中转点 k = P[i][j]，把它拆成两段递归处理：
//*       第一段：i -> k；第二段：k -> j
void print_path(int P[][MAXSIZE], int i, int j){
    if (P[i][j] == -1){
        printf(" V%d", j);          // 直达，输出终点
        return;
    }
    int k = P[i][j];                // 取出中转点
    print_path(P, i, k);            // 递归输出 i -> k 这一段
    print_path(P, k, j);            // 递归输出 k -> j 这一段
}

//! 结果输出：
//!  1) 打印所有顶点对之间的最短距离矩阵 D
//!  2) 打印 V0 到其余各顶点的最短路径（与 Dijkstra 的输出对照）
void show_result(int n, EdgeType D[][MAXSIZE], int P[][MAXSIZE]){
    // —— 打印最短距离矩阵 D ——
    printf("所有顶点对之间的最短距离矩阵 D:\n");
    printf("      ");
    for (int j = 0; j < n; j++) printf(" V%-4d", j);
    printf("\n");
    for (int i = 0; i < n; i++){
        printf("V%-4d ", i);
        for (int j = 0; j < n; j++){
            if (D[i][j] >= MAX){
                printf(" INF  ");        // 不可达
            }else{
                printf(" %-5d", D[i][j]);
            }
        }
        printf("\n");
    }

    // —— 打印 V0 到其余各顶点的最短路径 ——
    printf("\n从 V0 出发到各顶点的最短路径:\n");
    for (int j = 1; j < n; j++){
        if (D[0][j] >= MAX){
            printf("V0 -> V%d : 不可达\n", j);
        }else{
            printf("V0 -> V%d : 距离 = %d，路径 = V0", j, D[0][j]);
            print_path(P, 0, j);         // 递归打印中间顶点和终点
            printf("\n");
        }
    }

    // —— 再举一个例子：V3 到 V8 ——
    printf("\nV3 -> V8 : 距离 = %d，路径 = V3", D[3][8]);
    print_path(P, 3, 8);
    printf("\n");
}

int main(){
    Mat_Grph G;
    create_graph(&G);                 // 建图

    EdgeType D[MAXSIZE][MAXSIZE];     // D[i][j]：i 到 j 的最短路径长度
    int P[MAXSIZE][MAXSIZE];          // P[i][j]：i 到 j 最短路径上的中转顶点

    floyd(G, D, P);                   // 调用 Floyd，求出所有顶点对的最短路径

    show_result(G.vertex_num, D, P);  // 输出结果

    return 0;
}
