#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int Data;

typedef struct _node // 그룹 내 요소(element)
{
    struct _node* prev; // 이전 노드
    struct _node* next; // 다음 노드
    Data element; // 원소
} Node;

typedef struct _groupnode // 그룹들
{
    char groupName;
    struct _groupnode* gNext; // 다음 그룹

    Node* head; // 헤더
    Node* trailer; // 트레일러
    int nodeCount; // 그룹 내 원소 수
} GroupNode;

typedef struct _group // 그룹의 리스트
{

    GroupNode* ghead; // 그룹 헤드
    int groupCount; // 그룹 수
} GroupList;

bool Create_group(GroupList* list, const char g); // 그룹 생성
bool Show_all(GroupList* list); // 현재 생성되어 있는 그룹과 그 원소들을 출력
bool Add_element(GroupList* list, const char g, const Data e); // 그룹 내 원소 추가
bool Destroy_group(GroupList* list, const char g); // 그룹 '파괴자'(Destructor)
bool Remove_element(GroupList* list, const char g, const Data e); // 그룹 내 원소 삭제

bool gListInit(GroupList* target); // 그룹 모음 초기화
bool freeAll(GroupList* list); // 모든 동적 할당 해제; 프로그램 종료시 호출
GroupNode* searchGroupList(GroupList* list, const char groupName); // 그룹 검색
bool alignGroup(GroupList* list, GroupNode* target); // 그룹 배치 함수
bool alignElement(GroupNode* g, Node* newNode); // 원소 배치 함수
Node* searchNode(GroupNode* g, const Data e); // 그룹 내 원소 검색

void getCommand(GroupList* list); // 명령문 수행

// Group maintenance
int main(void)
{
    GroupList alphabet; // 그룹 저장 장소
    int event_count; // 명령어 수행 개수 저장

    gListInit(&alphabet); // 초기화

    scanf("%d", &event_count); // 명령어 갯수 입력 받기
    getchar();
    for (int i = 0; i < event_count; i++) // event_count 번만큼 수행
        getCommand(&alphabet); // 호출

    freeAll(&alphabet); // 모든 동적 할당 해제
    return 0;
}

bool Create_group(GroupList* list, const char g) // 그룹 생성
{
    // 해당 이름의 그룹이 있는지 일단 검색; 만약 해당 그룹이 반환된다면 함수 종료
    if (searchGroupList(list, g))
        return false;
    // If the group exists, return NULL and exit this function.

    // Otherwise, Make a new one.
    GroupNode* newGroup = (GroupNode*)malloc(sizeof(GroupNode));
    newGroup->groupName = g; // 이름 저장

    newGroup->head = (Node*)malloc(sizeof(Node)); // 헤드 생성
    newGroup->trailer = (Node*)malloc(sizeof(Node)); // 트레일러 생성
    newGroup->head->next = newGroup->trailer;
    newGroup->head->prev = NULL;
    newGroup->trailer->next = NULL;
    newGroup->trailer->prev = newGroup->head;
    // 위 4개는 두 노드를 연결

    newGroup->nodeCount = 0; // 저장된 수 초기화

    if (alignGroup(list, newGroup)) // 배치에 성공했으면 true 반환으로 함수 종료
        return true;

    return false;
}

bool Show_all(GroupList* list) // 모든 그룹과 하위 원소들을 출력
{
    if (!list->groupCount) return false; // 그룹이 없는 경우 함수 종료
    GroupNode* groupCursor = list->ghead->gNext; // '커서'; 순차적으로 가리키면서 종료

    while (groupCursor) // groupCursor가 현재 가리키고 있는 그룹 노드의 다음을 가리켜 NULL이 나올 때까지 돌린다.
    {
        Node* cursor = groupCursor->head->next; // 그룹 내 원소 노드를 가리킬 '커서'
        printf("%c:", groupCursor->groupName); // 그룹명 출력
        while (cursor != groupCursor->trailer) // 트레일러가 나올 때까지 반복
        {
            printf(" %d", cursor->element); // 원소 출력
            cursor = cursor->next; // 다음 원소로..
        }
        putchar('\n');
        groupCursor = groupCursor->gNext; // 다음 그룹으로..
    }

    return true;
}

bool Add_element(GroupList* list, const char g, const Data e) // 그룹 내 원소 출력
{
    GroupNode* gLocation = searchGroupList(list, g); // 해당 이름의 그룹을 찾는다.
    if (!gLocation) return false; // 없다면(NULL을 받음) 종료
    if (searchNode(gLocation, e)) return false; // 해당 원소가 그룹 내 있는 경우(NULL이 아님) 종료

    Node* newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 생성
    newNode->element = e; // 값 대입

    if (alignElement(gLocation, newNode)) // 적절한 위치를 찾아서 넣기 성공하면 종료
        return true;

    return false;
}

bool Destroy_group(GroupList* list, const char g) // 그룹 '파괴자'
{
    GroupNode* pos = searchGroupList(list, g); // 해당 이름의 그룹을 찾는다.
    if (!pos) return false; // 해당 그룹이 존재하지 않으면 종료
    Node* cursor = pos->head->next; // 원소를 삭제하기 위한 커서
    Node* rpos; // 위 커서를 돕는 또 다른 커서

    GroupNode* posPrev = list->ghead; // 이중 리스트가 아니라서 그 전 그룹을 따로 찾아야 한다. 그러므로 새로운 그룹 커서 선언
    while (posPrev->gNext != pos) // pos 전까지 계속 이동
        posPrev = posPrev->gNext;

    while (cursor != pos->trailer) // 헤드와 트레일러 간 모든 원소 삭제
    {
        rpos = cursor; // 일단 rpos에 해당 원소 저장
        cursor = cursor->next; // cursor는 다음 원소를 가리키게 미리 설정해야 한다.
        free(rpos); // 원소 '파괴'
    }
    free(pos->head); // 헤드 파괴
    free(pos->trailer); // 트레일러 파괴
    posPrev->gNext = pos->gNext; // 이전 그룹이 삭제된 그룹의 다음 그룹을 가리키게 설정
    list->groupCount--; // 총 그룹 수 1 감소
    free(pos); // 그룹 완전 삭제

    return true;
}

bool Remove_element(GroupList* list, const char g, const Data e) // 그룹 내 원소 삭제
{
    GroupNode* pos = searchGroupList(list, g); // 삭제 대상 원소가 있는 그룹을 찾는다.
    if (!pos) return false; // 없는 경우 NULL을 반환받는데 이 경우 함수 종료
    Node* cursor = searchNode(pos, e); // 해당 원소 노드를 찾는다.
    if (!cursor) return false; // 없는 경우 종료

    cursor->prev->next = cursor->next; // 해당 원소 이전 원소가 삭제 대상 원소의 다음 원소를 가리키도록 수정
    cursor->next->prev = cursor->prev; // 삭제 대상 다음 원소가 삭제 대상 원소의 이전 원소를 가리키도록 수정
    free(cursor); // 원소 파괴
    pos->nodeCount--; // 원소 수 1 감소

    return true;
}



// Internal functions

bool gListInit(GroupList* target) // 그룹 총괄 리스트 초기화 함수
{
    target->ghead = (GroupNode*)malloc(sizeof(GroupNode)); // 그룹 헤드 생성
    if (!target->ghead) return false; // 에러 발생 시 종료

    target->ghead->gNext = NULL; // 헤더 다음 가리키는 포인터를 NULL로 설정
    target->ghead->groupName = 0; // 그룹 이름 NULL로 초기화(NULL == '\0')
    target->ghead->head = target->ghead->trailer = NULL; // 해당 더미 그룹 노드 설정; NULL로 초기화
    target->ghead->nodeCount = 0; // 헤더 그룹 내 노드 수도 초기화

    target->groupCount = 0; // 그룹 수 초기화

    return true;
}

GroupNode* searchGroupList(GroupList* list, const char groupName) // 그룹을 그룹명으로 색인하는 함수
{
    if (!list->groupCount) return NULL; // 리스트에 그룹이 하나도 없는 경우 함수 종료

    GroupNode* cursor = list->ghead->gNext; // 색인할 때 사용할 커서
    
    while (cursor) // 처음부터 끝까지 색인; 끝이면 NULL이 나올 것이므로 루프 종료
    {
        if (cursor->groupName == groupName) // 해당 그룹이 나온 경우
            return cursor; // 해당 그룹을 가리키는 포인터를 반환
        cursor = cursor->gNext; // 그렇지 않은 경우 다음 그룹으로 이동..
    }

    return NULL; // 없는 경우 NULL을 반환
}

Node* searchNode(GroupNode* g, const Data e) // 원소 노드를 색인하는 함수
{
    Node* cursor = g->head->next; // 색인에 사용할 커서

    while (cursor != g->trailer) // 트레일러 더미 노드가 나오기 전까지 루프
    {
        if (cursor->element == e) // 해당 노드를 발견한 경우
            return cursor; // 해당 노드를 가리키는 포인터를 반환
        cursor = cursor->next; // 그렇지 않은 경우 다음 노드로 포인터 이동
    }

    return NULL; // 없는 경우 NULL을 반환
}

bool alignGroup(GroupList* list, GroupNode* target) // 새로 생성된 그룹 노드를 적절한 곳에 오름차순으로 배치시키는 함수
{
    GroupNode* cursor = list->ghead->gNext; // 그룹 커서 사용
    GroupNode* prevCursor = list->ghead; // 그룹 커서 이전 노드를 가리키는 커서

    while (cursor) // 그룹들을 전부 색인
    {
        if (target->groupName < cursor->groupName) // 커서의 그룹명이 추가 대상 그룹보다 뒤에 오는 문자일 때 멈춘다.
            break;
        prevCursor = cursor; // 그 외에는 갱신한다.
        cursor = cursor->gNext;
    }

    prevCursor->gNext = target;
    target->gNext = (!cursor) ? NULL : cursor; // cursor가 NULL인 경우(새로 생성한 그룹 노드에 처음 추가하거나 마지막에 추가하는 경우)에는 NULL을, 그렇지 않다면 cursor 대입
    list->groupCount++; //그룹 수 증가

    return true;
}

bool alignElement(GroupNode* location, Node* newNode) // 그룹 내 원소 배치
{
    Node* cursor = location->head->next; // 그룹 내 원소들을 가리킬 커서 포인터

    while (cursor != location->trailer) // 트레일러 전까지 기존의 원소들을 조회
    {
        if (newNode->element < cursor->element) // 새로 추가할 대상의 수가 커서가 가리키는 원소 노드의 수보다 작을 경우 루프 이탈
            break;
        cursor = cursor->next; // 그렇지 않은 경우 갱신
    }
    
    cursor->prev->next = newNode; // 커서 이전 원소가 가리키는 다음 원소 값을 newNode로 교체
    newNode->prev = cursor->prev; // 연결
    newNode->next = cursor; // 연결
    cursor->prev = newNode; // 연결
    location->nodeCount++; // 그룹 내 원소 수 증가

    return true;
}

void getCommand(GroupList* list) // 명령을 받아 수행하는 함수
{
    char input[21]; // 문자열의 형식으로 받기 때문에 이렇게 선언

    scanf("%[^\n]", input); // 입력 받는다.
    getchar();

    switch (input[0]) // 맨 앞에 오는 문자가 명령어이다. 이를 분석
    {
    case 'A':
        Add_element(list, input[2], atoi(input + 4)); // 문자열 해석 후 원소 추가
        break;
    case 'C':
        Create_group(list, input[2]);  // 그룹 생성
        break;
    case 'D':
        Destroy_group(list, input[2]); // 그룹 파괴
        break;
    case 'R':
        Remove_element(list, input[2], atoi(input + 4)); // 그룹 내 원소 제거
        break;
    case 'S':
        Show_all(list); // 모든 그룹들과 하위 원소들 출력
        break;
    }
}

bool freeAll(GroupList* list) // 종료 전 모든 그룹들과 하위 원소 제거
{
    while (list->ghead->gNext) // list->ghead->gNext != NULL; 끝까지 수행
        Destroy_group(list, list->ghead->gNext->groupName); // 별도로 구현하지 않고 파괴자 역할을 하는 Destroy_group을 여러 번 호출
    free(list->ghead); // 할당 해제

    return true;
}