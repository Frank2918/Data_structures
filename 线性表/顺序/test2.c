#include <stdio.h>
#include <stdlib.h>

/*顺序表
顺序表：用一组连续的存储单元来存储数据元素的线性表，称为顺序表。
顺序表的特点是：支持随机访问，访问效率高；插入和删除操作效率较低，因为需要移动大量元素。
*/


//顺序表——存储结构
#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}SeqList;


//顺序表——初始化
void initList(SeqList *L){
    L->length = 0;
    //解引用指针必须有括号：(*L).length = 0;
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

    SeqList list;  //创建顺序表

    //初始化顺序表
    initList(&list);
    printf("初始化成功，目前顺序表元素个数：%d\n", list.length);
    printf("内存占用：%zu 字节\n", sizeof(list.data));

    //在表尾添加元素
    appendElem(&list, 88);
    appendElem(&list, 91);

    //顺序表遍历
    listElem(&list);

    //插入元素
    insertElem(&list, 2, 100);
    listElem(&list);

    //删除元素
    ElemType delData;
    deleteElem(&list, 1, &delData);
    printf("被删除的数据是：%d\n", delData);
    listElem(&list);

    //查找元素
    printf("查找元素在顺序表位置：%d\n", findElem(&list, 100));
    return 0;
}