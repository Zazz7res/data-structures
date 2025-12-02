#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50  // 最大学生数
#define NAME_LEN 20          // 姓名最大长度
#define ID_LEN 10    // 学号最大长度

/*  学生信息结构体  */ 
typedef struct {
    char id[ID_LEN];        /*  学号  */ 
    char name[NAME_LEN];   /*  姓名  */ 
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
    int excellent = 0, good = 0, medium = 0, pass = 0, fail = 0;

    for (int i = 0; i < list->length; i++) {
        int score = list->students[i].score;
        if (score >= 90) excellent++;
        else if (score >= 80) good++;
        else if (score >= 70) medium++;
        else if (score >= 80) pass++;
        else fail++;
        
    }

    printf("优秀（90 - 100): %d人\n", excellent);
    printf("良好（80 - 89): %d人\n", good);
    printf("中等（70 - 79): %d人\n", medium);
    printf("及格（60 - 69): %d人\n", pass);
    printf("不及格（<60): %d人\n", fail);
}

// 11. 显示所有学生信息
void DisplayList(SeqList *list) {
    if (list->length == 0) {
        printf("成绩表为可空！\n");
        return;
    }
    
    printf("\n========== 学生成绩表（共%d人）==========\n", list->length);
    printf("%-4s %-10s %-20s %s\n", "序号", "学号", "姓名", "成绩");
    printf("--------------------------------------------\n");

    for (int i = 0; i < list->length; i++) {
        printf("%-4d %-10s %-20s %d\n",
                i + 1,
                list->students[i].id;
                list->students[i].name,
                list->students[i].score);
    }

    // 显示统计信息
    printf("\n统计信息：\n");
    printf("平均成绩：%.2f\n", GetAverageScore(list));
    CountScoreRange(list);
    printf("================================================\n\n");
}

// 12.获取表长度
int GetLength(SeqList *list) {
    return list->length;
}

// 13.判断表是否为空
int IsEmpty(SeqList *list) {
    return list->length == 0;
}

//演示函数
void Demo() {
    printf("========== 学生成绩管理系统（顺序表实现） ==========\n\n");
    
    SeqList gradeList;
    Student tempStudent;


    // 初始化
    InitList(&gradeList);

    // 创建示例数据
    CreateList(&gradeList);
    DisplayList(&gradeList);

    //查找演示
    printf("1.查找演示：\n");
    int pos = FindByID(&gradeList, "2021003");
    if (pos != -1) {
        GetStudent(&gradeList, pos, &tempStudent);
        printf("    找到学号2021003:%s, 成绩%d\n", tempStudent.name, tempStudent.score);
    }

    // 插入演示
    printf("\n2. 插入演示：\n");
    Student newStudent = { "2021006", "孙八", 87 };
    InsertStudent(&gradeList, 3, newStudent);
    DisplayList(&gradeList);

    //删除演示
    printf("\n3.删除演示：\n");
    DeleteStudent(&gradeList, 2);
    DisplayList(&gradeList);

    //查找最高分
    printf("\n4.查找最高分学生：\n");
    Student maxStudent;
    if (FindMaxScore(&gradeList, &maxStudent)) {
        printf("    最高分：%s（学号：%s), 成绩：%d\n",
                maxStudent.name, maxStudent.id, maxStudent.score);
    }

    //其他信息
    printf("\n5.其他信息：\n");
    printf("    当前学生数：%d\n", GetLength(&gradeList));
    printf("    成绩表是否为空：%s\n", IsEmpty(&gradeList) ? "是" : "否");
}

//主函数
int main() {
    Demo();

    //扩展：交互式菜单（可选）
     
    SeqList gradeList;
    InitList(&gradeList);

    int choice;
    do {
        printf("\n===== 学生成绩管理系统 =====\n");
        printf("1. 添加学生\n");
        printf("2. 删除学生\n");
        printf("3. 查找学生\n");
        printf("4. 显示所有学生\n");
        printf("5. 统计成绩\n");
        printf("6. 退出\n");
        printf("请选择：");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
            // 添加学生代码
            break;
            case 4:
                DisplayList(&gradeList);
                break;
            // 其他选项...
        }
    } while(choice != 6);

    return 0;
}
