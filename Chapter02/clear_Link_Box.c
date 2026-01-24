#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========================================
// 第一步：定义"学生卡片"结构体
// ========================================
typedef struct {
    int id;           // 学号
    char name[20];    // 姓名
    float score;      // 分数
} StudentCard;

// ========================================
// 第二步：定义"带挂钩的盒子"结构体
// ========================================
typedef struct Box {
    StudentCard card;        // 盒子里放一张学生卡片
    struct Box *hook;        // 盒子上的挂钩，指向下一个盒子
} Box, *RopeHead;            // 绳子头就是指向第一个盒子的指针

// ========================================
// 第三步：各种操作函数
// ========================================

// 1. 初始化一根空绳子
RopeHead initRope() {
    return NULL;  // 绳头什么也没系
}

// 2. 检查绳子是否空
int isRopeEmpty(RopeHead ropeHead) {
    return ropeHead == NULL;
}

// 3. 头插法：新盒子系在绳头
void insertAtHead(RopeHead *ropeHeadAddr, StudentCard newCard) {
    // 1. 造一个新盒子
    Box *newBox = (Box*)malloc(sizeof(Box));
    
    // 2. 把卡片放进盒子
    newBox->card = newCard;
    
    // 3. 连接盒子
    // 新盒子的挂钩挂上原来绳头挂的盒子（可能是NULL）
    newBox->hook = *ropeHeadAddr;
    
    // 4. 绳头改系这个新盒子
    *ropeHeadAddr = newBox;
    
    printf(">> 新学生[%s]已系在绳头\n", newCard.name);
}

// 4. 尾插法：新盒子系在绳尾
void insertAtTail(RopeHead *ropeHeadAddr, StudentCard newCard) {
    // 1. 造新盒子
    Box *newBox = (Box*)malloc(sizeof(Box));
    newBox->card = newCard;
    newBox->hook = NULL;  // 尾盒子的挂钩不挂东西
    
    // 2. 如果绳子是空的
    if (*ropeHeadAddr == NULL) {
        *ropeHeadAddr = newBox;
        printf(">> 新学生[%s]是第一个盒子\n", newCard.name);
        return;
    }
    
    // 3. 找到绳子的最后一个盒子
    Box *currentBox = *ropeHeadAddr;
    while (currentBox->hook != NULL) {
        currentBox = currentBox->hook;  // 顺着挂钩一个个找
    }
    
    // 4. 把新盒子挂到最后一个盒子的挂钩上
    currentBox->hook = newBox;
    printf(">> 新学生[%s]已系在绳尾\n", newCard.name);
}

// 5. 遍历绳子：打印所有盒子
void traverseRope(RopeHead ropeHead) {
    printf("\n=============== 遍历绳子 ===============\n");
    
    if (isRopeEmpty(ropeHead)) {
        printf("绳子是空的，没有盒子！\n");
        return;
    }
    
    Box *currentBox = ropeHead;
    int position = 1;
    
    while (currentBox != NULL) {
        printf("位置%d: [学号:%d 姓名:%s 分数:%.1f]\n",
               position,
               currentBox->card.id,
               currentBox->card.name,
               currentBox->card.score);
        
        currentBox = currentBox->hook;  // 移到下一个盒子
        position++;
    }
    printf("=======================================\n");
}

// 6. 按学号查找盒子
Box* findBoxById(RopeHead ropeHead, int targetId) {
    Box *currentBox = ropeHead;
    
    while (currentBox != NULL) {
        if (currentBox->card.id == targetId) {
            return currentBox;  // 找到了，返回这个盒子的地址
        }
        currentBox = currentBox->hook;
    }
    
    return NULL;  // 没找到
}

// 7. 按学号删除盒子
void deleteBoxById(RopeHead *ropeHeadAddr, int deleteId) {
    if (*ropeHeadAddr == NULL) {
        printf("绳子是空的，没东西可删！\n");
        return;
    }
    
    Box *currentBox = *ropeHeadAddr;
    Box *prevBox = NULL;  // 记住当前盒子的前一个盒子
    
    // 寻找要删除的盒子
    while (currentBox != NULL && currentBox->card.id != deleteId) {
        prevBox = currentBox;
        currentBox = currentBox->hook;
    }
    
    // 没找到
    if (currentBox == NULL) {
        printf("没找到学号为%d的学生\n", deleteId);
        return;
    }
    
    // 找到了，开始删除
    if (prevBox == NULL) {
        // 情况1：删除的是第一个盒子
        *ropeHeadAddr = currentBox->hook;  // 绳头直接系到第二个盒子
    } else {
        // 情况2：删除的是中间或最后的盒子
        prevBox->hook = currentBox->hook;  // 前盒子的挂钩跳过当前盒子
    }
    
    printf(">> 已删除学生[%s]\n", currentBox->card.name);
    free(currentBox);  // 把这个盒子从内存中扔掉
}

// 8. 计算绳子上有多少盒子
int countBoxes(RopeHead ropeHead) {
    int count = 0;
    Box *currentBox = ropeHead;
    
    while (currentBox != NULL) {
        count++;
        currentBox = currentBox->hook;
    }
    
    return count;
}

// 9. 清空整根绳子
void clearRope(RopeHead *ropeHeadAddr) {
    Box *currentBox = *ropeHeadAddr;
    Box *nextBox;
    
    while (currentBox != NULL) {
        nextBox = currentBox->hook;  // 先记住下一个盒子在哪
        free(currentBox);            // 扔掉当前盒子
        currentBox = nextBox;        // 移到下一个盒子
    }
    
    *ropeHeadAddr = NULL;  // 绳头现在什么都不系了
    printf(">> 绳子已清空，所有盒子已扔掉\n");
}

// 10. 修改学生的分数
void updateScore(RopeHead ropeHead, int id, float newScore) {
    Box *targetBox = findBoxById(ropeHead, id);
    
    if (targetBox == NULL) {
        printf("没找到学号为%d的学生\n", id);
        return;
    }
    
    targetBox->card.score = newScore;
    printf(">> 学生[%s]的分数已改为%.1f\n", targetBox->card.name, newScore);
}

// ========================================
// 第四步：演示所有操作
// ========================================
int main() {
    printf("🧵 绳子与盒子链表演示 🧵\n\n");
    
    // 1. 初始化一根空绳子
    RopeHead myRope = initRope();
    printf("1. 初始化绳子: %s\n", isRopeEmpty(myRope) ? "空的" : "有盒子");
    
    // 2. 创建几张学生卡片
    StudentCard zhangSanCard = {101, "张三", 85.5};
    StudentCard liSiCard = {102, "李四", 92.0};
    StudentCard wangWuCard = {103, "王五", 78.5};
    StudentCard zhaoLiuCard = {104, "赵六", 88.0};
    StudentCard sunQiCard = {105, "孙七", 95.5};
    
    // 3. 测试头插法（倒序：新来的在前面）
    printf("\n2. 测试头插法（新盒子系在绳头）:\n");
    printf("   绳子原来: 空\n");
    insertAtHead(&myRope, zhangSanCard);
    printf("   插入张三后: 绳头->[张三]\n");
    insertAtHead(&myRope, liSiCard);
    printf("   插入李四后: 绳头->[李四]->[张三]\n");
    insertAtHead(&myRope, wangWuCard);
    printf("   插入王五后: 绳头->[王五]->[李四]->[张三]\n");
    traverseRope(myRope);
    
    // 4. 测试尾插法（正序：新来的在后面）
    printf("\n3. 测试尾插法（新盒子系在绳尾）:\n");
    printf("   绳子现在: 绳头->[王五]->[李四]->[张三]\n");
    insertAtTail(&myRope, zhaoLiuCard);
    printf("   插入赵六后: ...->[张三]->[赵六]\n");
    traverseRope(myRope);
    
    // 5. 测试查找
    printf("\n4. 测试查找:\n");
    int targetId = 102;
    Box *foundBox = findBoxById(myRope, targetId);
    if (foundBox != NULL) {
        printf("   找到了学号%d的学生: %s (分数: %.1f)\n",
               targetId, foundBox->card.name, foundBox->card.score);
    } else {
        printf("   没找到学号%d的学生\n", targetId);
    }
    
    // 6. 测试修改
    printf("\n5. 测试修改分数:\n");
    updateScore(myRope, 103, 100.0);  // 把王五的分数改成100
    traverseRope(myRope);
    
    // 7. 测试删除
    printf("\n6. 测试删除盒子:\n");
    printf("   删除第一个盒子(王五):\n");
    deleteBoxById(&myRope, 103);
    traverseRope(myRope);
    
    printf("   删除中间盒子(李四):\n");
    deleteBoxById(&myRope, 102);
    traverseRope(myRope);
    
    printf("   删除最后一个盒子(赵六):\n");
    deleteBoxById(&myRope, 104);
    traverseRope(myRope);
    
    // 8. 再测试尾插法
    printf("\n7. 再次测试尾插法:\n");
    insertAtTail(&myRope, sunQiCard);
    traverseRope(myRope);
    
    // 9. 统计数量
    printf("\n8. 统计盒子数量:\n");
    printf("   绳子上共有 %d 个盒子\n", countBoxes(myRope));
    
    // 10. 清空绳子
    printf("\n9. 清空绳子:\n");
    clearRope(&myRope);
    traverseRope(myRope);
    
    return 0;
}
