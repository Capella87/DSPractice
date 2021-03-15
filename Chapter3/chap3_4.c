#include <stdio.h>
#include <stdlib.h>

int getMaxRecurv(int*, int);

int main(void)
{
    int n;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    if (arr == NULL) exit(EXIT_FAILURE);
    getchar();
    for (int i = 0; i < n; i++)
        scanf("%d", arr + i);
    printf("%d\n", getMaxRecurv(arr, n));

    free(arr);
    return 0;
}

int getMaxRecurv(int* target, int idx)
{
    int temp;
    
    if (idx == 1)
        return target[0];
    else if (idx == 2)
        return target[0] > target[1] ? target[0] : target[1];
    else
    {
        temp = getMaxRecurv(target, idx - 1);
        return temp > target[idx - 1] ? temp : target[idx - 1];
    }
}