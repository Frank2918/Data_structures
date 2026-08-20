//!递归
#include <stdio.h>


//计算前n项和——非递归方式
int fun(int n){
    int sum = 0;
    for(int i = 0; i <= n; i++){
        sum += i;
    }
    return sum;
}


//递归
int fun1(int n){
    if(n == 1){
        return 1;
    }else{
        return fun1(n-1) + n;
    }
}


//斐波那契数列第n项——非递归方式
int fibonacci(int n){
    int j = 1;
    int k = 1;
    int result = 1;

    for(int i = 3; i <= n; i++){
        result = j + k;
        j = k;
        k = result;
    }
    return result;
}


//递归
int fibonacci_1(int n){
    if(n == 1 || n == 2){
        return 1;
    }else{
        return fibonacci_1(n-2) + fibonacci_1(n-1);
    }
}






int main(int argc, char const *argv[]){
    printf("%d\n", fun(5));

    printf("%d\n", fun1(5));

    printf("%d\n", fibonacci(5));

    return 0;
}