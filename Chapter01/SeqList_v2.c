#include <stdio.h>
#include <stdlib.h>  // 包含 malloc 和 realloc 函数

//  --- 1. 定义结构体  ---
#define INIT_SIZE 5     // 顺序表的初始容量
#define INCREMENT_SIZE  3  // 当空间不够时，每次增加的容量

typedef struct {
    int *data;      // 指针，指向存放数据的动态数组
    int length;     // 当前顺序表的长度（即元素的个数）
    int capacity;   // 当前顺序表的总容量
} SeqList;

// --- 2. 函数声明 ---
void InitList(SeqList *L);                      // 初始化
void PrintList(SeqList L);                      // 打印
int ListInsert(SeqList *L, int i, int e);       // 插入元素（在第i个位置插入e)
int ListDelete(SeqList *L, int i, int *e);      // 删除元素（删除第i个位置，并用e返回值)
void DestroyList(SeqList *L);                   // 销毁顺序表，释放内存
void IncreaseCapacity(SeqList *L);              // 辅助函数：扩容

// --- 3. 主函数测试 ---
int main(void)
{
    SeqList L;
    int e; // 用于接收被删除的元素

    // 
}

// --- 4. 函数实现
