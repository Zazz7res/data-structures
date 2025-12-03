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

                if (deleteBookBYId(&library, id)) {
                    printf("图书删除成功！\n");
                } else {
                    printf("删除失败，未找到编号为 %d 的图书\n", id);
                } break;

            case 6:

        }
    }
}
