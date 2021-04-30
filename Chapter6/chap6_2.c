#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Data;

typedef struct _node
{
    struct _node* next;
    Data data;
} Node;

typedef struct _list
{
    struct _node* head;
    int nodeCount;
} Set;

bool setInit(Set*);
bool addElement(Set*, const Data);
bool member(Set*, const Data);
Set* getUnion(Set*, Set*);
Set* getIntersect(Set*, Set*);
bool printSet(Set*);
bool freeAll(Set*);

int main(void)
{
    int setSize, tempInput;
    Set arr[2];
    Set* uni, *inter;

    for (int i = 0; i < 2; i++)
    {
        setInit(&arr[i]);
        scanf("%d", &setSize);
        getchar();
        for (int j = 0; j < setSize; j++)
        {
            scanf("%d", &tempInput);
            addElement(&arr[i], tempInput);
        }
        if (setSize) getchar();
    }
    uni = getUnion(arr, arr + 1);
    inter = getIntersect(arr, arr + 1);
    if (!printSet(uni)) puts(" 0");
    if (!printSet(inter)) puts(" 0");

    freeAll(&arr[0]);
    freeAll(&arr[1]);
    freeAll(inter);
    freeAll(uni);

    return 0;
}

bool setInit(Set* target)
{
    target->head = (Node*)malloc(sizeof(Node));
    target->head->next = NULL;
    target->nodeCount = 0;

    return true;
}

bool addElement(Set* target, const Data data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    Node* cursor = target->head->next;
    Node* prevCursor = target->head;
    if (!cursor)
    {
        target->head->next = newNode;
        newNode->next = NULL;
        target->nodeCount++;
        return true;
    }
    while (cursor->next)
    {
        // 위치 선정
        if (cursor->data > data) break;
        prevCursor = cursor;
        cursor = cursor->next;
    }
    if (cursor->data < data && !cursor->next)
    {
        // 뒤에 삽입
        cursor->next = newNode;
        newNode->next = NULL;
    }
    else
    {
        // 앞에 삽입
        prevCursor->next = newNode;
        newNode->next = cursor;
    }
    target->nodeCount++;
    return true;
}

bool addElementLast(Set* target, const Data data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    Node* cursor = target->head;
    while (cursor->next)
        cursor = cursor->next;
    cursor->next = newNode;
    newNode->next = NULL;

    target->nodeCount++;
    return true;
}


Set* getUnion(Set* a, Set* b)
{
    Set* newSet = (Set*)malloc(sizeof(Set));
    setInit(newSet);

    Node* pa = a->head->next;
    Node* pb = b->head->next;

    while (pa && pb)
    {
        if (pa->data < pb->data)
        {
            addElementLast(newSet, pa->data);
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            addElementLast(newSet, pb->data);
            pb = pb->next;
        }
        else
        {
            addElementLast(newSet, pb->data);
            pa = pa->next;
            pb = pb->next;
        }
    }
    while (pa)
    {
        addElementLast(newSet, pa->data);
        pa = pa->next;
    }
    while (pb)
    {
        addElementLast(newSet, pb->data);
        pb = pb->next;
    }

    return newSet;
}

Set* getIntersect(Set* a, Set* b)
{
    Set* newSet = (Set*)malloc(sizeof(Set));
    setInit(newSet);

    Node* pa = a->head->next;
    Node* pb = b->head->next;

    while (pa && pb)
    {
        if (pa->data < pb->data)
            pa = pa->next;
        else if (pa->data > pb->data)
            pb = pb->next;
        else
        {
            addElementLast(newSet, pb->data);
            pa = pa->next;
            pb = pb->next;
        }
    }

    return newSet;
}

bool member(Set* target, const Data d)
{
    if (!target->nodeCount) return false;
    Node* cursor = target->head->next;

    while (1)
    {
        if (cursor->data < d)
        {
            if (!cursor->next) return false;
            cursor = cursor->next;
        }
        else if (cursor->data > d)
            return false;
        else return true;
    }


}

bool freeAll(Set* target)
{
    Node* pos = target->head->next;
    Node* rpos = NULL;

    while (pos)
    {
        rpos = pos;
        pos = pos->next;
        free(rpos);
    }
    free(target->head);
    target->nodeCount = 0;

    return true;
}

bool printSet(Set* target)
{
    if (!target->nodeCount) return false;

    Node* cursor = target->head->next;
    while (cursor)
    {
        printf(" %d", cursor->data);
        cursor = cursor->next;
    }
    putchar('\n');

    return true;
}