#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char Data;

typedef struct Node
{
    Data elem;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct List
{
    Node* head;
    Node* tail;

    int dataCount;
} List;

void init_list(List*);
bool traverse(List*, Data*);
Data get(List*, int);
void getCommand(List*);
bool add(List*, int, Data);
bool freeNode(List*);
bool delete(List*, int);
bool print(List*);

int main(void)
{
    List list;
    init_list(&list);
    int n;

    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
        getCommand(&list);

    freeNode(&list);
    return 0;
}

void init_list(List* list)
{
    Node* dummyHead = (Node*)malloc(sizeof(Node));
    if (dummyHead == NULL) exit(EXIT_FAILURE);
    list->head = dummyHead;
    Node* dummyTail = (Node*)malloc(sizeof(Node));
    if (dummyTail == NULL) exit(EXIT_FAILURE);
    list->tail = dummyTail;
    list->head->next = list->tail;
    list->head->prev = NULL;
    list->tail->next = NULL;
    list->tail->prev = list->head;

    list->dataCount = 0;
}

bool add(List* list, int rank, Data data)
{
    if (rank < 1 || rank > list->dataCount + 1)
    {
        puts("invalid position");
        return false;
    }
    Node* pos = list->head;

    for (int i = 0; i < rank; i++)
        pos = pos->next;

    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) exit(EXIT_FAILURE);
    node->elem = data;
    node->next = pos;
    node->prev = pos->prev;
    pos->prev->next = node;
    pos->prev = node;

    list->dataCount++;

    return true;
}

Data get(List* list, int rank)
{
    if (rank < 1 || rank > list->dataCount)
    {
        puts("invalid position");
        return '\0';
    }
    Node* pos = list->head;

    for (int i = 0; i < rank; i++)
        pos = pos->next;

    return pos->elem;
}

void getCommand(List* list)
{
    char command;
    int rank;
    char input;
    Data result;

    scanf("%c", &command);
    switch (command)
    {
    case 'A':
        scanf("%d %c", &rank, &input);
        add(list, rank, input);
        break;
    case 'D':
        scanf("%d", &rank);
        delete(list, rank);
        break;
    case 'G':
        scanf("%d", &rank);
        result = get(list, rank);
        if (result != '\0')
            putchar(result);
        break;
    case 'P':
        print(list);
        break;
    default:
        break;
    }
    getchar();

}

bool delete(List* list, int rank)
{
    if (rank < 1 || rank > list->dataCount)
    {
        puts("invalid position");
        return false;
    }

    Node* pos = list->head;

    for (int i = 0; i < rank; i++)
        pos = pos->next;
    Node* rpos = pos;
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    pos = pos->prev;

    free(rpos);
    list->dataCount--;
    return true;
}

bool print(List* list)
{
    if (list->dataCount == 0)
        return false;
    Node* pos = list->head->next;

    for (int i = 0; i < list->dataCount; i++)
    {
        printf("%c", pos->elem);
        pos = pos->next;
    }
    putchar('\n');

    return true;
}

bool freeNode(List* list)
{
    Node* pos = list->head;
    Node* rpos = pos;

    if (list->dataCount == 0) free(list->head);
    for (int i = 0; i < list->dataCount; i++)
    {
        pos = rpos->next;
        free(rpos);
        rpos = pos;
    }
    free(list->tail);

    return true;
}