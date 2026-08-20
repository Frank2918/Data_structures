#include <string.h>
#include <stdio.h>
//示例：图书管理系统
struct book
{
    int isbn;
    char bookName[20];
    double price;
};

int main(int argc, char const*argv[]){
    struct book b;
    b.isbn = 911;
    strcpy(b.bookName, "数据结构与算法");
    b.price = 58;
}