#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =======================================
// 1. 定义数据类型：书和书架节点
// =======================================

// 书的结构（这就是盒子里的"货物"）
typedef struct {
    int id;             // 书号
    char name[50];      // 书名
    char author[30];    // 作者
    float price;        // 价格
} Book;

// 书架节点的结构（这就是"盒子"）
typedef struct ShelfNode {
    Book data;              // 数据域：存放一本书
    struct ShelfNode *next; // 指针域：指向下一个盒子
} ShelfNode, *Bookshelf;    // 别名：ShelfNode是盒子，Bookshelf是指向盒子的指针

// =======================================
// 2. 书架操作函数
// =======================================

// 初始化一个空书架
Bookshelf InitBookshelf() {
    return NULL;  // 书架刚开始是空的
}

// 检查书架是否为空
bool IsEmpty(Bookshelf shelf) {
    return shelf == NULL;
}

// 添加书到书架开头（新来的放最前面）
void AddBookToFront(Bookshelf *shelf_ptr, Book book) {
    // 1. 造一个新盒子
    ShelfNode *new_box = (ShelfNode*)malloc(sizeof(ShelfNode));
    if (new_box == NULL) {
        printf("书架空间不足，无法添加新书！\n");
        return;
    }
    
    // 2. 把书放进盒子
    new_box->data = book;
    
    // 3. 连接盒子
    new_box->next = *shelf_ptr;  // 新盒子的挂钩挂上原来的第一本书
    *shelf_ptr = new_box;        // 书架指针指向新盒子
    
    printf(">> 《%s》已放在书架最前面\n", book.name);
}

// 添加书到书架末尾（新来的放最后面）
void AddBookToBack(Bookshelf *shelf_ptr, Book book) {
    // 1. 造一个新盒子
    ShelfNode *new_box = (ShelfNode*)malloc(sizeof(ShelfNode));
    if (new_box == NULL) {
        printf("书架空间不足，无法添加新书！\n");
        return;
    }
    new_box->data = book;
    new_box->next = NULL;  // 最后一个盒子后面没有盒子
    
    // 2. 如果书架是空的
    if (*shelf_ptr == NULL) {
        *shelf_ptr = new_box;
        printf(">> 《%s》已放在书架（第一本）\n", book.name);
        return;
    }
    
    // 3. 找到书架的最后一个盒子
    ShelfNode *current = *shelf_ptr;
    while (current->next != NULL) {
        current = current->next;  // 顺着挂钩一个个找
    }
    
    // 4. 把新盒子挂到最后
    current->next = new_box;
    printf(">> 《%s》已放在书架最后面\n", book.name);
}

// 在指定位置插入书（在第n个位置插入）
bool InsertBookAt(Bookshelf *shelf_ptr, Book book, int position) {
    if (position < 1) {
        printf("位置必须大于0！\n");
        return false;
    }
    
    // 情况1：插入到第一个位置
    if (position == 1) {
        AddBookToFront(shelf_ptr, book);
        return true;
    }
    
    // 造新盒子
    ShelfNode *new_box = (ShelfNode*)malloc(sizeof(ShelfNode));
    if (new_box == NULL) return false;
    new_box->data = book;
    
    // 找到插入位置的前一个盒子
    ShelfNode *current = *shelf_ptr;
    int count = 1;
    
    // 移动到position-1的位置
    while (current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    
    // 检查位置是否有效
    if (current == NULL) {
        printf("插入位置%d无效（书架只有%d本书）\n", position, count);
        free(new_box);
        return false;
    }
    
    // 插入新盒子
    new_box->next = current->next;  // 新盒子挂上后面的盒子
    current->next = new_box;        // 前一个盒子挂上新盒子
    
    printf(">> 《%s》已插入到第%d个位置\n", book.name, position);
    return true;
}

// 根据书号查找书
ShelfNode* FindBookById(Bookshelf shelf, int id) {
    ShelfNode *current = shelf;
    
    while (current != NULL) {
        // 比较书号
        if (current->data.id == id) {
            return current;  // 找到了！
        }
        current = current->next;
    }
    
    return NULL;  // 没找到
}

// 根据书名查找书
ShelfNode* FindBookByName(Bookshelf shelf, const char *name) {
    ShelfNode *current = shelf;
    
    while (current != NULL) {
        // 比较书名（忽略大小写）
        if (strcasecmp(current->data.name, name) == 0) {
            return current;  // 找到了！
        }
        current = current->next;
    }
    
    return NULL;  // 没找到
}

// 根据书号删除书
bool RemoveBookById(Bookshelf *shelf_ptr, int id) {
    if (*shelf_ptr == NULL) {
        printf("书架是空的！\n");
        return false;
    }
    
    ShelfNode *current = *shelf_ptr;
    ShelfNode *prev = NULL;  // 记录当前盒子的前一个盒子
    
    // 寻找要删除的盒子
    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }
    
    // 没找到
    if (current == NULL) {
        printf("没有找到书号为%d的书\n", id);
        return false;
    }
    
    // 找到了，开始删除
    if (prev == NULL) {
        // 情况1：删除的是第一个盒子
        *shelf_ptr = current->next;
    } else {
        // 情况2：删除的是中间或最后的盒子
        prev->next = current->next;
    }
    
    printf(">> 已下架：《%s》\n", current->data.name);
    free(current);  // 释放盒子占用的空间
    return true;
}

// 计算书架上有多少本书
int CountBooks(Bookshelf shelf) {
    int count = 0;
    ShelfNode *current = shelf;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

// 显示书架上的所有书
void DisplayBookshelf(Bookshelf shelf) {
    printf("\n════════════════════════════ 书架总览 ════════════════════════════\n");
    
    if (IsEmpty(shelf)) {
        printf("                   书架是空的，快去添置新书吧！\n");
    } else {
        printf("%-6s %-25s %-20s %-10s\n", "书号", "书名", "作者", "价格");
        printf("──────────────────────────────────────────────────────────────\n");
        
        ShelfNode *current = shelf;
        int position = 1;
        
        while (current != NULL) {
            printf("%-6d %-25s %-20s ￥%-9.2f\n",
                   current->data.id,
                   current->data.name,
                   current->data.author,
                   current->data.price);
            current = current->next;
            position++;
        }
        
        printf("──────────────────────────────────────────────────────────────\n");
        printf("共 %d 本书\n", CountBooks(shelf));
    }
    
    printf("══════════════════════════════════════════════════════════════════\n\n");
}

// 更新书的信息
bool UpdateBook(Bookshelf shelf, int id, float new_price, const char *new_author) {
    ShelfNode *book_node = FindBookById(shelf, id);
    
    if (book_node == NULL) {
        printf("没有找到书号为%d的书\n", id);
        return false;
    }
    
    // 更新信息
    book_node->data.price = new_price;
    if (new_author != NULL) {
        strncpy(book_node->data.author, new_author, sizeof(book_node->data.author) - 1);
        book_node->data.author[sizeof(book_node->data.author) - 1] = '\0';
    }
    
    printf(">> 《%s》信息已更新\n", book_node->data.name);
    return true;
}

// 清空书架（释放所有内存）
void ClearBookshelf(Bookshelf *shelf_ptr) {
    ShelfNode *current = *shelf_ptr;
    ShelfNode *next_box;
    
    while (current != NULL) {
        next_box = current->next;  // 先记住下一个盒子在哪
        free(current);             // 释放当前盒子
        current = next_box;        // 移动到下一个盒子
    }
    
    *shelf_ptr = NULL;  // 书架指针指向NULL
    printf(">> 书架已清空，所有书已下架\n");
}

// =======================================
// 3. 主程序：演示所有操作
// =======================================

int main() {
    printf("📚 欢迎使用图书管理系统（单链表版）📚\n");
    
    // 1. 初始化一个空书架
    Bookshelf my_shelf = InitBookshelf();
    printf("\n1. 初始化书架：%s\n", IsEmpty(my_shelf) ? "空的" : "有书");
    
    // 2. 准备一些书
    Book book1 = {1001, "C程序设计语言", "Brian Kernighan", 89.50};
    Book book2 = {1002, "数据结构与算法", "严蔚敏", 75.00};
    Book book3 = {1003, "深入理解计算机系统", "Randal Bryant", 128.00};
    Book book4 = {1004, "算法导论", "Thomas Cormen", 168.00};
    Book book5 = {1005, "现代操作系统", "Andrew Tanenbaum", 99.80};
    
    // 3. 测试：添加书到书架前面
    printf("\n2. 测试：头插法添加书\n");
    AddBookToFront(&my_shelf, book1);
    AddBookToFront(&my_shelf, book2);
    DisplayBookshelf(my_shelf);
    
    // 4. 测试：添加书到书架后面
    printf("\n3. 测试：尾插法添加书\n");
    AddBookToBack(&my_shelf, book3);
    AddBookToBack(&my_shelf, book4);
    DisplayBookshelf(my_shelf);
    
    // 5. 测试：在指定位置插入书
    printf("\n4. 测试：在指定位置插入书\n");
    InsertBookAt(&my_shelf, book5, 3);  // 在第3个位置插入
    DisplayBookshelf(my_shelf);
    
    // 6. 测试：查找书
    printf("\n5. 测试：查找书\n");
    ShelfNode *found = FindBookByName(my_shelf, "算法导论");
    if (found != NULL) {
        printf(">> 找到《%s》，作者：%s，价格：￥%.2f\n",
               found->data.name, found->data.author, found->data.price);
    }
    
    // 7. 测试：更新书的信息
    printf("\n6. 测试：更新书的信息\n");
    UpdateBook(my_shelf, 1004, 158.00, "Thomas H. Cormen");
    DisplayBookshelf(my_shelf);
    
    // 8. 测试：删除书
    printf("\n7. 测试：删除书\n");
    RemoveBookById(&my_shelf, 1002);  // 删除书号为1002的书
    DisplayBookshelf(my_shelf);
    
    // 9. 测试：计数
    printf("\n8. 书架统计\n");
    printf(">> 书架上共有 %d 本书\n", CountBooks(my_shelf));
    
    // 10. 清空书架
    printf("\n9. 清理书架\n");
    ClearBookshelf(&my_shelf);
    DisplayBookshelf(my_shelf);
    
    return 0;
}
