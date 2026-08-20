#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

//顺序表——动态分配内存地址初始化
typedef struct{
    ElemType *data;
    int length;
}SeqList;


SeqList* initList(){
    SeqList *L = (SeqList*)malloc(sizeof(SeqList));
    L->data = (ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    L->length = 0;
    return L;
}


//顺序表——在尾部添加元素
int appendElem(SeqList *L, ElemType e){
    if (L->length >= MAXSIZE){
        printf("顺序表已满\n");
        return 0;
    }
    L->data[L->length] = e;
    L->length++;
    return 1;
}


//顺序表——遍历
void listElem(SeqList*L){
    for (int i=0; i < L->length; i++){
        printf("%d ", L->data[i]);
    }
    printf("\n");
}


//顺序表——插入元素
int insertElem(SeqList*L, int pos, ElemType e){
    if (L->length >= MAXSIZE)
    {
        printf("顺序表已满\n");
        return 0;
    }

    if (pos < 1 || pos > L->length){
        printf("插入位置错误\n");
        return 0;
    }


    if (pos <= L->length){
        for (int i=L->length-1; i>=pos-1; i--){
            L->data[i+1] = L->data[i];
        }
        L->data[pos-1] = e;
        L->length++;
    }
    return 1;
}


//顺序表——删除元素
int deleteElem(SeqList*L, int pos, ElemType *e){
    if (L->length > MAXSIZE){
        printf("顺序表为空\n");
        return 0;
    }

    if (pos < 1 || pos > L->length){
        printf("插入位置错误\n");
        return 0;
    }

    *e = L->data[pos-1];
    if (pos < L->length ){
        for (int i = pos; i < L->length; i++){
            L->data[i-1]=L->data[i];
        }
        L->length--;
    }
    return 1;
}


//顺序表——按值查找
int findElem(SeqList*L, ElemType e){
    if (L->length == 0){
        printf("顺序表为空表\n");
        return 0;
    }

    for(int i = 0; i < L->length; i++){
        if (L->data[i] = e){
            return i+1;
        }
    }
    return 0;
}



int main(int argc, char const *argv[]){
    //动态分配内存初始化(无需声明顺序表，调用函数直接一个返回顺序表)
    SeqList *L = initList();
    printf("初始化成功，目前顺序表元素个数：%d\n", (*L).length);
    printf("内存占用：%zu 字节\n", sizeof(L->data));
    
    appendElem(L, 88);
    appendElem(L, 91);

    //顺序表遍历
    listElem(L);

    //插入元素
    insertElem(L, 2, 100);
    listElem(L);

    //删除元素
    ElemType delData;
    deleteElem(L, 1, &delData);
    printf("被删除的数据是：%d\n", delData);
    listElem(L);

    //查找元素
    printf("查找元素在顺序表位置：%d\n", findElem(L, 100));

    return 0;
}