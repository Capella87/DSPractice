#include <stdio.h>

int sum(int);

int main(void)
{
    int input;
    int total = 0;

    scanf("%d", &input);
    for (int i = 1; i <= input; i++)
        total += sum(i);
    printf("%d\n", total);

    return 0;
}

int sum(int input)
{
    static int result = 0;

    result += input;
    return result;
}