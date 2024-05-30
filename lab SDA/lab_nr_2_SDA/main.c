#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Student
{
    char name[50];
    int age;
    float average_grade;
    char specialization[50];
    char faculty[50];
};

struct Node
{
    struct Student student;
    struct Node *next;
};

void read_student(struct Student *student)
{
    printf("Enter student's name: ");
    scanf("%s", student->name);

    printf("Enter student's age: ");
    while (scanf("%d", &student->age) != 1 || student->age < 0 || student->age > 150)
    {
        printf("Invalid input! Please enter a valid age: ");
        while (getchar() != '\n')
            ;
    }

    printf("Enter student's average grade: ");
    while (scanf("%f", &student->average_grade) != 1 || student->average_grade < 0 || student->average_grade > 10)
    {
        printf("Invalid input! Please enter a valid average grade: ");
        while (getchar() != '\n')
            ;
    }

    printf("Enter student's specialization: ");
    scanf("%s", student->specialization);

    printf("Enter student's faculty: ");
    scanf("%s", student->faculty);
}

void print_student(struct Student student)
{
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("Average grade: %.2f\n", student.average_grade);
    printf("Specialization: %s\n", student.specialization);
    printf("Faculty: %s\n", student.faculty);
}

void free_list(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL)
    {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void print_list(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL)
    {
        print_student(current->student);
        printf("\n");
        current = current->next;
    }
}

void insert_beginning(struct Node **head, struct Student student)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL)
    {
        printf("Memory allocation error!");
        return;
    }
    new_node->student = student;
    new_node->next = *head;
    *head = new_node;
}

void insert_end(struct Node **head, struct Student student, int *length_list)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL)
    {
        printf("Memory allocation error!");
        return;
    }
    new_node->student = student;
    new_node->next = NULL;
    if (*head == NULL)
    {
        (*length_list)++;
        *head = new_node;
        return;
    }
    struct Node *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
        (*length_list)++;
    }
    current->next = new_node;
}

int search_student(struct Node *head, char *name)
{
    struct Node *current = head;
    int position = 0;
    while (current != NULL)
    {
        if (strcmp(current->student.name, name) == 0)
        {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1; // returns -1 if student is not found
}

void delete_student(struct Node **head, int position)
{
    if (*head == NULL)
    {
        return;
    }
    struct Node *temp = *head;
    if (position == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)
    {
        return;
    }
    struct Node *next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

void reverse_list(struct Node **head)
{
    struct Node *prev = NULL;
    struct Node *current = *head;
    struct Node *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void clear_list(struct Node **head)
{
    free_list(*head);
    *head = NULL;
}

int main()
{
    int length_list = 0;
    struct Node *list = NULL;
    int option;
    do
    {
        printf("\nMenu:\n");
        printf("1. Add student\n");
        printf("2. Print list\n");
        printf("3. Search student\n");
        printf("4. Delete student\n");
        printf("5. Reverse list\n");
        printf("6. Clear list\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
        {
            struct Student student;
            read_student(&student);
            insert_end(&list, student, &length_list);
            break;
        }
        case 2:
        {
            printf("\nList of students:\n");
            print_list(list);
            break;
        }
        case 3:
        {
            char name[50];
            printf("Enter student's name to search: ");
            scanf("%s", name);
            int position = search_student(list, name);
            if (position != -1)
            {
                printf("Student %s found at position %d.\n", name, position);
            }
            else
            {
                printf("Student %s not found in the list.\n", name);
            }
            break;
        }
        case 4:
        {
            int position;
            printf("Enter position of student to delete: ");

            while ((scanf("%d", &position) != 1) || (position < 0) || (position > length_list))
            {
                printf("Invalid input! Please enter a valid position: ");
                while (getchar() != '\n')
                    ;
            }

            delete_student(&list, position);
            printf("Student deleted successfully.\n");
            break;
        }
        case 5:
        {
            reverse_list(&list);
            printf("List reversed successfully.\n");
            break;
        }
        case 6:
        {
            clear_list(&list);
            printf("List cleared successfully.\n");
            break;
        }
        case 0:
        {
            printf("Exiting program.\n");
            break;
        }
        default:
            printf("Invalid option!\n");
        }
    } while (option != 0);
    

    return 0;
}
