#include <stdio.h>
#include <stdlib.h>

void typeToList(int*, int);
void printList(int*, int*, int);

int main(void)
{
    int n;
    int* alist = NULL;
    int* blist = NULL;

    scanf("%d", &n);
    getchar();
    alist = (int*)malloc(sizeof(int) * n);
    if (alist == NULL) exit(EXIT_FAILURE);
    blist = (int*)malloc(sizeof(int) * n);
    if (blist == NULL) exit(EXIT_FAILURE);
    typeToList(alist, n);
    typeToList(blist, n);
    printList(alist, blist, n);

    free(alist);
    free(blist);
    return 0;
}

void typeToList(int* target, int count)
{
    int* pos = target;

    for (; pos < target + count; pos++)
        scanf("%d", pos);
    getchar();
}

void printList(int* t1, int* t2, int count)
{
    int i;
    for (i = 0; i < count; i++)
        printf(" %d", t1[i] + t2[count - 1 - i]);
    putchar('\n');
}