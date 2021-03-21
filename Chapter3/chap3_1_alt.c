#include <stdio.h>

int addToNonStatic(int);

int main(void)
{
    int num;

    scanf("%d", &num);
    printf("%d\n", addToNonStatic(num));

    return 0;
}

int addToNonStatic(int num)
{
    if (num <= 1)
        return num;
    else
        return num + addToNonStatic(num - 1);
}