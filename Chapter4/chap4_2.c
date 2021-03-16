#include <stdio.h>
#include <stdlib.h>

void prepareSwap(int*, const int);
void processSwap(int**, int*, const int);
void showResult(const int*, const int);

int main(void)
{
    int n;

    scanf("%d", &n);
    int* x = (int*)malloc(sizeof(int) * n);
    if (x == NULL) exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    prepareSwap(x, n);
    showResult(x, n);

    free(x);
    return 0;
}

void prepareSwap(int* target, const int n)
{
    int length;
    int i;

    scanf("%d", &length);
    int* swapNav = (int*)malloc(sizeof(int*) * length);
    if (swapNav == NULL) exit(EXIT_FAILURE);
    for (i = 0; i < length; i++)
        scanf("%d", swapNav + i);

    int** swapTo = (int*)malloc(sizeof(int*) * (length - 1));
    if (swapTo == NULL) exit(EXIT_FAILURE);
    for (i = 0; i < length - 1; i++)
    {
        swapTo[i] = (int*)malloc(sizeof(int) * 2);
        if (swapTo[i] == NULL) exit(EXIT_FAILURE);
        swapTo[i][0] = target[swapNav[i]];
        swapTo[i][1] = swapNav[i + 1];
    }
    processSwap(swapTo, target, length - 1);


    for (i = 0; i < length - 1; i++)
        free(swapTo[i]);
    free(swapTo);
    free(swapNav);
}

void processSwap(int** list, int* target, const int lNum)
{
    for (int i = 0; i < lNum; i++)
        target[list[i][1]] = list[i][0];
}

void showResult(const int* target, const int n)
{
    for (int i = 0; i < n; i++)
        printf(" %d", target[i]);
    putchar('\n');
}
