#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  =========================================
//  1. 定义数据结构（书和书架）
//  =========================================

//  定义“书”这个数据类型
typedef struct {
    int id;                 //  书号（唯一标识）
    char name[50];          //  书名
    char author[20];        //  作者
    float price;            //  价格
} Book;

//  定义“顺序表”（即书架）
typedef struct {
    Book *data;             //  指向动态数组的指针（存放书的地方）
    int length;             //  当前书架上有多少本书
    int capacity            //  书架最大能放多少本书
} SqList; //  Sequence List

//  ==========================================
//  2. 基础操作函数（接口实现）
//  ==========================================

//  初始化书架
void InitList(SqList *L) {
    L->data = (Book *)malloc(sizeof(Book) * 4);     //  初始给 4 个位置
    if (L->data == NULL) {
        printf("内存分配失败！\n");
        exit(-1);
    }
    L->length = 0;
    L->capacity = 4;
    printf(">> 书架初始化完成，初始容量：%d\n", L->capacity);
}

//  判空
int IsEmpty(SqList L) {
    return L.length == 0;
}

//  获取当前长度
int GetLength(SqList L) {
    return L.length;
}

//  增容：如果书架满了，换个更大的
void CheckCapacity(SqList *L) {
    if (L->length >= L->capacity) {
        int newCap = L->capacity * 2;
        Book *newSpace = (Book *)realloc(L->data, sizeof(Book) * newCap);
        if (newSpace == NULL) {
            printf("增容失败！\n");
            return ;
        }
        L->data = newSpace;
        L->capacity = newCap;
        printf(">> 书架已扩容，当前容量：%d\n", L->capacity);
    }
}

//  新书入库（尾插法：新书放在最后）
void AddBook(SqList *L, Book b) {
    CheckCapacity(L);  //  先看有没有地方放
    L->data[L->capacity] = b;  //放入数据
    L->length++;
    printf(">> 入库成功：《%s》\n", b.name);
}

//  打印书架上的所有书（遍历）
void PrintList(SqList L) {
    printf("\n========== 当前馆藏列表 ==============\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "书名", "作者", "价格");
    printf("--------------------------------------\n");
    if (L.length == 0) {
      printf("（空空如也）\n");  
    } else {
        for (int i = 0; i < L.length; i++) {
            printf("%-5d %-20s %-10s %-10.2f\n",
                    L.data[i].id,
                    L.data[i].name,
                    L.data[i].author,
                    L.data[i].price);
        }
    }
    printf("=========================================\n\n");
}

//  按ID查找书
int FindBookById(SqList L, int id) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i].id == id) {
            return i;  //  找到了，返回数组下标
        }
    }
    return -1;  //  没找到
}

//  修改书籍信息
void UpdateBook(SqList *L, int id, float newPrice) {
    int index = FindBookById(*L, id);
    if (index == -1) {
        printf(">> 错误：找不到ID 为 %d 的书\n", id);
        return ;
    }
    L-data[index].price = newPrice;
    printf(">> 修改成功: 《%s》价格已经更新为 %.2f\n", L->data[index].name, newPrice);
}

//  下架书籍（按ID删除）
void RemoveBook(SqList *L, int id) {
    int index = FindBookById(*L , id);
    if (index == -1) {
        printf(">>错误：找不到 ID 为 %d 的书，无法删除\n", id);
        return ;
    }

    //  核心逻辑：从删除位置开始，后面所有的书都往前挪一格
    for (int i = index; i < L->length - 1; i++) {
        L->data[i] = L-data[i + 1];
    }

    L->length--;  //总数减1 
    printf(">> 下架成功：ID %d 已删除\n", id);
}

//  销毁书架（释放内存）
void DestroyList(SqList *L) {
    free(L-data);
    L->data = NULL;
    L->length = 0;
    L->capacity = 0;
    printf(">> 书架已销毁，内存已释放。\n");
}

// ================================================
// 3. 主程序（模拟图书馆的一天）
// ================================================


int main(void) {
    // 1. 开一家图书馆
    SqList library;
    InitList(&library);

    // 2. 准备一些新书数据
    Book b1 = {101, "C语言程序设计", "谭浩强", 45.00};
    Book b1 = {102, "数据结构", "严蔚敏", 55.50};
    Book b1 = {103, "红楼梦", "曹雪芹", 89.00};
    Book b1 = {104, "三体", "刘慈欣", 93.00};

    // 3. 新书入库（测试插入和自动扩容）
    printf("\n--- 正在入库 ---"\n);
    AddBook(&library, b1);
    AddBook(&library, b2);
    AddBook(&library, b3);
    AddBook(&library, b4);  //      
}

