#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int Data;

typedef struct _node // 그룹 내 요소(element)
{
    struct _node* prev;
    struct _node* next;
    Data element;
} Node;

typedef struct _groupnode // 그룹들
{
    char groupName;
    struct _groupnode* gPrev;
    struct _groupnode* gNext;

    Node* head;
    Node* trailer;
    int nodeCount;
} GroupNode;

typedef struct _group // 그룹의 리스트
{

    GroupNode* ghead;
    int groupCount;
} GroupList;

bool Create_group(GroupList* list, const char g);
bool Show_all(GroupList* list);
bool Add_element(GroupList* list, const char g, const Data e);
bool Destroy_group(GroupList* list, const char g);
bool Remove_element(GroupList* list, const char g, const Data e);

bool gListInit(GroupList* target);
bool freeAll(GroupList* list);
GroupNode* searchGroupList(GroupList* list, const char groupName);
bool alignGroup(GroupList* list, GroupNode* target);
bool alignElement(GroupNode* g, Node* newNode);
Node* searchNode(GroupNode* g, const Data e);

void getCommand(GroupList* list);

// Group maintenance
int main(void)
{
    GroupList alphabet;
    int event_count;

    gListInit(&alphabet);

    scanf("%d", &event_count);
    getchar();
    for (int i = 0; i < event_count; i++)
        getCommand(&alphabet);

    freeAll(&alphabet);
    return 0;
}

bool Create_group(GroupList* list, const char g)
{
    // Search among existing groups (This feature is implemented in a separated function, searchGroupList)
    if (searchGroupList(list, g))
        return false;
    // If the group exists, return NULL and exit this function.

    // Otherwise, Make a new one.
    GroupNode* newGroup = (GroupNode*)malloc(sizeof(GroupNode));
    newGroup->groupName = g;

    newGroup->head = (Node*)malloc(sizeof(Node));
    newGroup->trailer = (Node*)malloc(sizeof(Node));
    newGroup->head->next = newGroup->trailer;
    newGroup->head->prev = NULL;
    newGroup->trailer->next = NULL;
    newGroup->trailer->prev = newGroup->head;

    newGroup->nodeCount = 0;

    if (alignGroup(list, newGroup))
        return true;

    return false;
}

bool Show_all(GroupList* list)
{
    if (!list->groupCount) return false;
    GroupNode* groupCursor = list->ghead->gNext;

    while (groupCursor)
    {
        Node* cursor = groupCursor->head->next;
        printf("%c:", groupCursor->groupName);
        while (cursor != groupCursor->trailer)
        {
            printf(" %d", cursor->element);
            cursor = cursor->next;
        }
        putchar('\n');
        groupCursor = groupCursor->gNext;
    }

    return true;
}

bool Add_element(GroupList* list, const char g, const Data e)
{
    GroupNode* gLocation = searchGroupList(list, g);
    if (!gLocation) return false;
    if (searchNode(gLocation, e) != NULL) return false;

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->element = e;

    if (alignElement(gLocation, newNode))
        return true;

    return false;
}

bool Destroy_group(GroupList* list, const char g)
{
    GroupNode* pos = searchGroupList(list, g);
    if (!pos) return false;
    Node* cursor = pos->head->next;
    Node* rpos;

    while (cursor != pos->trailer) // ?
    {
        rpos = cursor;
        cursor = cursor->next;
        free(rpos);
    }
    free(pos->head);
    free(pos->trailer);
    pos->gPrev->gNext = pos->gNext;
    if (pos->gNext != NULL)
        pos->gNext->gPrev = pos->gPrev;
    list->groupCount--;
    free(pos);

    return true;
}

bool Remove_element(GroupList* list, const char g, const Data e)
{
    GroupNode* pos = searchGroupList(list, g);
    if (!pos) return false;
    Node* cursor = searchNode(pos, e);
    if (!cursor) return false;

    cursor->prev->next = cursor->next;
    cursor->next->prev = cursor->prev;
    free(cursor);
    pos->nodeCount--;

    return true;
}



// Internal functions

bool gListInit(GroupList* target)
{
    target->ghead = (GroupNode*)malloc(sizeof(GroupNode));
    if (!target->ghead) return false;

    target->ghead->gNext = NULL;
    target->ghead->gPrev = NULL;
    target->ghead->groupName = 0;
    target->ghead->head = target->ghead->trailer = NULL;
    target->ghead->nodeCount = 0;

    target->groupCount = 0;

    return true;
}

GroupNode* searchGroupList(GroupList* list, const char groupName)
{
    if (!list->groupCount) return NULL;

    GroupNode* cursor = list->ghead->gNext;
    
    while (cursor != NULL)
    {
        if (cursor->groupName == groupName)
            return cursor;
        cursor = cursor->gNext;
    }

    return NULL;
}

bool alignGroup(GroupList* list, GroupNode* target) // This function should be called from Create_Group function.
{
    GroupNode* cursor = list->ghead->gNext;
    GroupNode* prevCursor = list->ghead;


    while (cursor != NULL)
    {
        if (target->groupName < cursor->groupName)
            break;
        prevCursor = cursor;
        cursor = cursor->gNext;
    }
    if (cursor == NULL)
    {
        prevCursor->gNext = target;
        target->gPrev = prevCursor;
        target->gNext = NULL;
        list->groupCount++;

        return true;
    }

    cursor->gPrev->gNext = target;
    target->gPrev = cursor->gPrev;
    target->gNext = cursor;
    cursor->gPrev = target;
    list->groupCount++;

    return true;
}

bool alignElement(GroupNode* location, Node* newNode)
{
    Node* cursor = location->head->next;

    while (cursor != location->trailer)
    {
        if (newNode->element < cursor->element)
            break;
        cursor = cursor->next;
    }
    
    cursor->prev->next = newNode;
    newNode->prev = cursor->prev;
    newNode->next = cursor;
    cursor->prev = newNode;
    location->nodeCount++;

    return true;
}

Node* searchNode(GroupNode* g, const Data e)
{
    Node* cursor = g->head->next;

    while (cursor != g->trailer)
    {
        if (cursor->element == e)
            return cursor;
        cursor = cursor->next;
    }

    return NULL;
}

void getCommand(GroupList* list)
{
    char input[21];
    char* pos = input;

    scanf("%[^\n]", input);
    getchar();

    switch (input[0])
    {
    case 'A':
        Add_element(list, input[2], atoi(input + 4));
        break;
    case 'C':
        Create_group(list, input[2]);
        break;
    case 'D':
        Destroy_group(list, input[2]);
        break;
    case 'R':
        Remove_element(list, input[2], atoi(input + 4));
        break;
    case 'S':
        Show_all(list);
        break;
    }
}

bool freeAll(GroupList* list)
{
    while (list->ghead->gNext != NULL)
        Destroy_group(list, list->ghead->gNext->groupName);
    free(list->ghead);

    return true;
}