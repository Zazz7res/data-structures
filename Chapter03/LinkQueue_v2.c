#include <stdio.h>
#include <stdlib.h>

// =============================================
//  1. 数据结构定义
// =============================================

//  定义队列中元素的类型，这里假设是 int, 方便演示
typedef int QDataType;

//   定义链队列的节点结构
typedef struct QNode {
    QDataType data;             //  数据域
    struct QNode *next;         //   指针域，指向下一个节点
} QNode;

//  定义链队列的管理结构体
//  这里体现了结构体嵌套：LinkQueue 内部包含了指向 QNode 的指针
typedef struct {
    QNode *front;               //  队头指针
    QNode *rear;                //  队尾指针
} LinkQueue;

// =============================================
//  2. 基础操作函数声明
// =============================================

//  初始化队列
void InitQueue(LinkQueue *q);

//   判空操作，若空返回 1，非空返回 0
int IsEmpty(LinkQueue *q);

//  入队操作
void EnQueue(LinkQueue *q, QDataType x);

//  出队操作，用 x 返回出队的值
void DeQueue(LinkQueue *q, QDataType *x);

//  获取队头元素，用 x 返回
void GetHead(LinkQueue *q, QDataType *x);

//  销毁队列，释放所有内存
void DestroyQueue(LinkQueue *q);

//  打印队列当前内容（辅助调试用）
void PirntQueue(LinkQueue *q);

// ===========================================
//  3. 函数实现（你可以跟着敲这一部分)
// ===========================================

//   初始化队列：将头尾指针置空
void InitQueue(LinkQueue *q) {
    q->front = q->rear = NULL;
    printf("队列已初始化。\n");
}

//  判空操作
int IsEmpty(LinkQueue *q) {
    //  只要头指针为空，说明队列里没东西
    if (q->front == NULL) {
        return 1;
    }
    return 0;
}

//  入队操作
void EnQueue(LinkQueue *q, QDataType x) {
    //  1. 创建新节点
    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    if (newNode == NULL) {
        printf("内存分配失败，入队错误！\n");
        return;
    }
    newNode->data = x;
    newNode->next = NULL;  //   新节点的下一个展示为空

    //  2. 将新节点链接到队尾
    if (IsEmpty(q)) {
        //  如果是第一个节点，头尾指针都指向它
        q->front = q->rear = newNode;
    } else {
        //  否则，挂在当前 rear  的后面，然后更新 rear
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("元素 %d 入队成功。\n", x);
}

//  出队操作
void DeQueue(LinkQueue *q, QDataType *x) {
    //  1. 判空
    if (IsEmpty(q)) {
        printf("队列为空，无法出队！\n");
        return;
    }

    //  2. 记录要删除的节点（对头）
    QNode *p = q->front;
    *x = p->data;  //  取出数据带回

    //  3. 移动 front 指针
    q->front = p->next;

    //  4. 特殊情况处理：如果出队后队列空了， rear 也要置空
    if (q->front == NULL) {
        q->rear = NULL;
    }

    //  5. 释放内存
    free(p);
    printf("元素 %d 出队成功。\n", *x);
}

//  获取队头元素
void GetHead(LinkQueue *q, QDataType *x) {
    if (IsEmpty(q)) {
        printf("队列为空，无队头元素！\n");
        return;
    }
    *x = q->front->data;
}

//  销毁队列
void DestroyQueue(LinkQueue *q) {
    //  循环出队直到为空，或者直接遍历链表释放
    while (!IsEmpty(q)) {
        QDataType temp;
        DeQueue(q, &temp);  //  借用 DeQueue 来释放节点
    }
    printf("队列已销毁。\n");
}

//   打印队列
void PrintQueue(LinkQueue *q) {
    if (IsEmpty(q)) {
        printf("队列当前为空 []\n");
        return;
    }
    printf("队列当前元素：[ ");
    QNode *p = q->front;
    while (p != NULL) {
        printf("%d", p->data);
        p = p->next;
    }
    printf("]\n");
}

// =================================================
//  4. 主函数测试
// ==================================================

int main(void) {
    LinkQueue q;            //   声明一个队列结构体
    QDataType val;          //   用于临时存储数据

    //  1. 初始化
    InitQueue(&q);

    //  2. 入队测试
    EnQueue(&q, 10);
    EnQueue(&q, 20);
    EnQueue(&q, 30);
    PrintQueue(&q);

    //  3. 出队测试
    printf("\n--- 开始出队 ---\n");
    DeQueue(&q, &val);
    printf("出队的值是：%d\n", val);
    PrintQueue(&q);

    //  4. 获取队头
    if (!IsEmpty(&q)) {
        GetHead(&q, &val);
        printf("当前队头元素是: %d\n", val);
    }

    //  5. 再次入队
    printf("\n--- 再次入队 ---\n");
    EnQueue(&q, 48);
    PrintQueue(&q);

    //  6. 销毁
    printf("\n--- 销毁队列 ---\n");
    DestroyQueue(&q);
    PrintQueue(&q);  //  验证是否真的空了

    return 0;
}




































