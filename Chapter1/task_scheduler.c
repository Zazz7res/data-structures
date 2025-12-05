/*
循环链表实例：轮询调度任务管理器
我来给你展示一个使用循环链表的实际例子：
轮询调度任务管理器（Round-Robin Task Scheduler）。

场景描述
在一个简单的任务调度系统中，多个任务需要按顺序轮询执行。
当一个任务执行完后，就轮到下一个任务，循环往复。
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 任务节点结构
typedef struct TaskNode {
    int taskId;                 // 任务ID 
    char taskName[50];          // 任务名称
    int executionTime;          // 执行时间（毫秒）
    int priority;               // 优先级
    struct TaskNode* next;      // 指向下一个任务
} TaskNode;

// 任务循环链表结构
typedef struct {
    TaskNode* current;          // 当前指向的任务
    int taskCount;              // 任务总数
} TaskScheduler;

// 创建新任务节点
TaskNode* createTask(int id, const char* name, int time, int priority) {
    if (newTask == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }

    newTask->taskId = id;
    strncpy(newTask->taskName, name, sizeof(newTask->taskName) - 1);
    newTask->taskName[sizeof(newTask->taskName) - 1] = '\0';
    newTask->executionTime = time;
    newTask->priority = priority;
    newTask->next = NULL;

    return newTask;
}

// 初始化任务调度器
void initScheduler(TaskScheduler* scheduler) {
    scheduler->current = NULL;
    scheduler->taskCount = 0;
}

// 添加任务到调度表（添加到循环链表尾部）
void addTask(TaskScheduler* scheduler, TaskNode* newTask) {
    if (newTask == NULL) return;

    if (scheduler->current == NULL) {
    // 第一跟任务，自身指向自己行程循环
        scheduler->current = newTask;
        newTask->next = newTask;
    } else {
        TaskNode* tail = scheduler->current;
        while (tail->next != scheduler->current) {
            tail = tail->next;
        }

        // 插入新节点
        tail->next = newTask;
        newTask->next = scheduler->current;
    }

    scheduler->taskCount++;
    printf("任务 [%d] %s 已添加到调度器\n", newTask->taskId, newTask->taskName);

}

// 移除指定ID的任务
bool removeTask(TaskScheduler* scheduler, int taskId) {
    if (scheduler->current == NULL) {
        printf("调度器中无任务！\n");
        return false;
    }

    TaskNode *current = scheduler->current;
    TaskNode *prev = NULL;

    // 查找要删除的节点
    do {
        if (current->taskId == taskId) {
            break;
        }

        prev = current;
        current = current->next;
    } while (current != scheduler->current);

    // 未找到该任务
    if (current->taskId != taskId) {
        printf("未找到任务ID: %d\n", taskId);
        return false;
    }

    // 删除节点
    if (current == current->next) {
        // 只有一个节点的情况
        scheduler->current = NULL;

    }
}
