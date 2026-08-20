#include <stdio.h>

/*
堆排序：是一种基于完全二叉树的选择排序。(使用顺序存储方式构建二叉树)
1.时间复杂度：最坏O(nlogn)，最好O(nlogn)，平均O(nlogn)
2.空间复杂度：O(1)
3.稳定性：不稳定排序
4.适用场景：适用于数据量较大的排序
*/

/*
基本思路：
1.是将待排序序列构造成一个大顶堆，此时，整个序列的最大值就是堆顶的根节点。
2.将其与末尾元素进行交换，此时末尾就为最大值。
3.然后将剩余的n-1个元素重新构造成一个堆，这样会得到n个元素的次小值。
4.如此反复执行，便能得到一个有序序列。
*/

/*
//? 堆的插入操作
1.保证堆的完全二叉树性质：将新元素插入到堆的末尾
2.逐层调整
*/

/*
//? 堆的删除操作
1.保证堆的完全二叉树性质：用最后一个节点替换要删除元素
2.逐层调整
*/

void swap(int *data, int m, int n){
    int temp = data[m];
    data[m] = data[n];
    data[n] = temp;
}


//向下调整堆（从root开始，len为堆大小）
void adjust(int *data,int root, int len){
    int child;
    int parent = data[root];  //保存当前节点的值
    child = root * 2;   //左孩子下标

    // 存在左孩子
    while(child <= len){
        //如果有右孩子，且比左孩子大，则保存右孩子下标
        if(child < len && data[child] < data[child+1]){
            child++;        //右孩子下标
        }
        // 如果根节点大，无需调整
        if(parent > data[child]){
            break;
        }
        //否则交换值
        data[child/2] = data[child];
        //继续向下调整
        child = child * 2;
    }
    data[child/2] = parent;
}


//堆排序主函数
void heapSort(int *data, int len){
    // 1.建大根堆过程：从最后一个非叶节点开始向前依次做调整
    for(int i = len / 2; i >= 1; i--){
        adjust(data, i, len);
    }
    //2.排序过程：将堆顶最大值与数组最后一个元素交换位置，并调整剩余部分为大根堆
    for(int j = len; j > 1; j--){
        swap(data, 1, j);
        adjust(data, 1, j-1); //剩余部分重新建堆
    }
}



int main(int argc, char const *argv[]){
    //data[0]不使用，占位是为了从data[1]开始建堆
    int data[] = {-1, 47, 30, 60, 95, 77, 15, 28};
    //计算数组中元素个数
    int len = sizeof(data) / sizeof(data[0]);

    //调用堆排序函数
    heapSort(data, len-1);

    //输出排序结果（不含data[0]）
    for(int i = 1; i < len; i++){
        printf("%d ",data[i]);
    }
    return 0;
}