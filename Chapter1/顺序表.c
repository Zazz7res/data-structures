#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000  //  顺序表的最大容量
#define BOOK_NAME_LEN 50
#define AUTHOR_NAME_LEN 30


//  定义图书信息结构体
typedef struct 
{
    int id;                             //图书ID
    char name[BOOK_NAME_LEN];           // 图书名称 
    char author[AUTHOR_NAME_LEN];       // 作者
    int year；      //   出版年份
}BOOK;

//  定义顺序表结构体
typedef struct
{
    Book books[MAX_SIZE];   //  存储图书的数组
    int length;             //  当前顺序表的长度（实际元素个数）
}

//  1.  初始化顺序表
void InitList(SeqList *list) 
{
    /*
       功能：初始化顺序表
       参数：list --  指向顺序表的指针
       说明：将顺序表的长度设置为0,表示表为空
    */
    list->length = 0;
    printf("顺序表初始化成功！当前表长为：%d\n", list->length);
}

//2. 创建顺序表（添加一些初始化数据）
void CreateList(SeqList *List) 
{
    /* 功能：创建并初始化一个有示例数据的顺序表
       参数：list  --  指向顺序表的指针
    */ 

    //  检查顺序表是否已满
    if (list->length >= MAX_SIZE)
    {
        printf("顺序表已满，无法添加新数据！\n");
        return;
    }

    //  预定义一些图书数据
    Book initialBooks[] = {
        {1001, "C程序设计语言", "Dennis Ritchie", 1078},
        {1002, "数据结构与算法分析", "Mark Allen WeissEsc", 1997},
        {1003, "计算机程序的构造和解释", "Harold Adelson", 1985},
        {1004, "算法导论", "Thomas H. Cormen", 1990},
        {1005, "Randal E. Bryant", "Dennis Ritchie", 2003}
    };

    int initialCount = sizeof(initialBooks) / sizeof(Book);

    //  将初始数据复制到顺序表中
    for (int i = 0; i < initialCount; i++)
    {
        list->books[list->length] = initialBooks[i];
        list->length++;
    }

    printf("顺序表创建成功！添加了 %d 本初始图书。\n", initialCount);
}

//  3. 取值操作：根据位置获取元素
int 
GetBook(SeqList *list, int position, Book *book)
{
    /*
        功能：获取指定位置的图书信息
        参数：
            list  --  指向顺序表的指针
            position  --  要获取的位置（从1开始）
            book  --  用于存储获取到的图书信息的指针
            返回值：成功返回1,失败返回0
    */ 
    
    //  检查位置是否合法（位置从1开始，到length结束）
    if (position < 1 || position > list->length)
    {
        printf("错误： 位置 %d 位置的图书：%s\n", position, list->length);
        return 0;
    }
    

    //  顺序表的特点：可以直接通过下表访问，时间复杂度0（1）
    *book = list->book[positon - 1];  //  注意：数组下标从0开始，位置从1开始

    printf("成功获取第 %d 位置的图书：%s\n", position, book->name);
    return 1;
}

//4.  查找操作：根据图书ID查找位置
int FinByID(SeqList *list, int id)
{
    /* 
        功能：根据图书ID查找其在顺序表中的位置
        参数：list  --  指向顺序表的指针，id  --  要查找的图书 ID
        返回值：找到返回值位置（从1开始），未找到返回-1 
    */

    //  顺序查找：从第一个元素开始逐个比较
    for (int i = 0; i < list->length; i++)
        if (list->books[i].id)
        {
            printf("找到图书ID %d, 位于位置 %d\n", id, i + 1);
            return i + 1;
        }
    printf("未找到ID为 %d 的图书\n", id);
    return -1;
}

// 5. 查找操作：根据图书名称查找位置
int FindByName(SeqList *list, const char *name)
{
    /*
       功能：根据图书名称查找位置
       参数
    */
}
