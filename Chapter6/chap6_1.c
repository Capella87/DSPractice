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
    struct _node* next;
    int nodeCount;
} Set;

bool setInit(Set*);
bool addElement(Set*, const Data);
bool member(Set*, const Data);
Data subset(Set*, Set*);
bool freeAll(Set*);

int main(void)
{
    int setSize, tempInput;
    Set arr[2];

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
        getchar();
    }
    printf("%d\n", subset(&arr[0], &arr[1]));

    freeAll(&arr[0]);
    freeAll(&arr[1]);
    return 0;
}

bool setInit(Set* target)
{
    target->next = NULL;
    target->nodeCount = 0;

    return true;
}

bool addElement(Set* target, const Data data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    Node* cursor = target->next;
    Node* prevCursor = NULL;
    if (!cursor)
    {
        target->next = newNode;
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

bool member(Set* target, const Data d)
{
    if (!target->nodeCount) return false;
    Node* cursor = target->next;

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

Data subset(Set* a, Set* b)
{
    if (!a->nodeCount) return 0;
    else if (!b->nodeCount) return a->next->data;
    Node* cursor = a->next;

    while (1)
    {
        if (member(b, cursor->data))
        {
            if (!cursor->next) return 0;
            else cursor = cursor->next;
        }
        else return cursor->data;
    }

}

bool freeAll(Set* target)
{
    if (!target->nodeCount) return true;
    Node* pos = target->next, * rpos = NULL;

    while (pos)
    {
        rpos = pos;
        pos = pos->next;
        free(rpos);
    }
    target->nodeCount = 0;

    return true;
}