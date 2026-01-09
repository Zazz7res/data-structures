//  from z.ai  顺序栈
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>        //  使用 bool 类型需要包含这个头文件
#include <string.h>

// --- 宏定义 ---
#define MAX_SIZE 100        //  栈的最大容量

// =====================================
//  1. 结构体定义（体现嵌套）
// =====================================

//  定义一个日期结构体（子结构体）
typedef struct {
    int year;
    int month;
    int day;
} Date;

//  定义一个学生结构体（主结构体）
//  这里嵌套了 Date 结构体作为成员
typedef struct {
    int id;                 //  学号
    char name[50];          //  姓名
    Date birthday;          //  生日
}  Student;

//  定义顺序栈结构体
typedef struct {
    Student data[MAX_SIZE];  //  栈中存放的元素数组，类型为 Student 
    int top;                 //  栈顶指针， -1 表示空栈 
} SqStack;

// =====================================
//  2.  基础函数声明
// =====================================

//  初始化栈
void InitStack(SqStack *s);

//  判断栈是否为空
bool IsEmpty(SqStack s);

//  判断栈是否已满
bool IsFull(SqStack s);

//  进栈操作
bool Push(SqStack *s, Student e);

//  出栈操作
bool Pop(SqStack *s, Student *e);

//  获取栈顶元素
bool GetTop(SqStack s, Student *e);

//  打印栈内所有元素
void PrintStack(SqStack s);

// 获取用户输入的学生信息
Student InputStudent();

// =====================================
//  3. 函数实现
// =====================================

int main(void) {
    SqStack s;                  //  声明一个栈
    InitStack(&s);              //  初始化栈

    int choice;
    Student tempStu;
    bool flag;

    //  简单的交互菜单，方便测试所有操作
    while(1) {
        printf("\n======= 顺序栈演示系统 ========\n");
        printf("1. 进栈\n");
        printf("2. 出栈\n");
        printf("3. 查看栈顶元素\n");
        printf("4. 打印所有栈内元素\n");
        printf("0. 退出\n");
        printf("请输入选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (IsFull(s)) {
                    printf("栈已满，无法进栈！\n");
                } else {
                    printf("请输入学生信息：\n");
                    tempStu = InputStudent();
                    flag = Push(&s, tempStu);
                    if (flag) printf("进栈成功！\n");
                }
                break;
            case 2:
                if (IsEmpty(s)) {
                    printf("栈为空，无法出栈！\n");
                } else {
                    flag = Pop(&s, &tempStu);  //  注意出入地址
                    if (flag) {
                        printf("出栈成功！出栈的学生信息：[%d] %s\n", tempStu.id, tempStu.name);
                    }
                }
                break;
            case 3:
                if (IsEmpty(s)) {
                    printf("栈为空，无栈顶元素！\n");
                } else {
                    flag = GetTop(s, &tempStu);
                    if (flag) {
                        printf("栈顶元素：[%d] %s (生日：%d-%d-%d)\n",
                                tempStu.id, tempStu.name,
                                tempStu.birthday.year, tempStu.birthday.month, tempStu.birthday.day);
                                }
                }
                break;
            case 4:
                PrintStack(s);
                break;
            case 0:
                printf("程序退出。\n");
                return 0;
                default:
                    printf("无效的选择，请重试。\n");
        }
    }
    return 0;
}

// --- 初始化栈 ---
void InitStack(SqStack *s) {
    s->top = -1;        //  栈顶指针置为 -1 
}

// --- 判空 ---
bool IsEmpty(SqStack s) {
    return s.top == -1;
}

// --- 判满 --- 
bool IsFull(SqStack s) {
    return s.top == MAX_SIZE - 1;
}

// --- 进栈 ---
bool Push(SqStack *s, Student e) {
    //  1. 检查是否满
    if (s->top == MAX_SIZE -1) {
        return false;
    }

    //  2. 指针上移
    s->top++;
    //  3. 赋值
    s->data[s->top] = e;
    return true;
}

// --- 出栈 ---
bool Pop(SqStack *s, Student *e) {
    //  1. 检查是否空
    if (s->top == -1) {
        return false;
    }

    //  2. 取值（通过指针参数带回数据）
    *e = s->data[s->top];
    //  3. 指针下移
    s->top--;
    return  true;
}

// --- 获取栈顶元素 ---
bool GetTop(SqStack s, Student *e) {
    if (s.top == -1) {
        return false;
    }
    *e = s.data[s.top];
    return true;
}

// --- 打印栈 ---
void PrintStack(SqStack s) {
    if (IsEmpty(s)) {
        printf("栈为空。\n");
        return;
    }
    printf("--- 栈内元素（从底到顶）---n");
    //   从 0 遍历到 top 
    for (int i = 0; i <= s.top; i++) {
        printf("[%d] 姓名：%-10s 生日：%d-%02d-%02d\n",
                s.data[i].id,
                s.data[i].name,
                s.data[i].birthday.year,
                s.data[i].birthday.month,
                s.data[i].birthday.day);
    }
    printf("------------------------------------\n");
}

// --- 辅助函数：输入学生信息 ---
Student InputStudent() {
    Student s;
    printf("学号：");
    scanf("%d", &s.id);
    printf("姓名：");
    scanf("%s", s.name);
    printf("生日：");
    scanf("%d %d %d", &s.birthday.year, &s.birthday.month, &s.birthday.day);
    return s;
}
