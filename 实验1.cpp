#include <stdio.h>
#include <stdlib.h>

// 定义单链表结点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Node* LinkedList;

// 初始化单链表
LinkedList initList() {
    LinkedList L;
    L = (Node*)malloc(sizeof(Node));  // 创建头结点
    if (!L) {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    L->next = NULL;  // 初始化为空链表
    return L;
}

// 求单链表长度
int listLength(LinkedList L) {
    Node* p = L->next;
    int length = 0;
    while (p) {
        length++;
        p = p->next;
    }
    return length;
}

// 按位置查找
Node* getElem(LinkedList L, int position) {
    if (position < 1 || position > listLength(L)) return NULL;
    Node* p = L->next;
    int i = 1;
    while (i < position) {
        p = p->next;
        i++;
    }
    return p;
}

// 按值查找
int locateElem(LinkedList L, int value) {
    Node* p = L->next;
    int i = 1;
    while (p) {
        if (p->data == value) return i;
        p = p->next;
        i++;
    }
    return -1;  // 未找到返回-1
}

// 在位置i插入一个数据元素
int insertElem(LinkedList L, int position, int value) {
    if (position < 1 || position > listLength(L) + 1) return 0;
    Node* p = L;
    Node* newNode;
    int i = 1;
    while (i < position) {
        p = p->next;
        i++;
    }
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = p->next;
    p->next = newNode;
    return 1;
}

// 删除位置i的数据元素
int deleteElem(LinkedList L, int position) {
    if (position < 1 || position > listLength(L)) return 0;
    Node* p = L;
    Node* q;
    int i = 1;
    while (i < position) {
        p = p->next;
        i++;
    }
    q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}

// 遍历单链表
void traverseList(LinkedList L) {
    Node* p = L->next;
    while (p) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

// 合并链表
LinkedList mergeList(LinkedList L1, LinkedList L2) {
    Node* p1 = L1->next;
    Node* p2 = L2->next;
    LinkedList L = initList();
    Node* p = L;

    while (p1 && p2) {
        if (p1->data <= p2->data) {
            p->next = p1;
            p1 = p1->next;
        }
        else {
            p->next = p2;
            p2 = p2->next;
        }
        p = p->next;
    }

    if (p1) {
        p->next = p1;
    }
    else {
        p->next = p2;
    }

    free(L1);
    free(L2);

    return L;
}

// 销毁单链表
void destroyList(LinkedList L) {
    Node* p, * q;
    p = L;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
}

int main() {
    printf("===================================\n");
    printf("1. Initializing List\n");
    printf("===================================\n");
    LinkedList L = initList();  // 初始化单链表
    traverseList(L); // 遍历单链表

    printf("\n===================================\n");
    printf("2. Insertion Operations\n");
    printf("===================================\n");
    insertElem(L, 1, 10);
    insertElem(L, 2, 20);
    insertElem(L, 3, 30);
    traverseList(L); // 遍历单链表

    printf("\n===================================\n");
    printf("3. Locate Element By Value\n");
    printf("===================================\n");
    int position = locateElem(L, 20);  // 按值查找
    printf("Element 20 is at position: %d\n", position);

    printf("\n===================================\n");
    printf("4. Get Element By Position\n");
    printf("===================================\n");
    Node* nodeAtPosition2 = getElem(L, 2);  // 按位置查找
    printf("Element at position 2: %d\n", nodeAtPosition2->data);

    printf("\n===================================\n");
    printf("5. Calculate List Length\n");
    printf("===================================\n");
    int length = listLength(L);  // 求单链表长度
    printf("List length: %d\n", length);

    printf("\n===================================\n");
    printf("6. Deletion Operation\n");
    printf("===================================\n");
    deleteElem(L, 2); // 删除位置2的数据元素
    traverseList(L); // 遍历单链表

    printf("\n===================================\n");
    printf("7. Initializing and Inserting into Second List\n");
    printf("===================================\n");
    LinkedList L2 = initList();  // 初始化另一个单链表
    insertElem(L2, 1, 5);
    insertElem(L2, 2, 15);
    insertElem(L2, 3, 25);
    traverseList(L2); // 遍历单链表

    printf("\n===================================\n");
    printf("8. Merging Lists\n");
    printf("===================================\n");
    LinkedList mergedL = mergeList(L, L2);
    traverseList(mergedL); // 遍历单链表

    printf("\n===================================\n");
    printf("9. Destroying the List\n");
    printf("===================================\n");
    destroyList(mergedL);
    printf("List destroyed.\n");

    return 0;
}

