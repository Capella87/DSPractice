#include <stdio.h>

void splitNumRev(int);

int main(void)
{
    int n;
    scanf("%d", &n);
    splitNumRev(n);

    return 0;
}

void splitNumRev(int num)
{
    if (num != 0)
    {
        printf("%d\n", num % 10);
        splitNumRev(num / 10);
    }
}