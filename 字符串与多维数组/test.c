#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char s1[] = "abcde";
    char s2[] = "c";

    printf("%p\n", strstr(s1, s2));
    for (int i = 0; i < 5; i++)
    {
        printf("%p\t", &s1[i]);
    }
}