#include <stdio.h>

//顺序查找函数
int search(int *data, int len, int value){
    for(int i = 0; i < len; i++){
        if(data[i] == value){
            return i;  //返回找到元素的下标
        }
    }
    return -1;   //没查到返回-1
}


int main(){
    int arr[] = {15, 29, 6, 42, 76, 91}; //查找表
    int len = sizeof(arr) / sizeof(arr[0]); //数组长度
    int pos = search(arr, len, 6);
    printf("%d\n", pos);
    return 0;
}