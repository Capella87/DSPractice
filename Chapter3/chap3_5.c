#include <stdio.h>

void hanoiTower(int, char, char, char);

int main(void)
{
    int n;

    scanf("%d", &n);
    hanoiTower(n, 'A', 'B', 'C');

    return 0;
}

void hanoiTower(int num, char from, char via, char to)
{
    if (num == 1)
        printf("%c %c\n", from, to);
    else
    {
        hanoiTower(num - 1, from, to, via);
        printf("%c %c\n", from, to);
        hanoiTower(num - 1, to, from, via);
    }
}