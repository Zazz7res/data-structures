#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//  1. 先定义“学生”这种数据类型
//  这就是我们盒子里的“货物”
typedef struct {
    int id;                 //  学号
    char name[20];          //  姓名
    float score;            //  分数
} Student;

//  2. 定义“链表节点”
//  这里就是你要的【嵌套】
typedef struct Node {
    Student data;           //  【重点】:这里放了一个 Student 变量
}
