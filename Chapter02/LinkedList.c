#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =======================================
// 1. 定义节点（Node) 和 数据
// =======================================

//  书籍数据
typedef struct {
    int id;
    char name[50];
} Book;

//  链表节点
//  每一个节点包含：数据域 + 指针域
typedef struct Node {
    Book data;              //  数据域：存书
    struct Node *next;      //  指针域：存下一本书的地址
} Node;

//  简单定义：LinkList 就是指向 Node 的指针
typedef Node *LinkList;

// ========================================
// 2. 核心操作函数
// ========================================

//  初始化：创建一个空链表
//  返回头指针，初始为 NULL
LinkList InitList() {
    return NULL;
}

//  判空
int IsEmpty(LinkList L) {
    return L == NULL;
}

//  头插法：新书直接放到最前面
//  注意：因为要修改头指针的指向，所以需要传头指针的地址
void PushFront(LinkList *L, Book b) {
    // 1. 申请新节点空间
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存不足，无法入库！\n");
        return ;
    }

    // 2. 存入数据
    newNode->data = b;

    // 3. 插入逻辑（关键步骤）
    // 先把新节点的 next 指向原来的头结点
    newNode->next = *L;
    // 再把头指针更新为这个新节点
    *L = newNode;

    printf(">> [头插] 入库成功：%s\n", b.name);
}

// 尾插法：新书放到最后面
void PushBack(LinkList *L, Book b) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = b;
    newNode->next = NULL;   //  尾巴的 next 一定是 NULL

    //  特殊情况：如果是空链表，新节点就是头节点
    if (*L == NULL) {
        *L = newNode;
    } else {
        // 1. 找到现在的最后一个节点
        Node *p = *L;
        while (p->next != NULL) {
            p = p->next;  //往后挪
        }
        // 2. 把最后一个节点的 next 指向新节点
        p->next = newNode;  
    }
    printf(">> [尾插] 入库成功：%s\n", b.name);
}

//  打印链表
void PrintList(LinkList L) {
    printf("")
}
