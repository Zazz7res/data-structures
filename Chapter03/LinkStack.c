#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================================
// 1. 定义结构
// =====================================

//  定义链表的节点
typedef struct StackNode {
    char url[100];              //  数据域：存放网址
    struct StackNode *next;     //  指针域：指向下一个节点
} StackNode;

//  定义链栈
//  链栈其实就是一个指向栈顶节点的指针
typedef StackNode *LinkStack;

// ======================================
// 2. 核心操作函数
// ======================================

//  初始化：因为链栈不需要像顺序表那样申请数组，只需要把指针置空
LinkStack InitStack() {
    return NULL;
}

//  判空
int StackEmpty(LinkStack S) {
    return S == NULL;
}

//  进栈  --  Push
//  注意：因为要修改头指针，所以需要传 LinkStack 的指针（即二级指针）
void Push(LinkStack *S, char *url) {
    // 1. 创建新节点
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }

    //  2. 存入数据
    strcpy(newNode->url, url);

    //  3. 插入逻辑（头插法）
    //  新节点的 next 指向当前的栈顶
    newNode->next = *S;
    //  更新栈顶指针，指向新节点
    *S = newNode;

    printf(">> [访问网页]: %s\n ", url);
}

//  出栈   --  Pop
//  用 urlOut 带回被删除的数据
void Pop(LinkStack *S, char *urlOut) {
}
