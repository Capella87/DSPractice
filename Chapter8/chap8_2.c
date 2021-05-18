#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int Data;

typedef struct _node
{
    struct _node* prev;
    struct _node* next;
    Data d;

} Node;

typedef struct _deck
{
    Node* front;
    Node* rear;
    int count;
} Deck;

void getCommand(const int);
bool initDeck(Deck*);
bool add_front(Deck*, const Data);
bool add_rear(Deck*, const Data);
Data delete_front(Deck*);
Data delete_rear(Deck*);
Data peek_front(const Deck*);
Data peek_rear(const Deck*);
bool print(const Deck*);
bool deleteAll(Deck*);
bool isEmpty(const Deck*);
size_t count(const Deck*);

int main(void)
{
    int n;

    scanf("%d", &n);
    getCommand(n);

    return 0;
}

void getCommand(const int n)
{
    Deck a;
    char cmd[3];
    int num;

    initDeck(&a);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", cmd);
        
        if (!strcmp(cmd, "AF"))
        {
            scanf("%d", &num);
            add_front(&a, num);
        }
        else if (!strcmp(cmd, "AR"))
        {
            scanf("%d", &num);
            add_rear(&a, num);
        }
        else if (!strcmp(cmd, "P"))
            print(&a);
        else if (!strcmp(cmd, "DF"))
            delete_front(&a);
        else if (!strcmp(cmd, "DR"))
            delete_rear(&a);
        getchar();
    }

    deleteAll(&a);

    return;
}


bool initDeck(Deck* deck)
{
    deck->front = deck->rear = NULL;
    deck->count = 0;

    return true;
}
bool add_front(Deck* deck, const Data d)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->d = d;

    if (isEmpty(deck))
        deck->front = deck->rear = newNode;
    else
    {
        deck->front->prev = newNode;
        newNode->next = deck->front;
        newNode->prev = NULL;
        deck->front = newNode;
    }
    deck->count++;

    return true;
}

bool add_rear(Deck* deck, const Data d)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->d = d;

    if (isEmpty(deck))
        deck->front = deck->rear = newNode;
    else // need to fix
    {
        deck->rear->next = newNode;
        newNode->prev = deck->rear;
        newNode->next = NULL;
        deck->rear = newNode;
    }
    deck->count++;

    return true;
}

Data delete_front(Deck* deck)
{
    if (isEmpty(deck))
    {
        puts("underflow");
        deleteAll(deck);
        exit(EXIT_FAILURE);
    }

    Node* pos = deck->front;
    if (count(deck) - 1 == 0)
        deck->front = deck->rear = NULL;
    else
    {
        deck->front->next->prev = NULL;
        deck->front = deck->front->next;
    }

    free(pos);
    deck->count--;
    return true;
}

Data delete_rear(Deck* deck)
{
    if (isEmpty(deck))
    {
        puts("underflow");
        deleteAll(deck);
        exit(EXIT_FAILURE);
    }

    Node* pos = deck->rear;
    if (count(deck) - 1 == 0)
        deck->front = deck->rear = NULL;
    else
    {
        deck->rear->prev->next = NULL;
        deck->rear = deck->rear->prev;
    }

    free(pos);
    deck->count--;
    return true;
}

Data peek_front(const Deck* deck)
{
    if (isEmpty(deck)) return -1;

    return deck->front->d;
}

Data peek_rear(const Deck* deck)
{
    if (isEmpty(deck)) return -1;

    return deck->rear->d;
}

bool print(const Deck* deck)
{
    if (isEmpty(deck)) return false;

    Node* pos = deck->front;
    while (pos)
    {
        printf(" %d", pos->d);
        pos = pos->next;
    }
    putchar('\n');

    return true;
}

bool deleteAll(Deck* deck)
{
    while (!isEmpty(deck))
        delete_front(deck);

    return true;
}

bool isEmpty(const Deck* deck)
{
    return !deck->count ? true : false;
}

size_t count(const Deck* deck)
{
    return deck->count;
}