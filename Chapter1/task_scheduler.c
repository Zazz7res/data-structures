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

    } else {
        if (prev == NULL) {
            TaskNode* temp = current;
            while (temp->next != current) {
                temp = temp->next;
            }
            prev = temp;
        }

        prev->next = current->next;

        // 如果删除的是当前指向的节点，更新current
        if (current == scheduler->current) {
            scheduler->current = current->next;
        }
    }

    printf("任务 [%d] %s 已从调度器移除\n", current->taskId, current->taskName);
    free(current);
    scheduler->taskCount--;

    return true;
}

// 执行当前任务，并移到下一个任务
void executeCurrentTask(TaskScheduler* scheduler) {
    if (scheduler->current == NULL) {
        printf("调度器中无任务可执行！\n");
        return;
    }

    TaskNode* currentTask = scheduler->current;

    printf("正在执行任务：[ID: %d] %s\n", 
            currentTask-taskId,
            currentTask->taskName);
    printf("    优先级：%d, 执行时间：%dms\n",
            currentTask->priority,
            currentTask->executionTime);

    // 模拟任务执行
    printf("    任务执行中");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        // 简单的延时模拟（实际中不要这样实现延时）
        for (int j = 0; j < 100000000; j++) {
        } 
        printf("    完成！\n");

        // 移到下一个任务
        scheduler->current = scheduler->current->next;
    }

// 显示所有任务（从当前任务开始i）
void displayAllTasks(TaskScheduler* scheduler) {
    if (scheduler->current == NULL) {
        printf("调度器中无任务！\n");
        return;
    }

    printf("\n当前调度器中的任务（共%d个）:\n", scheduler->taskCount);
    printf("┌─────┬────────────────────┬─────────────┬──────────┐\n");
    printf("│ ID  │ 任务名称           │ 执行时间(ms)│ 优先级   │\n");
    printf("├─────┼────────────────────┼─────────────┼──────────┤\n");

    TaskNode* start = scheduler->current;
    TaskNode* current = start;
    int count = 0;

    do {
        printf("| %-3d | %-18s | %-11d | %-8d |\n",
                current->taskId,
                current->taskName,
                current->executionTime,
                current->priority;

            // 标记当前指向的任务
            if (current == start) {
                printf("│     ↑ 当前指向的任务                             │\n");
                
            }

            current = current->next;
            count++;

            // 防止无限循环（安全措施）
            if (count > scheduler->taskCount * 2) {
                printf("错误：检测到循环链表异常！\n");
                break;
            }
    }
}
}
