#include <stdio.h>

/*
简单选择排序
1.时间复杂度：最坏O(n^2)，最好O(n^2)，平均O(n^2)
2.空间复杂度：O(1)
3.稳定性：不稳定排序
4.适用场景：适用于数据量较小的排序
*/

void swap(int *data, int m, int n){
    int temp = data[m];
    data[m] = data[n];
    data[n] = temp;
}

//简单选择排序函数
void selectSort(int *data, int len){
    int min;
    // 外层循环，控制每轮的起始位置
    for(int i = 0; i < len; i++){
        //将当前位置i视为最小值
        min = i;  
        // 内层循环，从i开始向后寻找最小值的下标值
        for(int j = i; j < len; j++){
            //如果发现比当前最小值还小的元素，更新最小值的位置
            if(data[min] > data[j]){
                min = j;
            }
        }
        // 如果找到的最小值不是当前位置，则进行交换
        if(i != min){
            swap(data, min, i);
        }     
    }
}



int main(int argc, char const *argv[]){
    //定义待排序数组
    int data[] = {47, 30, 60, 95, 77, 15, 28};
    //计算数组中元素个数
    int len = sizeof(data) / sizeof(data[0]);

    //调用简单选择排序函数
    selectSort(data, len);
    //输出排序后的数组
    for(int i = 0; i < len; i++){
        printf("%d ",data[i]);
    }
    return 0;
}