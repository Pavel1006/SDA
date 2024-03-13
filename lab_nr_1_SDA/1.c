#include <stdio.h>
#include <string.h>

struct Book
{
    char title[50];
    char author[50];
    int number_of_pages;
    float price;
};

void introduceBooks(struct Book arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details about book %d \n", i + 1);
        printf("Enter title: ");
        scanf("%s", arr[i].title);

        printf("Enter author: ");
        scanf("%s", arr[i].author);

        printf("Enter number of pages: ");
        scanf("%d", &arr[i].number_of_pages);

        printf("Enter price: ");
        scanf("%f", &arr[i].price);
    }
}

void displayBooks(struct Book arr[], int n)
{
    printf("\nBooks with price less than $20:\n");
    for (int i = 0; i < n; i++)
    {
        if (arr[i].price < 20)
        {
            printf("Book %d: %s\n", i + 1, arr[i].title);
        }
    }
}

int main()
{
    int nr_of_books;

    printf("Enter number of books: ");
    scanf("%d", &nr_of_books);

    struct Book arr_stock_of_books[nr_of_books];

    introduceBooks(arr_stock_of_books, nr_of_books);

    displayBooks(arr_stock_of_books, nr_of_books);

    return 0;
}
