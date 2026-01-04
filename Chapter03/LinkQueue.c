#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
//  1. 定义结构
// ============================================

//  病人信息节点
typedef struct QNode {
    int id;             //  病人 ID （挂号单号）
    char name[20];      //  病人姓名
    struct QNode *next; //  指向下一个病人
} QNode;

//  链队结构
//  包含队头指针和队尾指针
typedef struct {
    QNode *front;  //  队头指针
    QNode *rear;   //  队尾指针
} LinkQueue;

// ===============================================
//  2. 核心操作函数
// ===============================================

//  初始化队列
void InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = NULL;  //  初始都为空
}

//  判空
int QueueEmpty(LinkQueue Q) {
    //  只要 front 是 NULL，就说明队空
    return Q.front == NULL; 
}

//  入队
void EnQueue(LinkQueue *Q, int id, char *name) {
    //  1. 创建新节点
    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    if (newNode == NULL) {
        printf("系统繁忙，无法挂号！\n");
        return ;
    }

    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->next = NULL;  //  新节点作为队尾，next 一定是 NULL

    //  2. 插入逻辑
    if (QueueEmpty(*Q)) {
        //  如果是空队，新节点既是队头也是队尾
        Q->front = Q->rear = newNode;
    } else {
        //  如果不为空，挂到 rear 后面
         Q->rear->next = newNode;
         Q->rear = newNode;  //  更新rear 指针
    }

    printf(">> [挂号]: %s（ID: %d) 排队成功\n", name, id);
}

//  出队
void DeQueue(LinkQueue *Q, int *id, char *name) {
    //  1. 判空
    if (QueueEmpty(*Q)) {
        printf(">> [叫号]: 当前没有病人在排队！\n");
        return ;
    }

    //  2. 暂存队头节点
    QNode *temp = Q->front;

    //  3. 取出数据
    *id = temp->id;
    strcpy(name, temp->name);

    //  4. 队头指针后移
    Q->front = temp->next;

    //  5. 释放节点
    free(temp);

    //  6. 关键一步：如果队头移除后变空了，必须把 rear 也置空
    //  否则 rear 会指向已经被释放的内存（野指针）
    if (Q->front == NULL) {
        Q->rear = NULL;
    }

    printf(">> [就诊]: 请 %d 号 %s 进诊室\n", *id, name);
}

//  查看队头（只看不叫号）
void GetHead(LinkQueue Q) {
    if (QueueEmpty(Q)) {
        printf("    [当前排队]: 无人\n");
        return ;
    }
    printf("    [下一位]: %d 号 %s\n", Q.front->id, Q.front->name);
}

//  打印队列状态
void printQueue(LinkQueue Q) {
    if (QueueEmpty(Q)) {
        printf("    [当前排队]: 无 \n");
        return;
    }

    printf("    [当前排队]: ");
    QNode *p = Q.front;
    while (p != NULL) {
        printf("%d-%s ", p->id, p->name);
        p = p->next;
    }
    printf("\n");
}

// =================================================
//  3. 主程序（模拟医院叫号系统）
// =================================================

int main(void) {
    LinkQueue hospitalQueue;
    InitQueue((&hospitalQueue));

    int pid;
    char pname[20];

    printf("--- 模拟医院挂号叫号系统（链队）---\n\n");

    //  1. 早上开门，一波病人来挂号
    printf(">>> 一批病人挂号：\n");
    EnQueue(&hospitalQueue, 1, "张三");
    EnQueue(&hospitalQueue, 2, "李四");
    EnQueue(&hospitalQueue, 3, "王五");

    printQueue(hospitalQueue);
    GetHead(hospitalQueue);  //  查看下一个是谁

    printf("\n>>> 医生开始看病（叫号 2次）：\n");
    DeQueue(&hospitalQueue, &pid, pname);  //  叫张三
    DeQueue(&hospitalQueue, &pid, pname);  //  叫李四

    printQueue(hospitalQueue);
    GetHead(hospitalQueue);  //  下一位应该是王五

    //  2. 中途又来了新病人
    printf("\n>>> 中途来个插队的...不对，来的一个挂号的：\n");
    EnQueue(&hospitalQueue, 4, "赵六");
    printQueue(hospitalQueue);

    //  3. 一直把号叫完，测试队空逻辑
    printf("\n>>> 医生加快速度，叫完剩余病人：\n");
    DeQueue(&hospitalQueue, &pid, pname);  //  王五
    DeQueue(&hospitalQueue, &pid, pname);  //  赵六

    printQueue(hospitalQueue);

     //  4. 测试队空后还能不能叫
    printf("\n>>> 再叫一次（测试空队):\n");
    DeQueue(&hospitalQueue, &pid, pname);

    return 0;
}
