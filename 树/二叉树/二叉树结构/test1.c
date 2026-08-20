//?二叉树的存储结构——顺序存储（除满二叉树和完全二叉树外其他场景比较浪费空间）
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct {
    char data[MAXSIZE]; // 存储二叉树结点的数组
    int n;              // 结点个数
} SeqTree;


//二叉树的存储结构——链式结构
typedef char ElemType;

typedef struct TreeNode{
    ElemType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TreeNode;

typedef TreeNode* BiTree;


//二叉树遍历——先序遍历
void preOrder(BiTree T){
    if(T == NULL){
        return;
    }
    printf("%c ", T->data);
    preOrder(T->lchild);
    preOrder(T->rchild);
}


//二叉树遍历——中序遍历
void inOrder(BiTree T){
    if(T == NULL){
        return;
    }
    inOrder(T->lchild);
    printf("%c ", T->data);
    inOrder(T->rchild);
}


//二叉树遍历——后序遍历
void postOrder(BiTree T){
    if(T == NULL){
        return;
    }
    postOrder(T->lchild);
    postOrder(T->rchild);
    printf("%c ", T->data);
}



char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

//构建树（二级指针）
void createTree(BiTree *T){
    ElemType ch;
    ch = str[idx++];
    if(ch == '#'){
        (*T) = NULL;
    }else{
        (*T) = (BiTree)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        createTree(&(*T)->lchild);
        createTree(&(*T)->rchild);
    }
}










int main(int argc, char const *argv[]){
    BiTree T;
    createTree(&T);

    preOrder(T);
    printf("\n");

    inOrder(T);
    printf("\n");

    postOrder(T);
    printf("\n");
}