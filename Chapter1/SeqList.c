#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000  // 顺序表的最大容量
#define BOOK_NAME_LEN 50
#define AUTHOR_NAME_LEN 30

// 定义图书信息结构体
typedef struct 
{
    int id;                             // 图书ID
    char name[BOOK_NAME_LEN];           // 图书名称 
    char author[AUTHOR_NAME_LEN];       // 作者
    int year;      // 出版年份  // 修正：中文分号改为英文分号
} Book;  // 修正：BOOK改为Book，保持一致性

// 定义顺序表结构体
typedef struct
{
    Book books[MAX_SIZE];   // 存储图书的数组
    int length;             // 当前顺序表的长度（实际元素个数）
} SeqList;  // 修正：添加分号

// 1. 初始化顺序表
void InitList(SeqList *list) 
{
    /*
       功能：初始化顺序表
       参数：list -- 指向顺序表的指针
       说明：将顺序表的长度设置为0,表示表为空
    */
    list->length = 0;
    printf("顺序表初始化成功！当前表长为：%d\n", list->length);
}

// 2. 创建顺序表（添加一些初始化数据）
void CreateList(SeqList *list)  // 修正：参数名List改为list（小写）
{
    /* 功能：创建并初始化一个有示例数据的顺序表
       参数：list -- 指向顺序表的指针
    */ 

    // 检查顺序表是否已满
    if (list->length >= MAX_SIZE)
    {
        printf("顺序表已满，无法添加新数据！\n");
        return;
    }

    // 预定义一些图书数据
    Book initialBooks[] = {
        {1001, "C程序设计语言", "Dennis Ritchie", 1978},  // 修正：1078改为1978
        {1002, "数据结构与算法分析", "Mark Allen Weiss", 1997},  // 修正：去掉Esc
        {1003, "计算机程序的构造和解释", "Harold Abelson", 1985},  // 修正：Adelson改为Abelson
        {1004, "算法导论", "Thomas H. Cormen", 1990},
        {1005, "深入理解计算机系统", "Randal E. Bryant", 2003}  // 修正：修正书名和作者
    };

    int initialCount = sizeof(initialBooks) / sizeof(Book);

    // 将初始数据复制到顺序表中
    for (int i = 0; i < initialCount; i++)
    {
        list->books[list->length] = initialBooks[i];
        list->length++;
    }

    printf("顺序表创建成功！添加了 %d 本初始图书。\n", initialCount);
}

// 3. 取值操作：根据位置获取元素
int GetBook(SeqList *list, int position, Book *book)
{
    /*
        功能：获取指定位置的图书信息
        参数：
            list -- 指向顺序表的指针
            position -- 要获取的位置（从1开始）
            book -- 用于存储获取到的图书信息的指针
            返回值：成功返回1,失败返回0
    */ 
    
    // 检查位置是否合法（位置从1开始，到length结束）
    if (position < 1 || position > list->length)
    {
        printf("错误：位置 %d 不合法！有效范围是 1 到 %d\n", position, list->length);  // 修正：错误信息
        return 0;
    }
    

    // 顺序表的特点：可以直接通过下标访问，时间复杂度O(1)
    *book = list->books[position - 1];  // 修正：book改为books，positon改为position

    printf("成功获取第 %d 位置的图书：%s\n", position, book->name);
    return 1;
}

// 4. 查找操作：根据图书ID查找位置
int FindByID(SeqList *list, int id)  // 修正：函数名FinByID改为FindByID
{
    /* 
        功能：根据图书ID查找其在顺序表中的位置
        参数：list -- 指向顺序表的指针，id -- 要查找的图书 ID
        返回值：找到返回位置（从1开始），未找到返回-1 
    */

    // 顺序查找：从第一个元素开始逐个比较
    for (int i = 0; i < list->length; i++) {
        if (list->books[i].id == id)  // 修正：添加比较条件 == id
        {
            printf("找到图书ID %d, 位于位置 %d\n", id, i + 1);
            return i + 1;
        }
    }
    printf("未找到ID为 %d 的图书\n", id);
    return -1;
}

// 5. 查找操作：根据图书名称查找位置
int FindByName(SeqList *list, const char *name)
{
    /*
       功能：根据图书名称查找位置
       参数: list -- 指向顺序表的指针，name -- 查找的图书名称
       返回值: 找到返回位置（从1开始），未找到返回-1
    */

    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->books[i].name, name) == 0)
        {
            printf("找到图书《%s》，位于位置 %d\n", name, i + 1);
            return i + 1;
        }
    }
    printf("未找到图书 《%s》\n", name);
    return -1;
}

// 6. 插入操作: 在指定位置插入新元素
int InsertBook(SeqList *list, int position, Book newBook)
{
    /*
     * 功能：指定位置插入新元素
     * 参数：
     * list -- 指向顺序表的指针
     * position -- 要插入的位置（从1开始）
     * newBook -- 要插入的新图书
    返回值：成功返回1,失败返回0
    */

    // 检查顺序表是否已满
    if (list->length >= MAX_SIZE) {  // 修正：添加表满检查
        printf("错误：顺序表已满，无法插入新元素！\n");
        return 0;
    }

    // 检查插入位置是否合法
    if (position < 1 || position > list->length + 1) {
        printf("错误：插入位置 %d 不合法！有效范围是 1 到 %d\n", position, list->length + 1);
        return 0;
    }

    // 顺序表插入的核心步骤：将插入位置及之后的元素都向后移动一位
    // 注意：要从最后一个元素开始向后移动，避免覆盖数据
    for (int i = list->length - 1; i >= position - 1; i--) {
        list->books[i + 1] = list->books[i];
    }

    // 在空出的位置插入新元素
    list->books[position - 1] = newBook;

    // 表长加1
    list->length++;

    printf("成功在位置 %d 插入新图书:《%s》\n", position, newBook.name);
    return 1;
}

// 7.删除操作：删除指定位置的元素
int DeleteBook(SeqList *list, int position) {
    /*
     * 功能：删除指定位置的图书
     * 参数：list -- 指定顺序表的指针，position -- 要删除的位置（从1开始）
     * 返回值：成功返回1,失败返回0
     */ 

    // 检查顺序表是否为空
    if (list->length == 0) {
        printf("错误：顺序表为空，无法删除元素！\n");
        return 0;
    }  // 修正：添加缺少的括号

    // 检查删除位置是否合法
    if (position < 1 || position > list->length) {
        printf("错误：删除位置 %d 不合法！有效范围是 1 到 %d\n", position, list->length);
        return 0;
    }

    // 保存被删除的图书信息用于显示
    Book deletedBook = list->books[position - 1];  // 修正：deleteBook改为deletedBook

    // 顺序表删除的核心步骤：将删除位置之后的元素都向前移动一位
    // 注意：要从删除位置的下一个元素开始向前移动
    for (int i = position; i < list->length; i++) {
        list->books[i - 1] = list->books[i];
    }

    list->length--;
    
    printf("成功删除位置 %d 的图书：《%s》\n", position, deletedBook.name);
    return 1;  // 修正：reaturn改为return
}

// 8.遍历输出顺序表
void DisplayList(SeqList *list) {
    /* 
     * 功能：遍历并显示顺序表的所有图书信息
     * 参数：list -- 指向顺序表的指针
     */ 
    if (list->length == 0) {
        printf("顺序表为空！\n");
        return;
    }

    printf("\n===== 图书馆藏书列表（共%d本） =====\n",list->length);
    printf("%-4s  %-6s  %-30s  %-20s  %s\n", "序号", "ID", "书名", "作者", "出版年份");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < list->length; i++) {
        printf("%-4d  %-6d  %-30s  %-20s  %d\n",  // 修正：添加%号，去掉分号改为逗号
                i + 1,
                list->books[i].id,
                list->books[i].name,
                list->books[i].author,
                list->books[i].year);  // 修正：分号改为逗号
    }
    printf("=======================================================================\n\n");
}

// 9. 获取顺序表长度
int GetLength(SeqList *list) {  // 修正：函数名Getlength改为GetLength
    /*
     * 功能：获取顺序表的当前长度
     * 参数：list -- 指向顺序表的指针
     * 返回值：顺序表的长度
     */ 
    return list->length;  // 修正：返回长度，不是判断是否为空
}

// 10.判断顺序表是否为空
int IsEmpty(SeqList *list) {
    /*
     * 功能：判断顺序表是否为空
     * 参数：list -- 指向顺序表的指针
     * 返回值：为空返回1,不为空返回0
     */
    return list->length == 0;
}

// 演示函数：展示所有操作
void Demo() {
    printf("========== 顺序表操作演示 - 图书馆管理系统 ==========\n\n");

    SeqList library;  // 声明一个顺序表
    Book tempBook;    // 修正：添加缺少的分号

    // 1.初始化顺序表
    InitList(&library);
    printf("\n");

    // 2.创建带有初始化数据的顺序表
    CreateList(&library);
    DisplayList(&library);

    // 3.取值操作演示
    printf("3. 取值操作演示: \n");
    GetBook(&library, 2, &tempBook);  // 获取第2位置的图书
    printf("\n");

    // 4.查找操作演示
    printf("4. 查找操作演示：\n");
    FindByID(&library, 1003);
    FindByName(&library, "算法导论");
    printf("\n");

    // 5.插入操作演示
    printf("5.插入操作演示：\n");
    Book newBook = { 1006, "代码大全", "Steve McConnell", 1993 };
    InsertBook(&library, 3, newBook);
    DisplayList(&library);

    // 6.删除操作演示
    printf("6.删除操作演示: \n");
    DeleteBook(&library, 4);
    DisplayList(&library);

    // 7.其他操作演示
    printf("7.其他操作演示\n");
    printf("当前顺序表长度：%d\n", GetLength(&library));
    printf("顺序表是否为空: %s\n", IsEmpty(&library) ? "是" : "否");
}

int main() {
    // 运行演示程序
    Demo();
    return 0;
}
