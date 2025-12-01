/*  学习顺序表  */
/*  第一部分：头文件和宏定义  */ 
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100  // 顺序表的最大容量
#define BOOK_NAME_LEN 50
#define AUTHOR_NAME_LEN 30

/*  第二部分：数据元素类型定义  */ 
//  定义图书信息结构体
typedef struct {
    int id;         //  图书ID 
    char name[BOOK_NAME_LEN];       //  图书名称
    char author[AUTHOR_NAME_LEN];   //  作者
    int year;       //  出版年份
}Book;
/*解读：
typedef struct { ... } Book; 创建了一个新的数据类型 Book
这个结构体定义了顺序表中每个数据元素的构成：
id: 整型，图书的唯一标识
name: 字符数组，存储图书名称
author: 字符数组，存储作者姓名
year: 整型，出版年份
这相当于定义了"一本书"的模板
*/ 

/*  第三部分：顺序表类型定义  */ 
//  定义顺序表结构
typedef struct {
    Book books[MAX_SIZE];  //  存储图书的数组
    int length;           //  当前顺序表的长度（实际元素个数）
} SeqList;
/*  
解读：
这是顺序表的类型定义，创建了数据类型 SeqList
结构体包含两个成员：
Book books[MAX_SIZE]: 数组，用于实际存储数据元素
大小是 MAX_SIZE (100)
这是顺序表的核心存储结构
int length: 长度指示器
记录当前表中实际有多少个有效元素
注意：length ≤ MAX_SIZE
*/ 
/*  第四部分：初始化函数  */ 
// 1.初始化顺序表
void InitList(SeqList *list) {
    /* 
     * 功能：初始化顺序表
     * 参数：list - 指向顺序表的指针
     * 说明：将顺序表的长度设置为0,表示为空
     */ 
    list->length = 0;
    printf("顺序表初始化成功！当前表长为 %d\n", list->length);
    
}
/*
 解读：
函数名：InitList - 初始化列表
参数：SeqList *list - 指向顺序表的指针
功能：将顺序表的长度设为0，表示空表
关键操作：list->length = 0;
-> 是指针访问结构体成员的运算符
等价于 (*list).length = 0;
*/ 


/*
 为什么用指针？
使用指针的原因：
SeqList library;        // 声明一个顺序表
InitList(&library);     // 传递地址，函数内可以修改library

如果不用指针：
void InitList(SeqList list) { ... }  // 参数是副本，修改无效
*/ 
/*  第五部分：创建顺序表（带初始数据） */ 
// 2.创建顺序表（添加一些初始化数据）
void CreateList(SeqList *list) {
    /*
     * 功能：创建并初始化一个有示例的顺序表
     * 参数：list - 指向顺序表的指针
     */ 
    /*  1. 容量检查  */
    /*  确保不会超过数组边界
        这是健壮性编程的重要习惯
    */ 
    //检查顺序表是否已满
    if (list->length >= MAX_SIZE) {
        printf("顺序表已满,无法添加新数据！\n");
        return;
    }

    // 预定义一些图书数据
    Book initialBooks[] = {
        { 1001, "C程序设计语言", "Dennis Ritchie", 1978 },
        { 1002, "数据结构与算法分析", "Mark Allen weiss", 1997 },
        { 1003, "计算机程序的构造和解释", "Harold Abelson", 1985 },
        { 1004, "算法导论", "Thomas H. Cormen", 1990 },
        { 1005, "深入理解计算机系统", "Randal E. Bryant", 2003 },
    };
    /*  计算元素个数  */ 
    int initialCount = sizeof(initialBooks) / sizeof(Book);
    /*  
        sizeof(initialBooks)：整个数组的字节数
        sizeof(Book)：一个Book结构体的字节数
        相除得到：数组中有多少个元素
        这是C语言中计算数组长度的常用技巧
    */ 

    // 将初始化数据复制到顺序表中
    for (int i = 0; i < initialCount; i++) {
        list->boos[list->length] = initialBooks[i];
        list->length++;
    }
    /*  关键逻辑：
        list->books[list->length]：总是往当前有效数据的下一个位置存放
        放一个元素，length就加1
        这样保证数据是连续存储的
    */ 

    printf("顺序表创建成功！添加了 %d 本初始化图书。\n", initialCount);
}
 
/*   第三个函数：GetBook（按位置取值） */ 
// 3.取值操作：根据位置获取元素
int GetBook(SeqList *list, int position, Book *book) {
    /*
     * 功能：获取指定位置的图书信息
     * 参数：
     *      list - 指向顺序表的指针
     *      position - 要获取的位置（从1开始）
     *      book - 用于存储获取到的图书信息的指针
     *  返回值：成功返回1,失败返回0
     
     
     *  list: 指向顺序表的指针，我们需要从这个表中获取数据
        position: 要获取的位置，注意这里从1开始计数（符合人类习惯）
        book: 指向Book结构体的指针，用于存储获取到的图书信息
        返回值: int类型，成功返回1，失败返回0
     *
     */ 

    // 检查位置是否合法（位置从1开始，到length结束）
    if (position < 1 || position  > list->length) {
        printf("错误：位置 %d 不合法！有效范围是1 到 %d\n", position, list->length);
        return 0;
    }

    /*  
     *2. 位置合法性检查
        为什么需要检查？ 防止访问不存在的内存位置（数组越界）
        有效范围：1 到 list->length
        示例：如果表中有5本书，有效位置就是1、2、3、4、5
        位置0或位置6都是非法的
     */ 

    //顺序表的特点：可以直接通过下标访问，时间复杂度O(1)
    *book = list->books[position - 1];  //注意：数组下标从0开始，位置从1开始
   /*  
    *3. 核心操作：随机存取
        这是顺序表最核心的优势：随机存取
        时间复杂度：O(1) - 常数时间
        下标转换：position - 1
        用户输入的位置从1开始（第1本、第2本...）
        数组下标从0开始（books[0]、books[1]...）
        所以需要减1转换


        4. 重要概念：随机存取 vs 顺序存取
            随机存取（顺序表的优势）：
            - 可以直接跳到任意位置
            - 不需要从头开始遍历
            - 时间复杂度：O(1)
            顺序存取（链表的缺点）：
            - 必须从头开始，一个一个往后找
            - 时间复杂度：O(n)
    */ 
    printf("成功获取第 %d 位置的图书：%s\n", position, book->name);
    return 1;
}

//   第四、第五个函数：查找操作

// 4.查找操作：根据图书ID查找位置
int FindByID(SeqList *list, int id) {
    /* 
     * 功能：根据图书ID查找其在顺序表中的位置
     * 参数：list - 指向顺序表的指针， id - 要查找的图书ID
     * 返回值：找到返回位置（从1开始），未找到返回-1
     *
     *
     *🔍 详细解读：
        查找方式：顺序查找（线性查找）
        从第一个元素开始，逐个比较
        时间复杂度：O(n)
        这是顺序表在查找方面的缺点
     */ 

    //  顺序查找：从第一个元素开始逐个比较
    for (int i = 0; i < list->length; i++) {
        if (list->boos[i].id == id) {
            printf("找到图书ID %d, 位于位置 %d\n", id, i + 1);
            return i + 1;
        }
    }


    printf("未找到ID为 %d 的图书\n", id);
    return -1;

        /*
            返回值处理：
            找到：返回位置（从1开始计数）
            未找到：返回-1（特殊值表示未找到）
            位置转换：
            数组下标 i 是从0开始的
            返回给用户的应该是从1开始的位置：i + 1
        */ 
}


// 5.查找操作：根据图书名称查找位置
int FindByName(SeqList *list, const char *name) {
    /*
     * 功能：根据图书名称查找其在顺序表中的位置
     * 参数：list - 指向顺序表的指针，name - 要查找的图书名称
     * 返回值：找到返回位置（从1开始），未找到返回-1 
     */ 
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->books[i].name, name) == 0) {
            printf("找到图书《%s》，位于位置 %d\n", name, i + 1);
            return i + 1;
        }
            //strcmp()是C标准库函数，用于比较两个字符串
            //返回0表示两个字符串完全相同
    }

    printf("未找到图书《%s》\n", name);
    return -1;
}
    /* 
    查找算法相同，比较内容不同：
    FindByID: 比较整数 id
    FindByName: 比较字符串 name
    都是顺序查找，时间复杂度O(n)
    */ 

// 6.插入操作：在指定位置插入新元素
int InsertBook(SeqList *list, int position, Book newBook) {
    /*
     * 功能：在指定位置插入新图书
     * 参数：
     *      list - 指向顺序表的指针
     *      position - 要插入的位置（从1开始）
     *      newBook - 要插入的新图书
     *  返回值：成功返回1,失败返回0
     */ 

    // 检查顺序表是否已满
    if (list->length >= MAX_SIZE) {
        printf("错误：顺序表已满，无法插入新数据！\n");
        return 0;
    }

    // 检查插入位置是否合法
    if (position < 1 || position > list->length + 1) {
        printf("错误：插入位置 %d 不合法！有效范围是 1 到 %d\n", position, list->length + 1)
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

    printf("成功在位置 %d 插入新图书：《%s》\n", position, newBook.name);
    return 1;
} 

// 7.删除操作：删除指定位置的元素
int DeleteBook(SeqList *list, int position) {
    /*
     * 功能：删除指定位置的图书
     * 参数：list - 指向顺序表的指针，position - 要删除的位置（从1开始）
     * 返回值：成功返回1,失败返回0
     */ 

    // 检查顺序表是否为空
    if (list->length == 0) {
        printf("错误：顺序表为空，无法删除元素！\n");
        return 0;
    }

    //检查位置是否合法
    if (position < 1 || position > list->length) {
        printf(" 错误：删除位置 %d 不合法！有效范围是 1 到 %d\n", position, list->length);
        return 0;
    }

    //保存被删除的图书信息用于显示
    Book DeleteBook = list->books[position - 1];

    //顺序表删除的核心步骤：将删除位置
}
