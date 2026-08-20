#include <stdio.h>

/*
希尔排序
1.时间复杂度：O(n^1+ε)，其中0<ε<1，最坏O(n^2)，最好O(nlogn)，平均O(n^1.3)
2.空间复杂度：O(1)
3.稳定性：不稳定排序
4.适用场景：适用于数据量中等的排序
*/


//希尔排序函数
void shellSort(int *data, int len){
    int temp;
    // 初始化步长为数组长度的一半
    int step = len / 2;
    // 当步长不小于1时继续排序
    while(step >= 1){
        // 对每个分组进行插入排序
        for(int i = step; i < len; i++){
            // 当前元素小于其步长距离元素进行交换
            if(data[i] < data[i-step]){
                temp = data[i];   //存放当前值
                int j = i-step;
                //向前寻找合适插入位置，并逐步移动大于temp的值
                while(j >= 0 && temp < data[j]){
                    data[j+step] = data[j];  //将较大值后移
                    j = j - step;
                }
                // 插入temp到正确位置
                data[j+step] = temp;
            }
        }
        // 缩小步长，通常为减半
        step = step / 2;
    }
}



int main(int argc, char const *argv[]){
    //定义待排序数组
    int data[] = {47, 30, 60, 95, 77, 15, 28};
    //计算数组中元素个数
    int len = sizeof(data) / sizeof(data[0]);

    //调用希尔排序函数
    shellSort(data, len);

    //输出排序后的数组
    for(int i = 0; i < len; i++){
        printf("%d ",data[i]);
    }
    return 0;
}