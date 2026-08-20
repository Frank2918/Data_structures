//?枚举

#include <stdio.h>

typedef enum {
    mon = 1, tue, wed, thu, fri, sta, sun
}weekday;



/*  enum bool{
        false = 0, ture = 1
    };               
    enum bool a;
    a = false;       */
                    



int main(int argc, char const *argv[]){
    weekday a;
    a = mon;
    weekday b;
    b = tue;

    printf("%d\n", a);
    printf("%d\n", b);

    return 0;
}