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
    if (StackEmpty(*S)) {
        printf(">> [错误]: 没有历史记录可退出了！（栈空）\n");
        return ;
    }

    //  1. 暂存栈顶节点
    StackNode *temp = *S;

    //  2. 取出数据
    strcpy(urlOut, temp->url);

    //  3. 栈顶指针下移（指向下一个节点）
    *S = (*S)->next;

    //  4. 释放被删除的节点（重要）
    free(temp);

    printf(">> [点击后退]: 返回到 %s\n", urlOut);
}

//  取栈顶元素  --  GetTop
//  只看数据，不删除
void GetTop(LinkStack S, char *urlOut) {
    if (StackEmpty(S)) {
        printf("栈空，无法取出\n");
        return ;
    }
    strcpy(urlOut, S->url);
}

//  打印当前历史记录栈（从栈顶往下打印）
void printStack(LinkStack S) {
    if (StackEmpty(S)) {
        printf("    [历史记录为空]\n");
        return ;
    }

    printf("    [当前历史记录栈]: ");
    StackNode *p = S;
    while (p != NULL) {
        printf("%s ", p->url);
        p = p->next;
        if (p != NULL) printf("-> ");
    }
    printf("\n");
}

// ==============================================
//  3. 主程序（模拟浏览器操作）
// ==============================================

int main(void) {
    LinkStack history = InitStack();
    char currentUrl[100];

    printf("--- 模拟浏览器历史记录（链表实现）---\n\n");

    //  1. 用户连续访问几个网页
    printf(">>> 用户操作：访问 Google, 访问 Bilibili, 访问 GitHub\n");
    Push(&history, "www.google.com");
    Push(&history, "www.bilibili.com");
    Push(&history, "www.github.com");

    //  打印一下看看
    printStack(history);
    //  栈顶应该是 Github -> Bilibili -> Google

    printf("\n");

    //  2. 用户点了一次“后退”按钮
    printf(">>> 用户操作：点击 [后退] 按钮");
    Pop(&history, currentUrl);           //  弹出 GitHub
    printStack(history);                            //  栈顶变成了 Bilibili

    printf("\n");

    //  3. 用户又访问了一个新网页（新网页会覆盖旧的“前进”历史，这里是模拟压线
    printf(">>> 用户操作：访问新网页 wwww.stackoverflow.com\n");
    Push(&history, "www.stackoverflow.com");
    printStack(history);
    //  栈顶：StackOverflow -> Bilibili -> Google

    printf("\n");

    //  4. 用户连续狂点后退
    printf(">>> 用户操作：连狂点 [后退] 直到清除历史\n");
    Pop(&history, currentUrl);  // StackOverflow
    Pop(&history, currentUrl);  //  Bilibili
    Pop(&history, currentUrl);  //  Google

    printf("\n      当前状态：");
    printStack(history);

    printf("\n>>> 用户再点一次后退 (测试栈空): \n");
    Pop(&history, currentUrl);  //   应该报错

    return 0;
}
