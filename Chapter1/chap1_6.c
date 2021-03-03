#include <stdio.h>
#include <stdlib.h>
#define PEOPLE 5

typedef struct _student
{
    char name[10];
    int score;
} Info;

void printDeclined(Info[], double*);

int main(void)
{
    Info list[PEOPLE];
    int i;
    double total = 0.0;

    for (i = 0; i < PEOPLE; i++)
    {
        scanf("%s %d", list[i].name, &list[i].score);
        getchar();
        total += (double)list[i].score;
    }
    printDeclined(list, &total);

    return 0;
}

void printDeclined(Info target[], double* total)
{
    int i;
    *total /= PEOPLE;
    for (i = 0; i < PEOPLE; i++)
        if ((double)target[i].score <= *total)
            puts(target[i].name);
}