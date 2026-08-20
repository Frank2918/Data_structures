#include <stdio.h>
/*
插入排序
1.时间复杂度：最坏O(n^2)，最好O(n)，平均O(n^2)
2.空间复杂度：O(1)
3.稳定性：稳定排序
4.适用场景：适用于数据量较小的排序，或者数据基本有序的情况。
*/


/*
折半插入排顺序
1.时间复杂度：最坏O(n^2)，最好O(nlogn)，平均O(n^2)
2.空间复杂度：O(1)
3.稳定性：稳定排序
4.适用场景：数据基本有序
*/

//插入排序
void insertSort(int *data, int len){
    int key;  //暂存待当前插入元素
    //从第二个元素开始插入
    for(int i = 1; i < len; i++){
        key = data[i];
        int j = i - 1;  //从已排序部分的最后一个元素向前比较

        //向前查找插入位置，移动比key大的元素
        while(j >= 0 && data[j] > key){
            data[j+1] = data[j];  //将比key大的元素后移
            j--;                  //继续向前比较
        }
        //找到插入位置将key插入
        data[j+1] = key;
    }
}


//折半插入排序
void binaryInsertSort(int *data, int len){
    int low, mid, high;
    int key;
    //从第二个元素开始遍历，将其插入已排序序列之中
    for(int i = 1; i < len; i++) {
        key = data[i];   //记录当前待插入的值
        low = 0;           //已排序序列的起始下标
        high = i - 1;       //已排序序列终止下标

        //使用折半查找法找到key该插入的位置（low的下标）
        while(low <= high){
            mid = (low + high) / 2;
            if(key > data[mid]){
                low = mid + 1; //插入点在右边
            }else{
                high = mid - 1;  //插入点在左边
            }
        }
        // 从后向前依次将大于key的值前移，为key腾出位置
        int j = i-1;
        while(j >= low){
            data[j+1] = data[j];
            j--;
        }
        //插入key到正确位置
        data[low] = key;
    }
}

int main(int argc, char const *argv[]){
    //定义待排序数组
    int data[] = {47, 30, 60, 95, 77, 15, 28};
    //计算数组中元素个数
    int len = sizeof(data) / sizeof(data[0]);

    /*
    调用插入排序函数
    insertSort(data, len);
    */

    //调用折半插入排序函数
    binaryInsertSort(data, len);

    //输出排序后的数组
    for(int i = 0; i < len; i++){
        printf("%d ",data[i]);
    }
    return 0;
}