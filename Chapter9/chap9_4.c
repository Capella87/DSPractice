#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int Data;

typedef struct _node
{
    struct _node* left;
    Data d;
    struct _node* right;
} Node;

typedef struct _tree
{
    struct _node* root;
    int count;
} Tree;

bool initTree(Tree* tr)
{
    tr->root = NULL;
    tr->count = 0;

    return true;
}

Node* getNode(const Data d)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->d = d;
    newNode->left = newNode->right = NULL;

    return newNode;
}

bool isInternal(const Node* node)
{
    return node->left || node->right ? true : false;
}

Node* searchNode(Node* node, const Data d)
{
    // 선위 순회
    Node* cur = NULL;
    if (node->d == d)
        return node;
    if (isInternal(node))
    {
        if (node->left && !cur) cur = searchNode(node->left, d);
        if (node->right&& !cur) cur = searchNode(node->right, d);
    }


    return cur;
}

bool makeNode(Tree* tr, const Data d, const Data left, const Data right)
{
    Node* pos = NULL;

    if (!tr->root)
    {
        pos = getNode(d);
        if (!pos) return false;
        tr->root = pos;
        tr->count++;
    }
    else
        pos = searchNode(tr->root, d);

    if (left)
    {
        pos->left = getNode(left);
        if (!pos) return false;
        tr->count++;
    }
    if (right)
    {
        pos->right = getNode(right);
        if (!pos) return false;
        tr->count++;
    }

    return true;
}

bool freeTree(Node* node)
{
    if (isInternal(node))
    {
        if (node->left) freeTree(node->left);
        if (node->right) freeTree(node->right);
    }
    free(node);

    return true;
}

bool goDestNode(Node* node, char* script)
{
    char* pos = script;
    size_t len = strlen(script);

    for (; pos <= script + len; pos++)
    {
        printf(" %d", node->d);
        switch (*pos)
        {
        case 'L':
            node = node->left;
            break;
        case 'R':
            node = node->right;
        }
    }
    putchar('\n');

    return true;
}

int main(void)
{
    int it;
    int nodeNum, leftNode, rightNode;
    char input[101];
    Tree tr;
    initTree(&tr);

    scanf("%d", &it);
    for (int i = 0; i < it; i++)
    {
        scanf("%d %d %d", &nodeNum, &leftNode, &rightNode);
        makeNode(&tr, nodeNum, leftNode, rightNode);
    }

    scanf("%d", &it);
    getchar();
    for (int i = 0; i < it; i++)
    {
        scanf("%[^\n]", input);
        getchar();
        goDestNode(tr.root, input);
    }

    freeTree(tr.root);
    return 0;
}