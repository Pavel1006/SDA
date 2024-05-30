#include <stdio.h>
#include <string.h>

struct Book
{
    char title[50];
    char author[50];
    int number_of_pages;
    float price;
};

void introduce_books(struct Book book_array[], int num_of_books)
{
    for (int i = 0; i < num_of_books; i++)
    {
        printf("\nEnter details about book %d \n", i + 1);
        printf("Enter title: ");
        scanf("%s", book_array[i].title);

        printf("Enter author: ");
        scanf("%s", book_array[i].author);

        printf("Enter number of pages: ");
        scanf("%d", &book_array[i].number_of_pages);

        printf("Enter price: ");
        scanf("%f", &book_array[i].price);
    }
}

void display_books(struct Book book_array[], int n)
{
    printf("\nBooks with price less than $20:\n");
    for (int i = 0; i < n; i++)
    {
        if (book_array[i].price < 20)
        {
            printf("Book %d: %s\n", i + 1, book_array[i].title);
        }
    }
}

int main()
{
    int nr_of_books;

    printf("Enter number of books: ");
    scanf("%d", &nr_of_books);

    struct Book arr_stock_of_books[nr_of_books];

    introduce_books(arr_stock_of_books, nr_of_books);

    display_books(arr_stock_of_books, nr_of_books);

    return 0;
}
