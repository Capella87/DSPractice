#include <stdio.h>

void hanoiTower(int, char, char);

int main(void)
{
    int n;

    scanf("%d", &n);
    hanoiTower(n, 1, 3);

    return 0;
}

void hanoiTower(int num, char from, char to)
{
    if (num == 1)
        printf("%c %c\n", from + 64, to + 64);
    else
    {
        hanoiTower(num - 1, from, 6 - from - to);
        printf("%c %c\n", from + 64, to + 64);
        hanoiTower(num - 1, 6 - from - to, to);
    }
}