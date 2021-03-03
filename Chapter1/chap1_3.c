#include <stdio.h>
#include <stdlib.h>

void swap(int*, int*);

int main(void)
{
    int n, a, b;
    int i;
    int* heapArray = NULL;

    scanf("%d", &n);
    getchar();
    heapArray = (int*)malloc(sizeof(int) * n);
    if (heapArray == NULL) exit(EXIT_FAILURE);
    for (i = 0; i < n; i++)
        scanf("%d", heapArray + i);
    getchar();
    scanf("%d %d", &a, &b);
    swap(heapArray + a, heapArray + b);
    for (i = 0; i < n; i++)
        printf(" %d", *(heapArray + i));
    putchar('\n');


    free(heapArray);
    return 0;
}

void swap(int* t1, int* t2)
{
    int temp;

    temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}