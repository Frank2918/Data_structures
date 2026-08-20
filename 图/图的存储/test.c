//!领接矩阵

#include <stdio.h>
#include <string.h>

#define MAXSIZE 100   //最大顶点数
#define NAME_LEN 20   //顶点名的最大长度
#define MAX 0x7fffffff  //用一个极大值表示无穷（int），即无边

typedef char VertexType[NAME_LEN];  //顶点类型（字符串形式的名字）
typedef int EdgeType;   //边的权值类型（0或1）

//图的领接矩阵结构体定义
typedef struct {
    VertexType vertex[MAXSIZE]; //顶点数组（每个顶点存一个名字字符串）
    EdgeType arc[MAXSIZE][MAXSIZE]; //领接矩阵
    int vertex_num;         //顶点个数
    int edge_num;           //边的个数
}Mat_Grph, Matrix_Graph;


//创建图的领接矩阵
void create_graph(Mat_Grph *G){
    //定义顶点和边数
    G->vertex_num = 4; 
    G->edge_num = 5;   

    //顶点命名
    strcpy(G->vertex[0], "v0");
    strcpy(G->vertex[1], "v1");
    strcpy(G->vertex[2], "v2");
    strcpy(G->vertex[3], "v3");

    //初始化领接矩阵
    for(int i = 0; i < G->vertex_num; i++){
        for(int j = 0; j < G->vertex_num; j++){
            G->arc[i][j] = 0;
        }
    }
    //添加边(无向图、有向图、带权图)
    G->arc[0][1] = 1; G->arc[1][0] = 1;
    G->arc[0][2] = 1; G->arc[2][0] = 1;
    G->arc[0][3] = 1; G->arc[3][0] = 1;
    G->arc[1][2] = 1; G->arc[2][1] = 1;
    G->arc[2][3] = 1; G->arc[3][2] = 1;
    
    //带权图
    //ToDo: G->arc[0][1] = 7; G->arc[1][0] = 5; G->arc[0][3] =  MAX
}


//输出领接矩阵
void print_matrix(Mat_Grph G){
    printf("领接矩阵表示如下：\n");
    for(int i = 0; i < G.vertex_num; i++){
        for(int j = 0; j < G.vertex_num; j++){
            printf("%d ", G.arc[i][j]);
        }
        printf("\n");
    }
}


int main(){
    Mat_Grph G;     //创建一个领接矩阵结构体变量
              
    create_graph(&G);   //初始化领接矩阵
    print_matrix(G);     //输出领接矩阵
    
    printf("MAX = %d\n", MAX);  //输出无穷大值

    return 0;
}