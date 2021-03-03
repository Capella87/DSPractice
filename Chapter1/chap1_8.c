#include <stdio.h>
#include <stdlib.h>

struct student
{
    char name[8];
    int korean;
    int english;
    int math;
    double mean;
};

void typeInfo(struct student*, int);
void printResult(struct student*, int);

int main(void)
{
    int n;
    struct student* list = NULL;

    scanf("%d", &n);
    list = (struct student*)malloc(sizeof(struct student) * n);
    if (list == NULL) exit(EXIT_FAILURE);
    
    typeInfo(list, n);
    printResult(list, n);

    free(list);
    return 0;
}

void typeInfo(struct student* tlist, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        scanf("%s %d %d %d", (tlist + i)->name, &(tlist + i)->korean, &(tlist + i)->english, &(tlist + i)->math);
        getchar();
        (tlist + i)->mean = (double)((tlist + i)->english + (tlist + i)->korean + (tlist + i)->math) / 3;
    }
}

void printResult(struct student* tlist, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        printf("%s %.1lf ", (tlist + i)->name, (tlist + i)->mean);
        if ((tlist + i)->english >= 90 || (tlist + i)->math >= 90 || (tlist + i)->korean >= 90)
            printf("GREAT");
        if ((tlist + i)->english < 70 || (tlist + i)->math < 70 || (tlist + i)->korean < 70)
            puts(" BAD");
        else
            putchar('\n');
    }
}