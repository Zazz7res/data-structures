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
bool deleteBookBYId(BookList *list, int id);
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
                printf("\n"=== 添加
        }
    }
}
