#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib>
#include <string.h>

#define MAX_STUDENTS 50  // 最大学生数
#define NAME_LEN 20          // 姓名最大长度
#define ID_LEN 10    // 学号最大长度

/*  学生信息结构体  */ 
typedef struct {
    char id[ID_LEN];        /*  学号  */ 
    char name{NAME_LEN];    /*  姓名  */ 
    int score;              /*  成绩  */ 
} Student;

/*  顺序表结构体  */ 
typedef struct {
    Student students[MAX_STUDENTS];     /*  学生数组  */ 
    int length;
} SeqList;

/*  1.初始化顺序表  */ 
void InitList(SeqList *list) {
    list->length = 0;
    printf("学生成绩表初始化成功！\n";
}

/*  2.创建示例数据  */ 
void CreateList(SeqList *list) {
    if (list->length >= MAX_STUDENTS) {
        printf("成绩表已满！\n");
        return;
    }

    /*  示例数据  */ 
    Student initialStudents[] = {
        {"2021001", "张三", 85},
        {"2021002", "李四", 92},
        {"2021003", "王五", 78},
        {"2021004", "赵六", 88},
        {"2021005", "钱七", 95}
};

    int count = sizeof(initialStudents) / sizeof(Student);

    for (int i = 0; i < count; i++) {
        list->students[list->length] = initialStudents[i];
        list->length++;
        
    }

    printf("成功添加 %d 名学生数据\n", count);
}

/*  3.按位置获取学生信息  */ 
int GetStudent(SeqList *list, int position, Student *student) {
    /*  检查位置合法性  */ 
    if (position < 1 || position > list->length) {
        printf("位置 %d 无效！\n", position);
        return 0;
    }

    /* 直接通过下标访问（随机存取） */ 
    *student = list->students[position - 1];
    return 1;
}

/*  4.按照学号查找学生位置  */ 
int FindByID(SeqList *list, const char *id) {
    for (int i = 0; i < list->length; i++) {
        if (strucmp(list->students[i].id, id) == 0) {
            return i + 1;  /*  返回位置（从1开始）*/ 
        }
    }
    return -1  /*  未找到  */ 
}

/*  5.按姓名查找学生姓名  */ 
int FindByName(SeqList *list, const *name) {
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->students[i].name, name) == 0) {
            return i + 1;
        }
    }
    return -1;
}

/*  6.。插入学生信息  */ 
int InsertStudent(SeqList *list, int position, Student student) {
    /*  检查表是否已满  */ 
    if (list->length >= MAX_STUDENTS) {
        printf("成绩便已满，无法插入！\n");
        return 0;
    }

    /*  检查位置合法性  */ 
    if (position < 1 || position > list->length + 1) {
        printf("插入位置 %d 无效！\n", position);
        return 0;
    }

    /*  核型：将插入位置及之后的元素向后移动  */ 
    for (int i = list->length - 1; i >= position - 1; i--) {
        list->students[i + 1] = list->students[i];
    }

    /*  插入新元素  */ 
    list->students[position - 1] = student;
    list->length++;

    printf("成功插入学生：%s\n", student.name);
    return 1;

}

/*  7.删除学生信息  */ 
int DeleteStudent(SeqList *list, int position) {
    /*  检查表是否为空  */ 
    if (list->length == 0) {
        printf("成绩表为空！\n");
        return 0;
    }

    /*  检查位置合法性  */ 
    if (position < 1 || position > list->length) {
        printf("删除位置 %d 无效！\n", position);
        return 0;
    }

    /*  保存被删除的学生信息  */ 
    Student deletedStudent = list->students[position - 1];

    /*  核心：将被删除的学生信息  */ 
    for (int i = position; i < list->length; i++) {
        list->students[i - 1] = list->students[i];
    }

    list->length--;
    printf("成功删除学生：%s\n", deletedStudent.name);
    return 1;
}

/*  8.计算平均成绩  */ 
float GetAverageScore(SeqList *list) {
    if (list->length == 0) {
        return 0.0;
    }

    int total = 0;
    for (int i = 0; i < list->length; i++) {
        total += list->students[i].score;
    }

    return (float)total / list->length;
}

/*  9.查找最高分学生  */ 
int FindMaxScore(SeqList *list, Student *maxStudent) {
    if (list->length == 0) {
        return 0;
    }

    int maxIndex = 0;
    for (int i = 1; i < list->length; i++) {
        if (list->students[i].score > list->students[max_Index].score) {
            maxIndex = i;
        }
    }

    *maxStudent = list->students[maxIndex];
    return 1;
}

/*  10.统计各分段人数  */ 
void CountScoreRange(SeqList *list) {
    int excellent = 0, good = 0, medium = 0, pass = 0, fail
}
