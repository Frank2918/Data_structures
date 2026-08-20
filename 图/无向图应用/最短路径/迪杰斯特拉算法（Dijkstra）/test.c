//! Dijkstra算法
//* 单源最短路径:从某一个顶点出发，求到其他所有顶点的最短路径

#include <stdio.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAXEDGE 200
#define MAX 0x10000

typedef struct{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Grph;

void create_graph(Mat_Grph *G){

    G->vertex_num = 9;
    G->edge_num = 16;

    for (int i = 0; i < G->vertex_num; i++){
        G->vertex[i] = i;
    }

    for (int i = 0; i < G->vertex_num; i++){
        for (int j = 0; j < G->vertex_num; j++){
            if(i == j){
                G->arc[i][j] = 0;
            }else{
                G->arc[i][j] = MAX;
            }
        }
    }

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

    for(int i = 0; i < G->vertex_num; i++){
        for(int j = 0; j < G->vertex_num; j++){
            G->arc[j][i] = G->arc[i][j];
        }
    }
}


int choose(int distance[], int found[], int vertex_num){
    int min = MAX;
    int minPos = -1;

    for(int i = 0; i < vertex_num; i++){
        if(distance[i] < min && found[i] == 0){
            min = distance[i];
            minPos = i;
        }
    }
    return minPos;
}


void dijkstra(Mat_Grph G, int begin){
    int found[MAXSIZE];
    int path[MAXSIZE];
    int distance[MAXSIZE];

    for (int i = 0; i < G.vertex_num; i++){
        found[i] = 0;
        path[i] = -1;
        distance[i] = G.arc[begin][i];
    }
    found[begin] = 1;
    distance[begin] = 0;

    int next;

    // 源点 begin 已确定，只需再确定 n-1 个顶点
    for(int i = 1; i < G.vertex_num; i++){
        next = choose(distance, found, G.vertex_num);
        if(next == -1){   // 剩余顶点均不可达
            break;
        }
        found[next] = 1;
        for(int j = 0; j < G.vertex_num; j++){
            if(found[j] == 0){
                if(distance[next] + G.arc[next][j] < distance[j]){
                    distance[j] = distance[next] + G.arc[next][j];
                    path[j] = next;
                }
            }
        }
    }
    for(int i = 0; i < G.vertex_num; i++){
        printf("V0 -> V%d : %d\n", i, distance[i]);

        // path[j] 存 j 的前驱，用栈把路径逆序成正序输出
        int stack[MAXSIZE], top = 0;
        int j = i;
        while(j != begin && j != -1){
            stack[top++] = j;
            j = path[j];
        }
        printf("路径: V0");
        while(top > 0){
            printf(" -> V%d", stack[--top]);
        }
        printf("\n");
    }
}


int main(){
    Mat_Grph G;
    create_graph(&G);
    int begin = 0;   // 源点：V0
    dijkstra(G, begin);
    return 0;
}