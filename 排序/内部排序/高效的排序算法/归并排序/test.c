#include <stdio.h>

/*
归并排序
1.时间复杂度：最坏O(nlogn)，最好O(nlogn)，平均O(nlogn)
2.空间复杂度：O(n)
3.稳定性：稳定排序
4.适用场景：适用于数据量较大的排序
*/

void merge(int *data, int left, int mid, int right){
    int temp[100];     //定义临时数组
    int i = left;       //左半部分起始下标
    int j = mid + 1;    //右半部分起始下标
    int k = 0;              //临时数组下标

    // 将两个有序部分按照大小关系依次放入temp数组
    while(i <= mid && j <= right){
        if(data[i] < data[j]){
            temp[k++] = data[i++];
        }else{
            temp[k++] = data[j++];
        }
    }
    // 将右半部分剩余数据放入temp中（如果有）
    if(i <= mid){
        temp[k++] = data[i++];
    }
    // 将左半部分剩余数据放入temp中（如果有）
    if(j < right){
        temp[k++] = data[j++];
    }
    //将临时数组的数据给data数组，完成合并
    for(int t = 0; t < k; t++){
        data[left+t] = temp[t];
    }
}


// 归并排序的递归函数
void mergeSort(int *data, int left, int right){
    
    if(left < right){    //至少两个元素才能进行排序
        int mid = (left + right) / 2;
        // 对左半部分进行排序
        mergeSort(data, left, mid);

        // 对右半部分进行排序
        mergeSort(data, mid+1, right);

        //将排好序的左右两部分合并
        merge(data, left, mid, right);
    }  
}




int main(int argc, char const *argv[]){
    //定义待排序数组
    int data[] = {47, 30, 60, 95, 77, 15, 28};
    //计算数组中元素个数
    int len = sizeof(data) / sizeof(data[0]);

    //调用归并排序函数
    mergeSort(data, 0, len-1);

    //输出排序后的数组
    for(int i = 0; i < len; i++){
        printf("%d ",data[i]);
    }
    return 0;
}