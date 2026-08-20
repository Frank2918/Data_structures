#include <stdio.h>
#include <string.h>


//字符串匹配——BF算法(时间复杂度O((n-m+1)*m))
int strMatch(char *str, char *pattern){
    int n = strlen(str);
    int m = strlen(pattern);

    for(int i=0; i<=(n-m); i++){
        int j = 0;
        while(j<m){
            if(str[i] == pattern[j]){
                i++;
                j++;
            }
            else{
                i = i - j;
                break;
            }
        }
        if(j == m){
            return i - j;
        }
    }
    return -1;
}



int main(int argc, char const *argv[]){
    char *str = "abcabaabcabc";
    char *pattern = "abaa";
    int pos = strMatch(str, pattern);
    printf("%d\n", pos);
    return 0;
}