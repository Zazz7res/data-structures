
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 任务节点结构
typedef struct TaskNode {
    int taskId;                  // 任务ID
    char taskName[50];           // 任务名称
    int executionTime;           // 执行时间（毫秒）
    int priority;                // 优先级
    struct TaskNode* next;       // 指向下一个任务
} TaskNode;

// 任务循环链表结构
typedef struct {
    TaskNode* current;           // 当前指向的任务
    int taskCount;               // 任务总数
} TaskScheduler;

// 创建新任务节点
TaskNode* createTask(int id, const char* name, int time, int priority) {
    TaskNode* newTask = (TaskNode*)malloc(sizeof(TaskNode));
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

// 添加任务到调度器（添加到循环链表尾部）
void addTask(TaskScheduler* scheduler, TaskNode* newTask) {
    if (newTask == NULL) return;
    
    if (scheduler->current == NULL) {
        // 第一个任务，自身指向自己形成循环
        scheduler->current = newTask;
        newTask->next = newTask;
    } else {
        // 找到当前节点的前一个节点（即尾节点）
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
        // 多个节点的情况
        if (prev == NULL) {
            // 要删除的是当前节点，需要找到前一个节点
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
    
    printf("正在执行任务: [ID: %d] %s\n", 
           currentTask->taskId, 
           currentTask->taskName);
    printf("  优先级: %d, 执行时间: %dms\n", 
           currentTask->priority, 
           currentTask->executionTime);
    
    // 模拟任务执行
    printf("  任务执行中");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        // 简单的延时模拟（实际中不要这样实现延时）
        for (int j = 0; j < 100000000; j++);
    }
    printf(" 完成！\n");
    
    // 移到下一个任务
    scheduler->current = scheduler->current->next;
}

// 显示所有任务（从当前任务开始）
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
        printf("│ %-3d │ %-18s │ %-11d │ %-8d │\n", 
               current->taskId, 
               current->taskName,
               current->executionTime,
               current->priority);
        
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
    } while (current != start);
    
    printf("└─────┴────────────────────┴─────────────┴──────────┘\n");
}

// 按优先级排序任务（简单冒泡排序）
void sortTasksByPriority(TaskScheduler* scheduler) {
    if (scheduler->taskCount < 2) return;
    
    bool swapped;
    TaskNode *ptr1, *lptr = NULL;
    
    // 执行冒泡排序
    do {
        swapped = false;
        ptr1 = scheduler->current;
        
        do {
            TaskNode* next = ptr1->next;
            
            // 如果到达尾节点（尾节点的next是头节点）
            if (next == scheduler->current) break;
            
            // 比较优先级并交换节点数据（不改变链表结构，只交换数据）
            if (ptr1->priority < next->priority) {
                // 交换任务数据
                int tempId = ptr1->taskId;
                ptr1->taskId = next->taskId;
                next->taskId = tempId;
                
                char tempName[50];
                strcpy(tempName, ptr1->taskName);
                strcpy(ptr1->taskName, next->taskName);
                strcpy(next->taskName, tempName);
                
                int tempTime = ptr1->executionTime;
                ptr1->executionTime = next->executionTime;
                next->executionTime = tempTime;
                
                int tempPriority = ptr1->priority;
                ptr1->priority = next->priority;
                next->priority = tempPriority;
                
                swapped = true;
            }
            
            ptr1 = next;
        } while (ptr1->next != scheduler->current);
        
        lptr = ptr1;
    } while (swapped);
    
    printf("任务已按优先级排序！\n");
}

// 查找任务
TaskNode* findTask(TaskScheduler* scheduler, int taskId) {
    if (scheduler->current == NULL) return NULL;
    
    TaskNode* current = scheduler->current;
    
    do {
        if (current->taskId == taskId) {
            return current;
        }
        current = current->next;
    } while (current != scheduler->current);
    
    return NULL;  // 未找到
}

// 清空调度器
void clearScheduler(TaskScheduler* scheduler) {
    if (scheduler->current == NULL) return;
    
    TaskNode* current = scheduler->current;
    TaskNode* next;
    
    do {
        next = current->next;
        printf("释放任务: [%d] %s\n", current->taskId, current->taskName);
        free(current);
        current = next;
    } while (current != scheduler->current);
    
    scheduler->current = NULL;
    scheduler->taskCount = 0;
    printf("调度器已清空！\n");
}

// 示例演示函数
void demonstrateScheduler() {
    printf("=== 循环链表：轮询调度任务管理器演示 ===\n\n");
    
    TaskScheduler scheduler;
    initScheduler(&scheduler);
    
    // 1. 添加一些任务
    printf("1. 添加任务到调度器：\n");
    addTask(&scheduler, createTask(1, "数据备份", 500, 2));
    addTask(&scheduler, createTask(2, "日志清理", 200, 3));
    addTask(&scheduler, createTask(3, "系统监控", 100, 1));
    addTask(&scheduler, createTask(4, "用户请求处理", 300, 1));
    addTask(&scheduler, createTask(5, "磁盘整理", 800, 2));
    
    printf("\n");
    
    // 2. 显示所有任务
    displayAllTasks(&scheduler);
    
    // 3. 执行几轮任务
    printf("\n2. 执行三轮任务调度：\n");
    for (int round = 1; round <= 3; round++) {
        printf("\n--- 第 %d 轮调度 ---\n", round);
        for (int i = 0; i < scheduler.taskCount; i++) {
            executeCurrentTask(&scheduler);
        }
    }
    
    printf("\n");
    
    // 4. 按优先级排序并显示
    printf("3. 按优先级排序任务：\n");
    sortTasksByPriority(&scheduler);
    displayAllTasks(&scheduler);
    
    // 5. 查找任务
    printf("\n4. 查找任务ID 3：\n");
    TaskNode* foundTask = findTask(&scheduler, 3);
    if (foundTask != NULL) {
        printf("找到任务: [%d] %s, 优先级: %d\n", 
               foundTask->taskId, foundTask->taskName, foundTask->priority);
    }
    
    // 6. 移除一个任务
    printf("\n5. 移除任务ID 2：\n");
    removeTask(&scheduler, 2);
    displayAllTasks(&scheduler);
    
    // 7. 再执行一轮任务
    printf("\n6. 再执行一轮调度：\n");
    for (int i = 0; i < scheduler.taskCount; i++) {
        executeCurrentTask(&scheduler);
    }
    
    // 8. 清空调度器
    printf("\n7. 清空调度器：\n");
    clearScheduler(&scheduler);
    
    printf("\n=== 演示结束 ===\n");
}

// 主函数
int main() {
    demonstrateScheduler();
    return 0;
}
