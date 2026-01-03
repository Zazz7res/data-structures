#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

// ==========================================
// 1. 定义结构
// ==========================================

#define MAX_SIZE 10  //  假设编辑器只能记录最近 10 步操作

typedef char SElemType;
                     //
                    
//  定义顺序栈
typedef struct {
    SElemType data[MAX_SIZE];   //  存放数据的数组
    int top;                    //  栈顶指针（类似于 size,指向当前栈顶元素的下标)
} SqStack;

// ============================================
// 2. 核心操作函数
// ============================================

//  初始化栈
//  约定：top = -1 表示栈空
void InitStack(SqStack *S) {
    S->top = -1;
}

// 判空
int StackEmpty(SqStack S) {
    return S.top == -1;
}

//  判满
int StackFull(SqStack S) {
    return S.top == MAX_SIZE - 1;
}

//  进栈  -- Push
void Push(SqStack *S, SElemType e) {
    //  1. 先检查栈是否满了
    if (StackFull(*S)) {
        printf(">> 错误：操作记录已满，无法记录更多步骤！（栈溢出）\n");
        return ;
    }

    //  2. 栈顶指针先上移，再赋值
    //  注意：因为是 top = -1 开始，所以先 ++ 才能放到 data[0]
    S->top++;
    S->data[S->top] = e;

    printf(">> 记录操作：输入了 '%c'\n", e);
}

//  出栈  --  Pop
//  用 e 带回被删除的数据
void Pop(SqStack *S, SElemType *e) {
    // 1. 先检查栈是否为空了
     if (StackEmpty(*S)) {
         printf(">> 错误：没有可撤销的操作了！（栈空）\n");
         return ;
     }

     // 2. 先取值，栈顶指针再下移
     *e = S->data[S->top];
     S->top--;

     printf(">> 执行撤销：移除了 '%c'\n", *e);
}

//  读取栈顶元素  --  GetTop
//  只看不删
void GetTop(SqStack S, SElemType *e) {
    if (StackEmpty(S)) {
        printf(">> 栈是空的\n");
        return ;
    }
    *e = S.data[S.top];
    //  printf("当前栈顶元素是：%c\n", *e);
}

//  打印当前栈内所有元素（从栈底到栈顶）
void PrintStack(SqStack S) {
    if (StackEmpty(S)) {
        printf("[当前操作记录为空]\n");
        return ;
    }

    printf("[当前操作记录]: ");
    for (int i = 0; i <= S.top; i++) {
        printf("%c ", S.data[i]);
    }
    printf("\n");
}

// ==================================================
// 3. 主程序（模拟编辑器）
// ==================================================

int main(void) {
    SqStack editHistory;        //  定义一个栈来存历史记录
    InitStack(&editHistory); //  初始化

    char ch;
    char deletedVal;


    printf("--- 模拟文本编辑器（输入为Push, 0 为 Pop/撤销， q 为退出) ---\n");

    //  这里为了演示方便，用循环模拟
    //  实际上编辑器是你每敲一次键盘，系统就调用一次 Push

    //  1. 模拟输入一连串字符
    printf("\n>>> 用户输入: H, e, l, l, o\n");
    Push(&editHistory, 'H');
    Push(&editHistory, 'e');
    Push(&editHistory, 'l');
    Push(&editHistory, 'l');
    Push(&editHistory, 'o');
    
    PrintStack(editHistory);

    //  2. 模拟按一次 Ctrl + Z （撤销）
    printf("\n>>> 用户按下撤销 （Ctrl + Z)\n");
    Pop(&editHistory, &deletedVal);  //  弹出 'o'
    PrintStack(editHistory);

    //  3. 再模拟输入一个 '!'
    printf("\n>>> 用户输入：!\n");
    Push(&editHistory, '!');
    PrintStack(editHistory);

    //  4. 连续按两次撤销
    printf("\n>>> 用户连续按两次撤销\n");
    Pop(&editHistory, &deletedVal);  // 弹出 '!'
    Pop(&editHistory, &deletedVal);  // 弹出 'l'
    PrintStack(editHistory);

    //  5. 测试栈空的情况
    printf("\n>>> 用户赋能狂按撤销（直到栈空)\n");
    //  剩下的应该是 H, e, l, 我们弹出 4 次，最后一次会报错
    for (int i = 0; i < 4; i++) {
        Pop(&editHistory, &deletedVal);
    }

    return 0;
}
