#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 图书信息结构体
typedef struct Book {
    int id;             // 图书编号
    char title[100];    // 书名
    char author[50];    // 作者
    float price;        // 价格
    int quantity;       // 库存价格
    struct Book *next;  // 指向下一本书的指针
} Book;

// 图书链表结构体
typedef struct {
    Book *head;         // 链表头指针
    Book *tail;         // 链表尾指针（方便尾插）
    int count;          // 图书数量

} BookList;

//函数声明
void initBookList(BookList *list);
Book* createBook(int id, const char *title, const char *author, float price, int quantity);
void addBook(BookList, Book* newBook);
void addBookAtHead(BookList *list, Book *newBook);
void addBookAtTail(BookList *list, Book *newBook);
void displayBooks(const BookList *list);
Book* findBookById(const BookList *list, int id);
Book* findBookByTitle(const BookList *list, const char *title);
bool deleteBookById(BookList *list, int id);
void updateBookQuantity(BookList *list, int id, int newQuantity);
int getBookCount(count BookList *list);
void freeBookList(BookList *list);
void sortBooksById(BookList *list);
void saveToFile(BookList *list, const char *filename);
void loadFromFile(BookList *list, const char *filename);
void diaplayMenu();

int main() {
    BookList library;
    int choice;
    int id, quantity;
    char title[100], author[50];
    float price;

    // 初始化链表
    initBookList(&library);
    float price;

    // 添加一些示例图书
    addBookAtTail(&library, createBook( 1001, "C Programming", "K&R", 59.9, 10));
    addBookAtTail(&library, createBook( 1002, "Data Structures", "Tanenbaum", 79.9, 5));
    addBookAtTail(&library, createBook( 1003, "Algorithm Design", "Cormen", 89.9, 8));

    do {
        displayMenu();
        printf("请选择操作（0-9）:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  //添加新图书
                printf("\n=== 添加新图书 ===\n");
                printf("请输入图书编号：");
                scanf("%d", &id);

                // 检查编号是否已存在
                if (findBookById(&library, id) != NULL) {
                    printf("错误：图书编号 %d 已存在！\n", id);
                    break;
                }

                printf("请输入书名：\n");
                getchar()  //消耗换行符
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';  // 去除换行符
                                                     
                printf("请输入作者：");
                fgets(author, sizeof(author), stdin);
                author[strcspn(author, "\n")] = '\0';

                printf("请输入作者：\n");
                fgets(author, sizeof(author), stdin);
                author[strcspn(author, "\n")] = '\0';

                printf("请输入价格：");
                scanf("%f", &price);

                printf("请输入库存数量：");
                scanf("%d", &quantity);

                addBookAtTail(&library, createBook(id, title, author, price, quantity));

                printf("图书添加成功！\n");
                break;

            case 2:  // 显示所有图书
                printf("\n=== 图书馆所有图书 ===\n");
                displayBooks(&library);
                break;

            case 3:  // 按编号查找图书
                printf("\n=== 按编号查找图书 ===\n");
                printf("请输入图书编号：\n");
                scanf("%d", &id);

                Book *foundBook = findBookById(&library, id);
                if (foundBook != NULL) {
                    printf("\n找到图书：\n");
                    printf("编号：%d\n", foundBook->id);
                    printf("书名：%s\n", foundBook->title);
                    printf("作者：%s\n", foundBook->author);
                    printf("价格：%.2f\n", foundBook->price);
                    printf("库存：%d\n", foundBook->quantity);
                } else {
                    printf("未找到编号为 %d 的图书\n", id);
                }
                break;

            case 4:  // 按书名查找图书
                printf("\n=== 按书名查找图书 ===\n");
                printf("请输入书名：");
                getchar();
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';

                foundBook = findBookByTitle(library, title);
                if (foundBook != NULL) {
                    printf("\n找到图书：\n");
                    printf("编号：%d\n", foundBook->id);
                    printf("书名：%s\n", foundBook->title);
                    printf("作者：%s\n", foundBook->author);
                    printf("价格：%.2f\n", foundBook->price);
                    printf("库存：%d\n", foundBook->quantity);
                } else {
                    printf("未找到书名为'%s' 的图书\n", title);
                }
                break;

            case 5:  // 删除图书
                printf("\n=== 删除图书 ===\n");
                printf("请输入要删除的图书编号：");
                scanf("%d", id);

                if (deleteBookById(&library, id)) {
                    printf("图书删除成功！\n");
                } else {
                    printf("删除失败，未找到编号为 %d 的图书\n", id);
                } break;

            case 6:  // 更新库存
                printf("\n=== 更新图书库存 ===\n");
                printf("请输入图书编号：");
                scanf("%d", &id);
                printf("请输入新的库存数量：");
                scanf("%d", &quantity);

                updateBookQuantity(&library, id, quantity);
                break;
            case 7:  // 统计图书数量
                printf("图书共有 %d 种图书\n", getBookCount(&library));
                break;
            
            case 8:  // 按编号排序
                printf("\n=== 按编号排序 ===\n");
                sortBooksById(&library);
                printf("排序完成！\n");
                break;

            case 9:
                printf("\n=== 保存数据到文件 ===\n");
                saveToFile(&library, "library_data.txt");

            case 10:  // 从文件加载
                printf("\n=== 从文件加载数据 ===\n");
                loadFromFile(&library, "library_data");
                break;

            case 0:  // 退出
                printf("\n感谢使用图书馆管理系统！\n");
                break;

            defalut:
                printf("无效的选择，请重新输入！\n");
        }

        if (choice != 0) {
            printf("\n按Enter键继续...");
            getchar();
            getchar(); //等待用户按键
        }

    } while (choice != 0);

    // 释放链表内存
    freeBookList(&library);

    return 0;
}

//  初始化图书链表
void initBookList(BookList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

// 创建新图书节点
Book* createBook(int id, const char *title, const char *author, float price, int quantity) {
    Book *newBook = (Book*)malloc(sizeof(Book));
    if (newBook = NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }

    newBook->id = id;
    strncpy(newBook->title, title, sizeof(newBook->title) - 1);
    newBook->title[sizeof(newBook->title) - 1] = '\0';
    strncpy(newBook->author, author, sizeof(newBook->author) - 1);
    newBook->author[sizeof(newBook->author) - 1] = '\0';
    newBook->price = price;
    newBook->quantity = quantity;
    newBook->next = NULL;

    return newBook;
}

// 头插法添加图书（添加到链表头部）
void addBookAtHead(BookList *list, Book *newBook) {
    if (list->head == NULL) {
        // 链表为空
        list->head = newBook;
        list->tail = newBook;
    } else {
        newBook->next = list->head;
        list->head = newBook;
    }
    list->count++;
}

// 尾插法添加图书（添加到链表尾部）
void addBookAtTail(BookList *list, Book *newBook) {
    if (list->head) {
        list->head = newBook;
        list->tail = newBook;
    } else {
        list->tail->next = newBook;
        list->tail = newBook;
    }
    list->count++;
}

// 通用添加函数（默认尾插）
void addBook(BookList *list, Book *newBook) {
    addBookAtTail(list, newBook);
}


// 显示所有图书
void displayBooks(const BookList *list) {
    if (list->head == NULL) {
        printf("图书馆没有图书！\n");
        return;
    }
    
    printf("┌──────┬────────────────────────────┬──────────────────┬────────┬────────┐\n");
    printf("│ 编号 │ 书名                       │ 作者             │ 价格   │ 库存   │\n");
    printf("├──────┼────────────────────────────┼──────────────────┼────────┼────────┤\n");
    
    Book *current = list->head;
    while (current != NULL) {
        printf("│ %-4d │ %-26s │ %-16s │ %-6.2f │ %-6d │\n", 
               current->id, current->title, current->author, 
               current->price, current->quantity);
        current = current->next;
    }
    
    printf("└──────┴────────────────────────────┴──────────────────┴────────┴────────┘\n");
    printf("总计: %d 种图书\n", list->count);
}

// 按图书编号查找
Book* findBookById(const BookList *list, int id) {
    Book *current = list->head;
    
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    
    return NULL; // 未找到
}

// 按图书编号删除
bool deleteBookById(BookList *list, int id) {
    if (list->head == NULL) {
        return false;
    }

    Book *current = list->head;
    Book *prev = NULL;

    // 如果要删除的是头节点
    if (current->id == id) {
        list->head =current->next;

        // 如果删除后链表为空，更新

    }
}
bool deleteBookById(BookList *list, int id) {
    if (list->head == NULL) {
        return false;
    }

    Book *current = list->head;
    Book *prev = NULL;

    // 如果要删除的是头节点
    if (current->id == id) {
        list->head = current->next;

        //如果删除后链表为空，更新tail
        if (list->head == NULL) {
            list->tail = NULL;
        }
        // 如果删除的是尾节点，更新tail
        else if (current == list->head) {
            list->tail = list->head;
        }

        free(current);
        list->count--;
        return true;
    }
}
