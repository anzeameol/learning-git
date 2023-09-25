#include <stdio.h>

int main()
{
    foo();
    printf("hello world\n");
    foo();
    return 0;
}

void foo()
{
    printf("foob\n");
}