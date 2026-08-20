#include <stdio.h>


/*
快速排序（非常高效的排序算法，采用分治思想）
1.时间复杂度：最坏O(n^2),最好O(nlog2n),平均O(nlog2n)
2.空间复杂度：O(log2n)
3.稳定性：不稳定
4.适用场景：适用于大数据量的排序，尤其是随机分布的数据。
*/

/*
基本思路
1. 选择一个基准元素（pivot）
2. 将数组分为两部分，一部分小于基准元素，另一部分大于基准元素
3. 递归地对两部分进行快速排序
4. 直至子序列的长度为1或0，排序完成
*/

/*

一个简单的快速排序实现
void quickSort(int *data, int left, int right){
    if(left < right){ //至少两个元素才能进行排序
        int pivot = data[left]; //选择基准元素
        int i = left; //左指针
        int j = right; //右指针

        while(i < j){
            //从右向左找第一个小于基准元素的元素
            while(i < j && data[j] >= pivot){
                j--;
            }
            if(i < j){
                data[i++] = data[j]; //将小于基准元素的元素放到左边
            }

            //从左向右找第一个大于基准元素的元素
            while(i < j && data[i] <= pivot){
                i++;
            }
            if(i < j){
                data[j--] = data[i]; //将大于基准元素的元素放到右边
            }
        }
        data[i] = pivot; //将基准元素放到正确的位置

        //递归地对左右两部分进行快速排序
        quickSort(data, left, i - 1);
        quickSort(data, i + 1, right);
    }
}

*/

//partition用于将数组划分为左右两个部分，返回基准值的最终位置
int partition(int *data, int low, int high){
    // 选择第一个元素作为基准
    int pivot = data[low];
    // 当low与high没相遇时继续循环
    while(low < high){
        //从右向左寻找第一个小于基准的值
        while(low < high && data[high] >= pivot){
            high--;
        }
        //将小于基准的值放到左边
        data[low] = data[high];

        // 从左向右寻找第一个大于基准的值
        while(low < high && data[low] <= pivot){
            low++;
        }
        //将大于基准的值放到右边
        data[high] = data[low];
    }
    //当low = high时找到pivot该放的位置
    data[low] = pivot;
    return low;     //返回pivot当前值
}


//快速排序主函数
void quickSort(int *data, int low, int high){
    int pivot;
    if(low < high){
        //对当前区间进行划分，并获取pivot的位置
        pivot = partition(data, low, high);
        //对pivot左侧子数组递归进行快速排序
        quickSort(data, low, pivot-1);
        //对pivot右侧子数组递归进行快速排序
        quickSort(data, pivot+1, high);
    }
}



int main(int argc, char const *argv[]){
    //定义待排序数组
    int data[] = {47, 30, 60, 95, 77, 15, 28};
    //计算数组中元素个数
    int len = sizeof(data) / sizeof(data[0]);

    //调用快速排序函数
    quickSort(data, 0, len-1);

    //输出排序后的数组
    for(int i = 0; i < len; i++){
        printf("%d ",data[i]);
    }
    return 0;
}