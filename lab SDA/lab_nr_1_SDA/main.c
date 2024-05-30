#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    char title[50];
    char author[50];
    int number_of_pages;
    float price;
} Book;

void generate_random_book(Book *book, int index_book)
{
    sprintf(book->title, "Random Title %d", index_book);
    sprintf(book->author, "Random Author %d", index_book);
    book->number_of_pages = rand() % 500 + 50;
    book->price = (float)(rand() % 1000);
}

Book *generate_array_of_random_books(int size)
{
    Book *books = malloc(size * sizeof(Book));
    if (books == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        generate_random_book(&books[i], i);
    }
    return books;
}

void display_books(int size, Book *books)
{
    printf("Current Array:\n");
    for (int i = 0; i < size; i++)
    {
        printf("Book %d: Title: %s, Author: %s, Pages: %d, Price: $%.2f\n", i + 1, books[i].title, books[i].author, books[i].number_of_pages, books[i].price);
    }
}

int insert_book_by_index(Book **books, int *size, Book new_book, int insert_index)
{
    Book *new_array = realloc(*books, (*size + 1) * sizeof(Book));
    if (new_array == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 0;
    }
    (*size)++;
    *books = new_array;

    if (insert_index < *size - 1)
    {
        for (int i = *size - 1; i > insert_index; i--)
        {
            (*books)[i] = (*books)[i - 1];
        }
    }

    (*books)[insert_index] = new_book;

    return 1;
}

int delete_book_at_index(Book **books, int *size, int delete_index)
{
    if (*size == 0 || delete_index < 0 || delete_index >= *size)
    {
        fprintf(stderr, "Invalid index for deletion.\n");
        return 0;
    }

    for (int i = delete_index; i < *size - 1; i++)
    {
        (*books)[i] = (*books)[i + 1];
    }

    (*size)--;

    if (*size > 0)
    {
        Book *new_array = realloc(*books, (*size) * sizeof(Book));
        if (new_array == NULL)
        {
            fprintf(stderr, "Memory reallocation failed.\n");
            return 0;
        }
        *books = new_array;
    }
    else
    {
        free(*books);
        *books = NULL;
    }

    return 1;
}

void enter_book_details(Book *new_book)
{
    char title[50], author[50];
    int num_pages;
    float price;
    int check_enter_book_value = 0;
    while (1)

    {
        printf("\n Enter new book details (Title, Author, Pages, Price): ");
        if (scanf("%49s %49s %d %f", title, author, &num_pages, &price) != 4)
        {
            printf("\n Input invalid! Please enter valid data.\n");
            check_enter_book_value = 0;
        }
        else
        {

            check_enter_book_value = 1;
            break;
        }
    }
    if (check_enter_book_value == 1)
    {

        strcpy(new_book->title, title);
        strcpy(new_book->author, author);
        new_book->number_of_pages = num_pages;
        new_book->price = price;
    }
}

int main()
{
    Book *books = NULL;
    int size;
    srand(time(NULL));
    // size int verification
    printf("Enter the number of random books to generate: ");
    if (scanf("%d", &size) != 1)
    {
        fprintf(stderr, "Invalid input. Size should be an integer.\n");
        return 0;
    }
    //
    books = generate_array_of_random_books(size);

    display_books(size, books);

    int insert_index;

    // insert index verification
    printf("Enter insertion index: ");
    if (scanf("%d", &insert_index) != 1)
    {
        fprintf(stderr, "Invalid input. Size should be an integer.\n");
        return 0;
    }
    else if ((insert_index < 0) || (insert_index > size))
    {
        fprintf(stderr, "Number is invalid.\n");
        return 0;
    }
    //
    Book new_book;
    enter_book_details(&new_book);

    if (insert_book_by_index(&books, &size, new_book, insert_index))
    {
        printf("\nArray after insertion:\n");
        display_books(size, books);
    }
    else
    {
        printf("Failed to insert new book.\n");
    }

    int delete_index;
    printf("Enter deletion index: ");
    // delete index int verify
    if (scanf("%d", &delete_index) != 1)
    {
        fprintf(stderr, "Invalid input. Size should be an integer.\n");
        return 0;
    }
    else if ((delete_index < 0) || (delete_index > size))
    {
        fprintf(stderr, "Number is invalid.\n");
        return 0;
    }
    //
    if (delete_book_at_index(&books, &size, delete_index))
    {
        printf("\nArray after deletion:\n");
        display_books(size, books);
    }
    else
    {
        printf("Failed to delete book at index %d.\n", delete_index);
    }

    free(books);

    return 0;
}
