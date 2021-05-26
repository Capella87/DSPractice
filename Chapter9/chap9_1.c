 #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int Data;
typedef struct _node
{
    char name[3];
    Data data;
    struct _node* left;
    struct _node* right;
} Node;

typedef struct _binarytree
{
    Node* root;
    Node* tempLeft;
    Node* tempRight;
    Node* tempParent;
    int n;
} Tree;

bool initTree(Tree* tr)
{
    tr->root = tr->tempLeft = tr->tempParent = tr->tempRight =  NULL;
    tr->n = 0;

    return true;
}

bool isInternal(const Node* node)
{
    return node->left != NULL || node->right != NULL ? true : false;
}

bool isExternal(const Node* node)
{
    return node->left == NULL && node->right == NULL ? true : false;
}

bool swapNode(Node* n1, Node* n2)
{
    Node temp;
    strcpy(temp.name, n1->name);
    temp.data = n1->data;

    strcpy(n1->name, n2->name);
    n1->data = n2->data;
    strcpy(n2->name, temp.name);
    n2->data = temp.data;
    return true;
}

bool addNode(Tree* tr, const Data d, Node* left, Node* right, const char* name)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = d;
    newNode->left = left;
    newNode->right = right;
    strcpy(newNode->name, name);
    if (!tr->root || isInternal(newNode))
        tr->root = newNode;

    if (isInternal(newNode))
    {
        tr->tempParent = newNode;
    }
    else // isExternal
    {
        int num = atoi(newNode->name + 1);
        if (num % 2 == 0) tr->tempRight = newNode;
        else tr->tempLeft = newNode;
    }

    tr->n++;

    return true;
}

bool FindNode(Tree* tr, const int num)
{
    if (num > 8 || num < 1)
    {
        printf("-1\n");
        return false;
    }

    Node* pos = tr->root;
    switch (num)
    {
    case 1:
        break;
    case 2:
        pos = pos->left;
        break;
    case 3:
        pos = pos->right;
        break;
    case 4:
        pos = pos->left;
        pos = pos->left;
        break;
    case 5:
        pos = pos->left;
        pos = pos->right;
        break;
    case 6:
        pos = pos->right;
        pos = pos->right;
        break;
    case 7:
        pos = pos->right;
        pos = pos->right;
        pos = pos->left;
        break;
    case 8:
        pos = pos->right;
        pos = pos->right;
        pos = pos->right;
        break;
    }

    printf("%d ", pos->data);
    if (pos->left) printf("%d ", pos->left->data);
    if (pos->right) printf("%d ", pos->right->data);
    putchar('\n');

    return true;
}

int main(void)
{
    Tree t;
    Node* temp = NULL;
    int nodeNum;

    initTree(&t);

    addNode(&t, 80, NULL, NULL, "F8");
    addNode(&t, 130, NULL, NULL, "F7");
    addNode(&t, 120, t.tempLeft, t.tempRight, "F6");
    addNode(&t, 50, NULL, t.tempParent, "F3");
    temp = t.root;

    addNode(&t, 90, NULL, NULL, "F5");
    addNode(&t, 70, NULL, NULL, "F4");
    swapNode(t.tempLeft, t.tempRight);
    addNode(&t, 30, t.tempLeft, t.tempRight, "F2");
    addNode(&t, 20, t.root, temp, "F1");

    scanf("%d", &nodeNum);
    FindNode(&t, nodeNum);

    return 0;
}