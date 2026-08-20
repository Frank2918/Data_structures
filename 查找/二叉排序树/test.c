#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct TreeNode{
    ElemType data;
    struct TreeNode *lchild, *rchild;
}TreeNode, *BiTree;  // *BiTree等价于typedef TreeNode* BiTree;

//用数组模拟二叉树(-1表示空)
int treeArr[] = {70, 55, 49, 30, -1, 39, -1, -1, 53, -1, -1, -1, 80, 75, -1, -1, 98, 95, -1, -1, -1};
int idx = 0;

//递归先序方式构建二叉树
void createTree(BiTree *T){
    ElemType num;
    num = treeArr[idx++];  //取当前索引位置的值
    if(num == -1){
        *T = NULL;
    }else{
        // 创建新节点并递归构建左右子树
        (*T) = (BiTree)malloc(sizeof(TreeNode));
        (*T)->data = num;
        createTree(&(*T)->lchild);
        createTree(&(*T)->rchild);
    }
}

//二叉树遍历——先序遍历
void preOrder(BiTree T){
    if(T == NULL){
        return;
    }
    printf("%d ", T->data);
    preOrder(T->lchild);
    preOrder(T->rchild);
}


// 二叉排序树——查找
//?二叉排序树查找的时间复杂度为O(h)，其中h为树的高度。
//?最坏情况下，h可能接近n（退化为链表）O(n)，平均情况下，h约为log2(n)。
int search_bst(BiTree T, int value, BiTree parent, BiTree *target){
    if(T == NULL){
        *target = parent; //递归到空节点，查找失败，将父节点返回（可用于插入）
        return 0;
    }
    if(T->data == value){
        *target = T;  //找到目标
        return 1;
    }
    if(value < T->data){
        //要查找的值比根节点小，向左子树查找
        return search_bst(T->lchild, value, T, target);
    }else{
        //要查找的值比根节点大，向右子树查找
        return search_bst(T->rchild, value, T, target);
    }
}



// 二叉排序树——插入
//如果值存在，插入失败，返回0；否则成功，返回1；
int insert_bst(BiTree *T, int value){
    BiTree parent = NULL, pos = NULL;  //parent用于辅助search_bst,pos表示插入位置或已存在位置
    BiTree curr;

    // 查找插入位置
    int status = search_bst(*T, value, parent, &pos);
    if(status == 0){
        // 如果未找到，创建新节点
        curr = (BiTree)malloc(sizeof(TreeNode));
        curr->data = value;
        curr->lchild = NULL;
        curr->rchild = NULL;
        //如果树为空，新节点作为空间点
        if(pos == NULL){
            *T = curr;
        }
        else if(value < pos->data){
            pos->lchild = curr;     //插入为左子结点
        }else{
            pos->rchild = curr;     //插入为右子结点
        }
        return 1;
    }else{
        return 0;  //如果已存在，不插入
    }  
}


// 二叉排序树——删除
/*
1. 删除叶子节点：
直接将其父节点的指针置为NULL，并释放该节点的内存。、

2. 删除只有一个子树的节点：
让它的父节点指向它的子树，并释放该节点的内存。

3. 删除有两个子树的节点：
找到其右子树中的最小节点（中序后继），用该节点的值替换要删除的节点的值，然后删除该最小节点。
或者找到其左子树中的最大节点（中序前驱），用该节点的值替换要删除的节点的值，然后删除该最大节点。
*/

// 递归查找并删除目标节点
int delete_bst(BiTree *T, int value){
    if(*T == NULL){
        return 0; //未找到目标节点
    }
    if(value < (*T)->data){
        return delete_bst(&(*T)->lchild, value);
    }else if(value > (*T)->data){
        return delete_bst(&(*T)->rchild, value);
    }else{
        // 找到目标节点
        BiTree temp = *T;
        if((*T)->lchild == NULL && (*T)->rchild == NULL){
            // 情况1：删除叶子节点
            free(temp);
            *T = NULL;
        }else if((*T)->lchild == NULL){
            // 情况2：只有右子树
            *T = (*T)->rchild;
            free(temp);
        }else if((*T)->rchild == NULL){
            // 情况2：只有左子树
            *T = (*T)->lchild;
            free(temp);
        }else{
            // 情况3：有两个子树，找到右子树的最小节点
            BiTree minNode = (*T)->rchild;
            while(minNode->lchild != NULL){
                minNode = minNode->lchild;
            }
            (*T)->data = minNode->data; // 替换值
            delete_bst(&(*T)->rchild, minNode->data); // 删除最小节点
        }
        return 1; //删除成功
    }
}



int main(){
    //构建二叉树排序树
    BiTree T = NULL, bst = NULL;
    createTree(&T);

    BiTree target;
    search_bst(T, 53, NULL, &target); //查找值为53的节点

    preOrder(T);
    printf("\n");
    printf("%d\n", target->data);  //输出查找到节点的值


    // 准备插入的初始序列
    int treeArr1[] = {7, 3, 78, 10, 38, 10, 53, 46, 77};
    //批量插入（构建二叉排序树）
    for(int i = 0; i < sizeof(treeArr1) / sizeof(treeArr1[0]); i++){
        insert_bst(&bst, treeArr1[i]);
    }
    //查看当前树结构
    preOrder(bst);
    printf("\n");

    //插入一个新值100
    insert_bst(&bst, 100);
    
    preOrder(bst);
    printf("\n");

    //删除一个值10
    delete_bst(&bst, 10);

    preOrder(bst);
    printf("\n");

    return 0;
}