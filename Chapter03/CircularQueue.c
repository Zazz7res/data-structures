#include <stdio.h>
#include <stdlib.h>

// ==========================================
// 1. 定义结构
// ==========================================

#define MAX_SIZE 5 // 设定传送带最多能放 5 盘 (实际只能存 4 盘，因为要牺牲一个空间)

typedef struct {
    int data[MAX_SIZE]; // 存放寿司ID的数组
    int front;          // 队头指针 (指向第一个元素)
    int rear;           // 队尾指针 (指向最后一个元素的下一个位置)
} SqQueue;

// ==========================================
// 2. 核心操作函数
// ==========================================

// 初始化
void InitQueue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
}

// 判空
int QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

// 判满
int QueueFull(SqQueue Q) {
    // 核心逻辑：如果 rear 的下一个位置是 front，就是满了
    return (Q.rear + 1) % MAX_SIZE == Q.front;
}

// 入队
void EnQueue(SqQueue *Q, int e) {
    // 1. 先判满
    if (QueueFull(*Q)) {
        printf(">> [厨师]: 传送带满了！稍等一下，不能放 %d 号寿司\n", e);
        return;
    }
    
    // 2. 数据入队
    Q->data[Q->rear] = e;
    
    // 3. rear 指针后移 (取模实现循环)
    printf(">> [厨师]: 上菜 %d 号寿司 (位置: %d)\n", e, Q->rear);
    Q->rear = (Q->rear + 1) % MAX_SIZE;
}

// 出队
void DeQueue(SqQueue *Q, int *e) {
    // 1. 先判空
    if (QueueEmpty(*Q)) {
        printf(">> [顾客]: 传送带空了，没吃的！\n");
        return;
    }
    
    // 2. 取出数据
    *e = Q->data[Q->front];
    
    // 3. front 指针后移
    printf(">> [顾客]: 取走了 %d 号寿司 (位置: %d)\n", *e, Q->front);
    Q->front = (Q->front + 1) % MAX_SIZE;
}

// 打印队列状态 (从 front 遍历到 rear)
void PrintQueue(SqQueue Q) {
    if (QueueEmpty(Q)) {
        printf("   [传送带状态]: 空空如也\n");
        return;
    }
    
    printf("   [传送带状态]: ");
    int i = Q.front;
    while (i != Q.rear) {
        printf("%d ", Q.data[i]);
        i = (i + 1) % MAX_SIZE; // 必须用取模循环查找
    }
    printf("\n");
}

// ==========================================
// 3. 主程序 (模拟回转寿司)
// ==========================================

int main() {
    SqQueue belt;
    InitQueue(&belt);
    int sushiId;

    printf("--- 模拟回转寿司 (容量5，实装4) ---\n\n");

    // 1. 厨师疯狂做菜 (入队) - 填满队列
    printf(">>> 厨师动作: 连续做 4 盘寿司\n");
    EnQueue(&belt, 101);
    EnQueue(&belt, 102);
    EnQueue(&belt, 103);
    EnQueue(&belt, 104);
    
    // 此时应该满了
    PrintQueue(belt);
    
    printf("\n>>> 厨师想再做一盘: \n");
    EnQueue(&belt, 105); // 应该提示满了
    
    printf("\n");

    // 2. 顾客吃掉两盘 (出队)
    printf(">>> 顾客动作: 取走 2 盘\n");
    DeQueue(&belt, &sushiId); // 拿走 101
    DeQueue(&belt, &sushiId); // 拿走 102
    PrintQueue(belt); 
    // 注意：此时传送带前段空了， rear 在 4 (或绕回去)，front 在 2
    
    printf("\n");

    // 3. 厨师再做新菜 (关键测试：循环利用空间)
    // 这里就是循环队列的精髓：前面空了，数据可以绕回来存
    printf(">>> 厨师动作: 再做 2 盘新寿司 (测试循环)\n");
    EnQueue(&belt, 105); // 应该能存入 (绕到下标 0 或 1)
    EnQueue(&belt, 106); 
    PrintQueue(belt); // 看看顺序是不是对的

    printf("\n");

    // 4. 清空测试
    printf(">>> 顾客动作: 全部吃光\n");
    while (!QueueEmpty(belt)) {
        DeQueue(&belt, &sushiId);
    }
    PrintQueue(belt);

    return 0;
}
