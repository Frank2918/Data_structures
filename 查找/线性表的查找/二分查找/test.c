#include <stdio.h>

//!:折半查找（二分查找）的前提：查找表必须是有序的
//?折半查找时间复杂度：O(log2n)

//折半查找函数
int binary_search(int *data, int len, int value){
    int low = 0;  //起始下标
    int high = len -1;  //结束下标
    int mid;

    while(low <= high){
        mid = (low + high) / 2;  //计算中间下标
        if(value > data[mid]){
            low = mid + 1;      //在右半部分继续查找
        }else if(value < data[mid]){
            high = mid - 1;   //在左半部分继续查找
        }else{
            return mid;      //关键字等于中间元素，查找成功，返回下标
        } 
    }
    return -1;
}


int main(){
    int arr[] = {6, 15, 29, 42, 76, 91}; //查找表（必须有序）
    int len = sizeof(arr) / sizeof(arr[0]); //数组长度
    int pos = binary_search(arr, len, 6);
    printf("%d\n", pos);
    return 0;
}