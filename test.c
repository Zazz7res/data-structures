#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct
{
    int key;
    char data;
} RecordType;

typedef struct
{
    RecordType records[MAXSIZE];
    int length;
} SeqList;

//初始化顺序表
void InitSeqList(SeqList *L)
{
    L->length = 0;
}

//计数排序算法
void CountSort(SeqList *L, SeqList *SortedL)
{
    int i, j, count;


    //初始化结果表长度
    SortedL->length = L->length;

    printf("排序过程:\n");
    //对原表中的每个记录进行计数
    for (i = 0; i < L->length; i++)
    {
        count = 0;  //  计数器清零
        //扫描整个表，统计比当前记录关键字小的记录个数
        for (j = 0; j < L->length; j++)
        {
            if (L->records[j].key < L->records[i].key)
            {
                count++;
            }

        }
            
        //根据计数值确定新的位置
        SortedL->records[count] = L->records[i];
        printf("记录 %d 的计数值为 %d, 放在位置 %d\n", L->records[i].key, count, count);
    }
}

//  打印顺序表
void PrintSeqList(SeqList *L)
{
    int i;
    for (i = 0; i < L->length; i++)
    {
        printf("%d ", L->records[i].key);

    }
    printf("\n");

}

//  计算比较次数
int CalculateComparisons(int n)
{
    return n * n;

}

//简单选择排序用于比较
void SelectionSort(SeqList *L)
{
    int i, j, min, comparisons = 0;
    RecordType temp;

    for (i = 0; i < L->length -1; i++)
    {
        min = i;
        for (j = i + 1; j < L->length; j++)
        {
            comparisons++;
            if (L->records[j].key < L->records[min].key)
            {
                min = j;

            }

        }
        if (min != i)
        {
            temp = L->records[i];
            L->records[i] = L->records[min];
            L->records[min] = temp;

        }

    }
    printf("简单选择排序选择比较次数: %d\n", comparisons);



}

int main(void)
{
    SeqList L, SortedL;

    //初始化
    InitSeqList(&L);
    InitSeqList(&SortedL);


    L.length = 8;
    L.records[0].key = 46;
    L.records[1].key = 79;
    L.records[2].key = 56;
    L.records[3].key = 38;
    L.records[4].key = 40;
    L.records[5].key = 84;
    L.records[6].key = 12;
    L.records[7].key = 65;
    
    printf("=== 计数排序算法演示 ===\n");
    printf("原始序列:\n");
    PrintSeqList(&L);
    printf("\n");

    //执行计数排序
    CountSort(&L, &SortedL);

    printf("\n排序后序列:");
    PrintSeqList(&SortedL);

    //计算比较次数
    int n = L.length;
    int comparisons = CalculateComparisons(n);
    printf("\n=== 算法分析 ===\n");
    printf("记录个数 n = %d\n", n);
    printf("计数排序关键字比较次数: %d\n", comparisons);
    printf("\n=== 与简单选择排序比较 === \n");
    printf("时间复杂度: O(n^2) = O(%d^2) = %d\n", n, n*n);
    //  重新初始化测试数据用于选择排序
    SeqList L2 = L;
    SelectionSort(&L2);
    printf("选择排序理论比较次数: %d\n", n*(n - 1)/ 2);

    printf("\n=== 结论=== \n");
    printf("计数排序比较次数 %d\n", n*n);
    printf("简单选择排序比较次数: %d\n", n*(n-1)/2);
    printf("计数排序比较次数是简单排序的 %.1f 倍\n", (double)(n*n) / (n*(n-1)/2));
    printf("因此，简单选择排序优于计数排序\n");







    return 0;

}
