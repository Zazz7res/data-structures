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
    printf("\n================== 链表馆藏列表 ===============\n");
    if (L == NULL) {
        printf("(空链表)\n");
    } else {
        Node *p = L;
        int count = 1;
        while (p != NULL) {
            printf("%d. [%d] %s\n", count++, p->data.id, p->data.name);
            p = p->next;  //  指针往后移
        }
    }
    printf("========================================\n\n");
}

//  按ID查找，返回节点指针
Node* SearchById(LinkList L, int id) {
    Node *p = L;
    while (p != NULL) {
        if (p->data.id == id) {
            return p;  //  找到了
        }
        p = p->next;
    }
    return NULL;  //没找到
}

//  删除指定ID的节点
void DeleteNode(LinkList *L, int id) {
    if (*L == NULL) {
        return ;
    }

    Node *p = *L;
    Node *prev = NULL;  //  用来记录前一个节点

    //  遍历查找
    while (p != NULL && p->data.id != id) {
        prev = p;
        p = p->next;
    }

    //  如果 p 是 NULL，说明没找到
    if (p == NULL) {
        printf(">> 未找到 ID 为%d 的书\n", id);
        return ;
    }

    //  找到了，开始删除
    //  情况1：删除的是头节点
    if (prev == NULL) {
        *L = p->next;
    }
    //  情况2：删除的是中间或尾部节点
    else{
        prev->next = p->next;  //  让前一个节点直接连向下一个节点，跳过 p
    }

    free(p);  //  释放被删除节点的内存（非常重要！）
    printf(">> 下架成功：ID %d\n", id);
}

//  销毁整个链表
void DestroyList(LinkList *L) {
    Node *p = *L;
    Node *temp;
    while (p != NULL) {
        temp = p->next;     //  先记下下一个节点在哪
        free(p);            //  释放当前节点
        p = temp;           //  移动到下一个
    }
    *L = NULL;
    printf(">> 链表已销毁，内存已全部释放。\n");
}

// =====================================
// 3. 主程序
// =====================================

int main(void) {
    //  1. 初始化链表头指针
    LinkList library = InitList();

    //  2. 准备数据
    Book b1 = {101, "C程序设计"};
    Book b2 = {102, "数据结构"};
    Book b3 = {103, "算法导论"};
    Book b4 = {104, "计算机网络"};

    //  3. 测试头插（后进的排前面，像叠盘子）
    printf("--- 测试头插 ---\n");
    PushFront(&library, b1);
    PushFront(&library, b2);
    PushFront(&library, b3);

    //  4. 测试尾插（后进的排后面,像排队）
    printf("\n--- 测试尾插 ---\n");
    PushBack(&library, b4);
    PrintList(library);         //   此时最后面的是 104

    //  5. 测试查找
    printf("\n--- 测试查找 ---\n");
    int targetId = 102;
    Node *result = SearchById(library, targetId);
    if (result != NULL) {
        printf(">> 找到了：%s\n", result->data.name);
    } else {
        printf(">> 未找到");
    }

    //  6. 测试删除
    printf("\n--- 测试删除 ---\n");
    //  删头节点（103）
    DeleteNode(&library, 103);
    PrintList(library);

    // 删除中间节点（102）
    DeleteNode(&library, 102);
    PrintList(library);

    //  7. 销毁
    DestroyList(&library);

    return 0;
}
