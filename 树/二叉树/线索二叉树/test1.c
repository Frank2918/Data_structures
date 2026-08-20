#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;

//线索二叉树——存储结构
typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode *lchild; 
    struct ThreadNode *rchild;
    int ltag;                   /*ltag为0表示指向左孩子，为1表示指向前驱线索*/
    int rtag;                   /*rtag为0表示指向右孩子，为1表示指向后继线索*/
}ThreadNode;

typedef ThreadNode* ThreadTree;


//线索二叉树——中序遍历线索化

//?1.头节点的lchild指向根节点，ltag为0
//?2.头节点的rchild指向中序遍历的最后一个节点，rtag为1
//?3.第一个节点的lchild指向头节点，ltag为1
//?4.最后一个节点的rchild指向头节点，rtag为1

char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;
ThreadTree prev;


//建立原始二叉树（根据字符串）
void createTree(ThreadTree *T){
    ElemType ch = str[idx++];
    if(ch == '#'){
        *T = NULL;
    }else{
        (*T) = (ThreadTree)malloc(sizeof(ThreadNode));
        (*T)->data = ch;
        createTree(&(*T)->lchild);  //构建左子树
        //!三目运算符：表达式1 ？ 表达式2 ：表达式3
        (*T)->ltag = (*T)->lchild ? 0 : 1;   //有左子树——>ltag = 0
        createTree(&(*T)->rchild);  //构建右子树
        (*T)->rtag = (*T)->rchild ? 0 : 1;   //有右子树——>rtag = 0
    }
}

//中序线索化函数：建立前驱/后继关系
void threading(ThreadTree T){
    if(T != NULL){
        threading(T->lchild);  //递归线索化左子树
        //如果当前节点的左指针为空，建立前驱线索
        if(T->ltag == 1){
            T->lchild = prev;
        }
        //如果前一个结点的右指针是空，建立其后继线索指向当前节点
        if(prev && prev->rtag == 1){
            prev->rchild = T;
        }
        prev = T;  //更新prev为当前节点
        threading(T->rchild);  //递归线索化右子树
    }
}












//创建头节点，调用线索化过程构建线索二叉树
void inOrderThreading(ThreadTree *T, ThreadTree *head){
    *head = (ThreadTree)malloc(sizeof(ThreadNode));
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = *head; //初始时指向自己

    if(*T == NULL){
        (*head)->lchild = *head;  //空树情况
    }else{
        (*head)->lchild = *T;     //头节点左指向根节点
        prev = *head;     //初始化前驱节点
        threading(*T);   //中序线索化整棵树
    }

    //补全最后一个节点的后继线索
    prev->rchild = (*head);
    (*head)->rchild = prev;

}


//中序遍历线索化后的二叉树（非递归）
void inOrder(ThreadTree T){
    ThreadTree curr = T->lchild; //从头节点的左子树开始
    while(curr != T){
        //沿着左孩子一直到底
        while(curr->ltag == 0){
            curr = curr->lchild;
        }
        //访问当前节点
        printf("%c ", curr->data);
        //顺着线索一直向右访问所以后继
        while(curr->rtag == 1 && curr->rchild != T){
            curr = curr->rchild;
            printf("%c ", curr->data); 
        }
        //进入当前节点的右子树
        curr = curr->rchild;
    }
}

















int main(int argc, char const *argv[]){
    ThreadTree T, head;
    createTree(&T);
    inOrderThreading(&T, &head); //执行线索化
    printf("中序遍历结果：");
    inOrder(head);   //遍历线索二叉树
    return 0;
}