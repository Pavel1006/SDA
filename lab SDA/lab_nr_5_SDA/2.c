#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(int *arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
}

void display(int *arr, int size)
{
    printf("Array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void freeMemory(int *arr)
{
    free(arr);
}

double linearSearch(int *arr, int size, int key)
{
    clock_t start = clock();

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == key)
        {
            break;
        }
    }

    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double binarySearch(int *arr, int size, int key)
{
    clock_t start = clock();

    int left = 0, right = size - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
        {
            break;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void menu()
{
    printf("\nMenu:\n");
    printf("1. Initialize array\n");
    printf("2. Display array\n");
    printf("3. Free memory\n");
    printf("4. Linear search\n");
    printf("5. Binary search\n");
    printf("6. Exit\n");
}

int main()
{
    int choice, *arr = NULL, size, key;
    double timeTaken;

    do
    {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the size of the array: ");
            scanf("%d", &size);
            arr = (int *)malloc(size * sizeof(int));
            init(arr, size);
            break;
        case 2:
            if (arr != NULL)
            {
                display(arr, size);
            }
            else
            {
                printf("Array is not initialized!\n");
            }
            break;
        case 3:
            if (arr != NULL)
            {
                freeMemory(arr);
                arr = NULL;
                printf("Memory freed successfully!\n");
            }
            else
            {
                printf("Array is not initialized!\n");
            }
            break;
        case 4:
            if (arr != NULL)
            {
                printf("Enter the number to search: ");
                scanf("%d", &key);
                timeTaken = linearSearch(arr, size, key);
                printf("Linear search executed in %.30f seconds\n", timeTaken);
            }
            else
            {
                printf("Array is not initialized!\n");
            }
            break;
        case 5:
            if (arr != NULL)
            {
                printf("Enter the number to search: ");
                scanf("%d", &key);
                timeTaken = binarySearch(arr, size, key);
                printf("Binary search executed in %.30f seconds\n", timeTaken);
            }
            else
            {
                printf("Array is not initialized!\n");
            }
            break;
        case 6:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
