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

double quickSort(int *arr, int low, int high)
{
    clock_t start = clock();

    if (low < high)
    {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (arr[j] <= pivot)
            {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int partitionIndex = i + 1;

        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }

    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double bubbleSort(int *arr, int size)
{
    clock_t start = clock();

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
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
    printf("4. Quick sort\n");
    printf("5. Bubble sort\n");
    printf("6. Exit\n");
}

int main()
{
    int choice, *arr = NULL, size;
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
                timeTaken = quickSort(arr, 0, size - 1);
                printf("Quick sort executed in %.10f seconds\n", timeTaken);
            }
            else
            {
                printf("Array is not initialized!\n");
            }
            break;
        case 5:
            if (arr != NULL)
            {
                timeTaken = bubbleSort(arr, size);
                printf("Bubble sort executed in %.10f seconds\n", timeTaken);
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
