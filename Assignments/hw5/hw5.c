#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _node
{
    char data;
    struct _node** child; // 자식 노드들을 모아놓은 포인터 배열
    struct _node* firstChild; // 첫번째 자식을 가리킴
    struct _node* nextChild; // 같은 부모를 가진 다음 자식 노드를 가리킴
    struct _node* lastChild; // 막내를 가리킴
} Node;

typedef struct _tree // 트리
{
    Node* root; // 루트 노드
    int count; // 노드 수
} Tree;

Node* getNode(const char d) // 노드 생성
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // 새 노드 동적 할당
    if (!newNode) return NULL;
    newNode->child = (Node**)malloc(sizeof(Node*) * 26); // 자식 노드들을 가리키는 포인터 배열 생성
    for (int i = 0; i < 26; i++) // 요소들을 NULL로 초기화
        newNode->child[i] = NULL;
    newNode->data = d; // 자료 삽입
    newNode->firstChild = newNode->nextChild = newNode->lastChild = 0; // 노드의 자식을 가리키는 포인터 초기화

    return newNode;
}

bool initTree(Tree* tr) // 트리 초기화
{
    tr->root = getNode(0); // 루트 노드 생성
    if (!tr->root) return false;

    tr->count = 0;
    return true;
}

bool isInternal(const Node* n) // 내부 노드인 경우 true를 반환
{
    return n->firstChild ? true : false;
}

Node* compareChar(Node* node, const char target) // 오름차순 비교기
{
    if (target < node->firstChild->data) return NULL; // 새 노드가 첫 자식이 되어야 되는 경우
    Node* pos = node->firstChild;
    while (pos->nextChild && (target > pos->data)) // 마지막 자식까지이거나 target 문자보다 앞에 와야 하는 문자들을 패스
        pos = pos->nextChild; // 다음 자식으로 간다.

    return pos; // 위치 반환
}

Node* getLocation(const Node* node, const char target) // 포인터 배열 내 위치 찾아 반환하는 함수
{
    return node->child[target - 'A'];
}

bool insertNode(Tree* tr, char* input) // 문자열에 따라 노드를 추적하고 추가하는 함수
{
    char* pos = input; // 문자열에 쓰일 포인터
    size_t len = strlen(input); // 문자열 길이 저장
    Node* nodePos = tr->root; // 루트 노드를 가리킨다.
    Node* temp = 0; // 위치 포인터

    for (; pos < input + len; pos++)
    {
        temp = getLocation(nodePos, *pos); // 위치를 찾는다.
        if (!temp) // 위치에 해당되는 게 NULL인 경우
        {
            temp = getNode(*pos); // 새 노드 생성
            tr->count++;
            if (!nodePos->firstChild) // 첫째인 경우
                nodePos->firstChild = nodePos->lastChild = temp;
            else // 둘째 이상
            {
                Node* loc = compareChar(nodePos, *pos); // 위치 찾기
                if (!loc) // 맨 앞에 와야 하는 경우
                {
                    temp->nextChild = nodePos->firstChild; // 맨 앞에 넣어 첫 자식 갱신
                    nodePos->firstChild = temp;
                }
                else if (loc != nodePos->lastChild) // 사이에 들어갈 경우
                {
                    temp->nextChild = loc->nextChild;
                    loc->nextChild = temp;
                }
                else // 맨 뒤에 들어가는 경우
                {
                    temp->nextChild = NULL;
                    nodePos->lastChild->nextChild = temp;
                    nodePos->lastChild = temp;
                }
            }
            nodePos->child[*pos - 'A'] = temp; // 부모 노드와 연결
            // 바로 위 형 노드의 nextChild를 temp로 설정한다.
        }
        nodePos = temp; // '커서'에 해당되는 nodePos를 자식 노드로 이동시킨다.
    }

    return true;
}

bool searchNode(Tree* tr, char* keyword) // 문자 찾기
{
    char* pos = keyword;
    Node* nodePos = tr->root;
    size_t len = strlen(keyword);
    
    for (; pos < keyword + len; pos++) // 키워드 찾기
    {
        if (!getLocation(nodePos, *pos)) // 해당 위치에 아무 것도 없는 경우 루프를 벗어난다. (아무것도 적지 않을 것)
            break;
        nodePos = getLocation(nodePos, *pos); // 그렇지 않은 경우 그 위치로 이동 
        printf("%c", nodePos->data); // 해당 문자 출력
    }
    putchar('\n');
    return true;
}

bool freeAll(Node* node) // 모든 노드 동적 할당 해제
{
    Node* childNode = node->firstChild; // 첫 자식을 가리키게 한다.
    while (childNode) // 자식을 모두 쳐 낸다.
    {
        Node* temp = childNode;
        childNode = childNode->nextChild;
        if (isInternal(temp)) // 아직 자식이 있는 경우 해당 자식으로 간다. (재귀)
            freeAll(temp);
    }
    free(node->child); // 이 구간으로 오면 외부노드이므로 (== 자식이 없음) 포인터 배열 해제
    free(node); // 노드 삭제

    return true;
}

int main(void)
{
    int in;
    char input[101]; // string input
    Tree tr;

    initTree(&tr);
    scanf("%d", &in); // Dictionary word count
    getchar();
    for (int i = 0; i < in; i++)
    {
        scanf("%[^\n]", input); // Type dictionary words
        getchar();
        insertNode(&tr, input);
    }
    scanf("%d", &in); // Search word count
    getchar();
    for (int i = 0; i < in; i++)
    {
        scanf("%[^\n]", input); // Type keyword
        getchar();
        searchNode(&tr, input); // Search keyword
    }

    freeAll(tr.root);
    return 0;
}