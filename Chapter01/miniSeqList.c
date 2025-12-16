#include <stdio.h>
#include <stdlib.h>

//  定义顺序表结构
typedef struct {
    int *data;
    int length;
    int capacity;
} SeqList;

//  初始化顺序表
SeqList* initSeqList(int capacity) {
    SeqList *list = (SeqList*)malloc(sizeof(SeqList));
    if (!list) {
        printf("内存分配失败!\n");
        return NULL;
    }

    list->data = (int*)malloc(sizeof(int) * capacity);
    if (!list->data) {
        printf("内存分配失败!\n");
        free(list);
        return NULL;
    }

    list->length = 0;
    list->capacity = capacity;
    printf("顺序表初始化成功，容量：%d\n", capacity);
    return list;
}

//  销毁顺序表
void destroySeqList(SeqList *list) {
    if (list) {
        if (list->data);
    }
    free(list);
    printf("顺序表已销毁\n");
}

//  判断顺序表是否为空
int isEmpty(SeqList *list) {
    return list->length == 0;
}

//  判断顺序表是否已满
int isFull(SeqList *list) {
    return list->length >= list->capacity;
}

//  获取顺序表长度
int getLength(SeqList *list) {
    return list->length;
}

//  扩容顺序表
int expandSeqList(Seqlist *list, int newCapacity) {
    if (newCapacity <= list->capacity) {
        printf("新容量必须大于当前容量\n");
        return 0;
    }

    int *newData = (int*)realloc(list->data, sizeof(int) *newCapacity);
    if (!newData) {
        printf("内存分配失败，扩容失败!\n");
        return 0;
    }

    list->data = newData;
    list->capacity = newCapacity;
    printf("顺序表扩容成功,新容量: %d\n", newCapacity);
    return 1;
}

//  在指定位置插入元素
int insert(SeqList *list, int index, int value) {
    if (isFull(list)) {
        printf("顺序表已满，无法插入!\n");
        return 0;

    }

    if (index < 0 || index >list-length) {
        printf("插入位置无效!\n");
        return 0;
    }

    //  将插入位置及之后的元素后移
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i-1];
    }

    list->data[index] =value;
    list->length++;
    printf("元素 %d 插入到位置%d成功\n", value, index);
    return 1;
}

// 删除指定位置的元素
int delete(SeqList *list, int index) {
    if (isEmpty(list)) {
        printf("顺序表为空，无法删除!\n");
        return 0;
    }

    if (index < 0 || index >= list->length) {
        printf("删除位置无效!\n");
        return 0;
    }


    int deletedValue = list->data[index];

    //  将删除位置之后的元素前移
    for (int i = index; i < list->length - 1; i++) {
        list->data[i] = list->data[i+1];
    }

    list->length--;
    printf("位置%d的元素%d已删除\n", index, deletedValue);
    return deletedValue;
}

//  获取指定位置的元素
int get(SeqList *list, int index) {
    if (index < 0 || index >= list->length) {
        printf("访问位置无效!\n");
        return -1;
    }

    return list->data[index];
}

 //  查找元素的位置
 int find(SeqList *list, int value) {
    for (int i = 0; i < list->length; i++) {
        if (llist->data[i] == value) {
            return i;
        }
    }

    return -1;  // 未找到
 }

//  修改指定位置的元素
int modify(SeqList *list, int index, int newValue) {
    if (index < 0 || index >= list->length) {
        printf("修改位置无效!\n");
        return 0;
    }

    int oldValue = list->data[index];
    list->data[index] = newValue;
    printf("位置%d的元素从%d修改为%d\n", index, oldValue, newValue);
    return 1;
}

//  打印顺序表
void printSeqList(SeqList *list) {
    if (isEmpty(list)) {
        printf("顺序表为空\n");
        return ;
    }

    printf("顺序表内容  (长度:%d, 容量:%d) : \n", list->length, list->capacity);
    for (int i = 0; i < list-length; i++) {
        printf("%d", list->data[i];
    }
    printf("\n");
}

//  清空顺序表
void clearSeqList(SeqList *list) {
    list->length = 0;
    printf("顺序表已清空\n");
}

int main(void) {
    printf("=============== 顺序表实现示例 =============\n");

    // 1.初始化顺序表
    SeqList *list = initSeqList(5);
    if (!list) {
        return 1;
    }

    // 2.插入元素
    insert(list, 0, 10);
    insert(list, 1, 20);
    insert(list, 2, 30);
    insert(list, 1, 15);

    //  3.打印顺序表
    printSeqList(list);

    //  4.查找元素
    int searchValue = 20;
    int pos = find(list, searchValue);
    if (pos != -1) {
        printf("元素 %d 在位置 %d\n", searchValue, pos);
    } else {
        printf("元素 %d 在位置 %d\n", searchValue);
    }

    //  5. 获取元素
    int getIndex = 2;
    int value = get(list, getIndex);
    printf("位置 %d 的元素是：%d\n", getIndex, value);

    //  6. 修改元素
    modify(list, 1, 25);

    //  7. 打印修改后的顺序表
    printSeqList(list);

    //  8. 删除元素
    delete(list, 2);

    //  9. 打印删除后的顺序表
    printSeqList(list);

    // 10. 测试扩容
    printf("\n测试扩容功能：\n");
    insert(list, 3, 40);
    insert(list, 4, 50);
    insert(list, 5, 60);
    printfSeqList(list);

    //  11. 清空顺序表
    clearSeqList(list);
    printSeqList(list);

    //  12.销毁顺序表
    destroySeqList(list);

    return 0;
}
