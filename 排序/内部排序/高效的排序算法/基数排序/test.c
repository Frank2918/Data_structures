#include <stdio.h>
#include <stdlib.h>

/*
基数排序(非比较排序)
1.时间复杂度：O(d*n)，其中d是数字的位数，n是元素个数
2.空间复杂度：O(n+k)，其中k(计数桶)是基数
3.稳定性：稳定排序
4.适用场景：适用于整数,定长字符串， 尤其是大数据量、数据分布均匀、位数不高的排序 
*/


//基数排序函数
void radixSort(int *data, int len){
    int max = data[0];  //假设第一个元素为最大值
    //找出数组中最大值
    for(int i = 1; i < len; i++){
        if(data[i] > max){
            max = data[i];
        }
    }

    //计算最大值的位数
    int digit = 0;
    while(max != 0){
        digit++;
        max /= 10;
    }

    //基数排序的核心思想是按位数进行排序，从低位到高位
    int exp = 1;  //表示当前位的权值（1, 10, 100, ...）
    int *output = (int *)malloc(len * sizeof(int)); //输出数组
    for(int d = 0; d < digit; d++){
        int count[10] = {0}; //计数数组，范围为0-9

        //统计每个数字出现的次数
        for(int i = 0; i < len; i++){
            count[(data[i] / exp) % 10]++;
        }

        //将计数数组转换为位置数组
        for(int i = 1; i < 10; i++){
            count[i] += count[i - 1];
        }

        //根据位置数组将数据放入输出数组
        for(int i = len - 1; i >= 0; i--){
            output[count[(data[i] / exp) % 10] - 1] = data[i];
            count[(data[i] / exp) % 10]--;
        }

        //将输出数组复制回原数组
        for(int i = 0; i < len; i++){
            data[i] = output[i];
        }

        exp *= 10; //移动到下一位
    }

    free(output); //释放输出数组的内存
}



int main(int argc, char const *argv[]){
    //定义待排序数组
    int data[] = {47, 30, 60, 95, 77, 15, 28};
    //计算数组中元素个数
    int len = sizeof(data) / sizeof(data[0]);

    //调用基数排序函数
    radixSort(data, len);

    //输出排序后的数组
    for(int i = 0; i < len; i++){
        printf("%d ",data[i]);
    }
    return 0;
}