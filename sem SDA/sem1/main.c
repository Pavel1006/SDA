#include <stdio.h>

#define MAX_SIZE 100

int main()
{
    FILE *file = fopen("sales.csv", "r");
    if (file == NULL)
    {
        printf("Nu am putut deschide fisierul!");
        return 1;
    }

    int id;
    char first_name[MAX_SIZE], last_name[MAX_SIZE];
    int age;

    while (fscanf(file, "%d,%[^,],%[^,],%d\n", &id, first_name, last_name, &age) == 4)
    {
        printf("ID: %d, Nume: %s, Prenume: %s, Varsta: %d\n", id, first_name, last_name, age);
    }

    fclose(file);
    // printf("vfbfg");
    return 0;
}