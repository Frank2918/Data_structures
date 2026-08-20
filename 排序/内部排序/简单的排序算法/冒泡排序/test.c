#include <stdio.h>
/*
冒泡排序：
1. 时间复杂度：最坏O(n^2)，最好O(n)，平均O(n^2)
2. 空间复杂度：O(1)
3. 稳定性：稳定排序
4. 适用场景：适用于数据量较小的排序，或者数据基本有序的情况。
*/

//交换数组下标为m和n的两元素的值
void swap(int *data, int m, int n){
    int temp = data[m];
    data[m] = data[n];
    data[n] = temp;
}

//冒泡排序
void bubbleSort(int *data, int len){
    //外层循环控制排序趟数len次
    for(int i = 0; i < len; i++){
        //内层循环控制比较次数len-i-1次
        for(int j = 0; j < len-i-1; j++){
            //如果前一个数比后一个数大，进行交换
            if(data[j] > data[j+1]){
                swap(data, j, j+1);  //调用swap进行交换
            }
            
        }
    }
}


int main(int argc, char const *argv[]){
    //定义待排序数组
    int data[] = {47, 30, 60, 95, 77, 15, 28};
    //计算数组中元素个数
    int len = sizeof(data) / sizeof(data[0]);
    //调用冒泡排序函数
    bubbleSort(data, len);
    //输出排序后的数组
    for(int i = 0; i < len; i++){
        printf("%d ",data[i]);
    }
    return 0;
}