//!二级指针作用：在函数中传入指针的地址来修改指针所指向内存空间的值
#include <stdio.h>
#include <stdlib.h>

//? void fun(int *temp){
//     temp指针指向在堆内存开辟的空间
//?     temp = (int *)malloc(sizeof(int));
//?     *temp = 100;
//? }

//? int main(){
//?     int *p = NULL;
//     /*  传入p的地址，相当于复制p的地址给temp，temp指向NULL，temp指针指向在堆内存开辟的空间
//        temp指针指向的空间存储100，temp指针释放，p指针仍然指向NULL    */
//?     fun(p);
//?     printf("%d\n", *p);  //p->NULL，解引用p输出p指向的值时报错
//?     return 0;
//? }

void fun(int **temp){
    //p指针指向在堆内存开辟的空间
    *temp = (int *)malloc(sizeof(int));
    **temp = 100;
}

int main(){
    int *p = NULL;
    /*  传入p的地址，相当于复制p的地址给temp，temp(p)指向NULL，temp(p)指针指向在堆内存开辟的空间
        temp(p)指针指向的空间存储100，temp指针释放，p指针仍然指向在堆内存开辟的空间    */
    fun(&p);
    printf("%d\n", *p);  
    return 0;
}