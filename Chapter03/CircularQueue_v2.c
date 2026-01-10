//  from z.ai   循环队列

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

// 定义队列的最大容量
#define MAX_SIZE 5


// 1. 定义队列中存储的“数据元素”结构体
typedef struct {
    int id;             // 学号
    char name[20];      // 姓名
} Student;

// 2. 定义“循环队列”控制结构体
typedef struct {
    Student data[MAX_SIZE]; // 数据域：存放Student结构体的数组
    int front;              // 队头指针：指向队首元素
    int rear;               // 队尾指针：指向队尾元素的下一个位置
} CircularQueue;


// 初始化队列
void initQueue(CircularQueue *q) {
    q->front = 0;
    q->rear = 0;
    // 注意：这里不需要对data数组进行memset，因为我们会通过front/rear控制访问
}

// 判断队列是否为空
int isEmpty(CircularQueue *q) {
    return q->front == q->rear;
}

// 判断队列是否已满
// 核心逻辑：(rear + 1) % MAX_SIZE == front 意味着rear即将追上front，此时队列满
int isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}


// 入队操作
int enQueue(CircularQueue *q, Student s) {
    if (isFull(q)) {
        printf("队列已满，无法入队！\n");
        return 0; // 入队失败
    }
    // 1. 将数据存入rear指向的位置
    q->data[q->rear] = s;
    // 2. rear指针后移，若到最后则回到0 (取模运算)
    q->rear = (q->rear + 1) % MAX_SIZE;
    return 1; // 入队成功
}

// 出队操作
int deQueue(CircularQueue *q, Student *s) {
    if (isEmpty(q)) {
        printf("队列为空，无法出队！\n");
        return 0; // 出队失败
    }
    // 1. 取出front指向的数据，通过指针s带回去
    *s = q->data[q->front];
    // 2. front指针后移，若到最后则回到0
    q->front = (q->front + 1) % MAX_SIZE;
    return 1; // 出队成功
}






// 获取队首元素（不出队）
int getHead(CircularQueue *q, Student *s) {
    if (isEmpty(q)) {
        printf("队列为空！\n");
        return 0;
    }
    *s = q->data[q->front];
    return 1;
}

// 遍历打印队列
void printQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("当前队列是空的。\n");
        return;
    }
    
    printf("队列元素: [");
    // 从front开始遍历，直到遇到rear
    int i = q->front;
    while (i != q->rear) {
        printf("{id:%d, name:%s}", q->data[i].id, q->data[i].name);
        i = (i + 1) % MAX_SIZE; // 指针循环后移
        
        // 如果还没到rear，打印个分隔符
        if (i != q->rear) {
            printf(" <- ");
        }
    }
    printf("]\n");
}

int main() {
    CircularQueue q;
    Student s;
    
    // 1. 初始化
    initQueue(&q);
    printf(">>> 队列初始化完成\n");

    // 2. 尝试入队4个元素
    for (int i = 1; i <= 4; i++) {
        s.id = i;
        sprintf(s.name, "同学%d", i); // 格式化生成名字
        if (enQueue(&q, s)) {
            printf("入队成功: %s\n", s.name);
        }
    }
    printQueue(&q); // 查看当前状态

    // 3. 测试满队
    printf("\n>>> 尝试入队第5个元素...\n");
    s.id = 5;
    strcpy(s.name, "同学5");
    enQueue(&q, s); // 应该会提示队列已满 (因为MAX_SIZE=5，实际可用4)
    
    // 4. 出队2个元素
    printf("\n>>> 执行2次出队操作...\n");
    for (int i = 0; i < 2; i++) {
        if (deQueue(&q, &s)) {
            printf("出队元素: %s\n", s.name);
        }
    }
    printQueue(&q); // 查看当前状态

    // 5. 再次入队（测试循环利用空间）
    printf("\n>>> 再次入队新元素 (测试循环)...\n");
    s.id = 6;
    strcpy(s.name, "新同学A");
    enQueue(&q, s);
    
    s.id = 7;
    strcpy(s.name, "新同学B");
    enQueue(&q, s);
    printQueue(&q);

    return 0;
}
