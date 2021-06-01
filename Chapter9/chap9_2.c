#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Data;
typedef enum dir { no, lft, rgt } dir;
enum trv { pre = 1, in = 2, post = 3 };

typedef struct _node
{
    Data data;
    int id;
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
    tr->root = tr->tempLeft = tr->tempParent = tr->tempRight = NULL;
    tr->n = 0;

    return true;
}

bool isInternal(const Node* node)
{
    return node->left || node->right ? true : false;
}

bool isExternal(const Node* node)
{
    return !node->left && !node->right ? true : false;
}

Node* createNode(const Data d, const int id)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;

    newNode->left = newNode->right = NULL;
    newNode->data = d;
    newNode->id = id;
    
    return newNode;
}

bool insertNode(Tree* tr, const Data d, const int id, const dir dr)
{
    Node* node = createNode(d, id);
    if (!node) return false;
  
    tr->n++;
    if (dr == lft && tr->tempLeft || dr == rgt && tr->tempRight || dr == no || tr->tempRight && tr->tempLeft) // Make parent node
    {
        node->left = tr->tempLeft;
        node->right = tr->tempRight;
        tr->tempLeft = tr->tempRight = 0;
        if (dr == lft) tr->tempLeft = node;
        else if (dr == rgt) tr->tempRight = node;
        else tr->root = tr->tempParent = node;
    }
    else if (dr == lft && !tr->tempLeft) // for external node
        tr->tempLeft = node;
    else if (dr == rgt && !tr->tempRight)
        tr->tempRight = node;

    if ((!tr->root || isInternal(node)) && !tr->tempParent)
        tr->root = node;

    return true;
}

void preorderTrv(Node* pos, const int id, bool prt) // preorder traversal
{
    if (prt || id == pos->id) // 일치하는 경우이거나 일치하는 정보를 찾은 이후 순회
    {
        printf(" %d", pos->data);
        if (isInternal(pos))
        {
            if (pos->left) preorderTrv(pos->left, id, true);
            if (pos->right) preorderTrv(pos->right, id, true);
        }

        return true;
    }
    else
    {
        if (isInternal(pos))
        {
            if (pos->left) preorderTrv(pos->left, id, false);
            if (pos->right) preorderTrv(pos->right, id, false);
        }
        return false;
    }
}

void inorderTrv(Node* pos, const int id, bool prt) // preorder traversal
{
    if (isInternal(pos) && pos->left)
        inorderTrv(pos->left, id, false);
    if (pos->id == id || prt)
    {
        if (isInternal(pos) && pos->left)
            inorderTrv(pos->left, id, true);
        printf(" %d", pos->data);
        if (isInternal(pos) && pos->right)
            inorderTrv(pos->right, id, true);
    }
    else
        if (isInternal(pos) && pos->right)
            inorderTrv(pos->right, id, false);
}

void postorderTrv(Node* pos, const int id, bool prt)
{
    if (isInternal(pos) && pos->left)
        postorderTrv(pos->left, id, false);
    if (isInternal(pos) && pos->right)
        postorderTrv(pos->right, id, false);
    if (pos->id == id || prt)
    {
        if (isInternal(pos))
        {
            if (pos->left) postorderTrv(pos->left, id, true);
            if (pos->right) postorderTrv(pos->right, id, true);
        }
        printf(" %d", pos->data);
    }
}

void finder(Tree* tr, const int mode, const int id)
{
    if (id > 8 || id < 1)
    {
        printf("-1\n");
        return;
    }
    switch (mode)
    {
    case pre:
        preorderTrv(tr->root, id, false);
        break;
    case in:
        inorderTrv(tr->root, id, false);
        break;
    case post:
        postorderTrv(tr->root, id, false);
        break;
    }
    putchar('\n');
}

void freeAll(Node* pos)
{
    if (isInternal(pos) && pos->left)
        freeAll(pos->left);
    if (isInternal(pos) && pos->right)
        freeAll(pos->right);
    free(pos);
}

int main(void)
{
    Tree t;
    int searchMode, id;

    initTree(&t);
    insertNode(&t, 80, 8, rgt);
    insertNode(&t, 130, 7, lft);
    insertNode(&t, 120, 6, rgt);
    insertNode(&t, 50, 3, rgt);
    insertNode(&t, 20, 1, no);
    insertNode(&t, 90, 5, rgt);
    insertNode(&t, 70, 4, lft);
    insertNode(&t, 30, 2, lft);
    t.root->left = t.tempLeft;

    scanf("%d %d", &searchMode, &id);
    finder(&t, searchMode, id);
    
    freeAll(t.root);
    return 0;
}