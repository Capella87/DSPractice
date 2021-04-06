#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _polynomial
{
    int coef;
    int exp;
    struct _polynomial* next;
} Monomial;

typedef struct _list
{
    Monomial* head;
    int DataCount;
} List;

Monomial* Init(List* target);
void appendTerm(List* target, Monomial** k, int c, int e);
List* addPoly(List* x, List* y);
void freeNode(List* target);
bool showEquation(List* target);

int main(void)
{
    int polyCount;
    int c, e;
    int i, j; // For Loop
    List polyArr[2];
    Monomial* arr[2] = { Init(&polyArr[0]), Init(&polyArr[1]) };
    List* result = NULL;

    for (i = 0; i < 2; i++)
    {
        scanf("%d", &polyCount);
        getchar();
        for (j = 0; j < polyCount; j++)
        {
            scanf("%d %d", &c, &e);
            appendTerm(&polyArr[i], &arr[i], c, e);
        }
        getchar();
    }
    for (i = 0; i < 2; i++)
        arr[i] = polyArr->head;
    
    result = addPoly(&polyArr[0], &polyArr[1]);
    showEquation(result);

    freeNode(&polyArr[0]);
    freeNode(&polyArr[1]);
    freeNode(result);
    free(result);
    return 0;
}

Monomial* Init(List* target)
{
    target->head = (Monomial*)malloc(sizeof(Monomial));
    if (target->head == NULL)
        exit(EXIT_FAILURE);

    target->head->next = NULL;
    target->DataCount = 0;
    Monomial* last = target->head;

    return last;
}

void appendTerm(List* target, Monomial** k, int c, int e)
{
    Monomial* append = (Monomial*)malloc(sizeof(Monomial));
    if (!append) exit(EXIT_FAILURE);

    append->coef = c;
    append->exp = e;
    append->next = NULL;
    (*k)->next = append; // Caution! (*k) ==> _polynomial* type
    *k = append;

    target->DataCount++;

}

List* addPoly(List* x, List* y)
{
    List* result = (List*)malloc(sizeof(List));
    if (!result) exit(EXIT_FAILURE);
    Monomial* k = Init(result);
    Monomial* i = x->head->next;
    Monomial* j = y->head->next;
    int sum;

    while ((i != NULL) & (j != NULL))
    {
        sum = 0;
        if (i->exp > j->exp)
        {
            appendTerm(result, &k, i->coef, i->exp);
            i = i->next;
        }
        else if (i->exp < j->exp)
        {
            appendTerm(result, &k, j->coef, j->exp);
            j = j->next;
        }
        else
        {
            sum = i->coef + j->coef;
            if (sum)
                appendTerm(result, &k, sum, i->exp);
            i = i->next;
            j = j->next;
        }
    }
    while (i)
    {
        appendTerm(result, &k, i->coef, i->exp);
        i = i->next;
    }
    while (j)
    {
        appendTerm(result, &k, j->coef, j->exp);
        j = j->next;
    }


    return result;
}

bool showEquation(List* target)
{
    Monomial* pos = target->head;

    if (!target->DataCount) return false;

    for (int i = 0; i < target->DataCount; i++)
    {
        pos = pos->next;
        printf(" %d %d", pos->coef, pos->exp);
    }
    putchar('\n');

    return true;
}

void freeNode(List* target)
{
    Monomial* pos = target->head;
    Monomial* rpos = pos;

    if (!target->DataCount) free(target->head);
    for (int i = 0; i < target->DataCount; i++)
    {
        pos = rpos->next;
        free(rpos);
        rpos = pos;
    }
}