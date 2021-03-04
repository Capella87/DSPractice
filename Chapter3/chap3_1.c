#include <stdio.h>

int addTo(int);

int main(void)
{
    int n;

    scanf("%d", &n);
    printf("%d\n", addTo(n));

    return 0;
}

int addTo(int num)
{
    static int total = 0;

    total += num;
    if (num == 1)
        return total;
    else
        return addTo(num - 1);
}