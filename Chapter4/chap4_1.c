#include <stdio.h>
#include <stdlib.h>

int swapRange(int*, const int, const int, const int);
void printArray(const int*, const int);

int main(void)
{
    int n, revRequest, revFrom, revTo;
    int i;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    if (arr == NULL) exit(EXIT_FAILURE);

    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    getchar();
    scanf("%d", &revRequest);
    for (i = 0; i < revRequest; i++)
    {
        scanf("%d %d", &revFrom, &revTo);
        swapRange(arr, n, revFrom, revTo);
    }
    printArray(arr, n);

    free(arr);
    return 0;
}

int swapRange(int* arr, const int n, const int from, const int to)
{
    int count = to - from + 1;
    int temp;

    for (int i = 0; i < count / 2; i++)
    {
        temp = arr[from + i];
        arr[from + i] = arr[to - i];
        arr[to - i] = temp;
    }

    return 0;
}

void printArray(const int* arr, const int n)
{
    for (int i = 0; i < n; i++)
        printf(" %d", arr[i]);
    putchar('\n');
}