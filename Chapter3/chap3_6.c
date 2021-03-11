#include <stdio.h>

int gcd(int, int);

int main(void)
{
    int a, b;

    scanf("%d %d", &a, &b);
    printf("%d\n", gcd(a, b));

    return 0;
}

int gcd(int a, int b)
{
    if (b > 0) return gcd(b, a % b);
    else return a;
}