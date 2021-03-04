#include <stdio.h>

void splitNum(int);

int main(void)
{
    int n;
    scanf("%d", &n);
    splitNum(n);

    return 0;
}

void splitNum(int num)
{
    if (num != 0)
    {
        splitNum(num / 10);
        printf("%d\n", num % 10);
    }
}