#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct magazine
{
    int id_product;
    float unit_price;
    int quantity;
    int day;
    int month;
    int year;
    float total_income;
    char product_name[100];
    char product_category[100];
    char country[100];
    char city[100];
    char sub_category[100];
    char date[10];
    float total_month[12];
    int total_sales;
    char group[100];
    int check;
    int transaction_number;
    char key[100];
} Magazine;

void max_sales_city_per_country(Magazine *m, int size)
{
    int count = 0;
    int new_size = 0;
    Magazine *n = malloc(new_size * sizeof(Magazine));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < new_size; j++)
        {
            if (strcmp(m[i].country, n[j].country) == 0)
            {
                count++;
            }
        }

        if (count == 0)
        {
            new_size++;
            n = realloc(n, new_size * sizeof(Magazine));
            n[new_size - 1] = m[i];
        }

        count = 0;
    }

    for (int i = 0; i < new_size; i++)
    {
        n[i].total_sales = 0;
        n[i].city[0] = '\0';
    }

    for (int i = 0; i < new_size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (strcmp(n[i].country, m[j].country) == 0)
            {
                if (m[j].quantity > n[i].total_sales)
                {
                    n[i].total_sales = m[j].quantity;
                    strcpy(n[i].city, m[j].city);
                }
            }
        }
    }

    printf("\n\nCity with the most sales for each country: \n\n");
    for (int i = 0; i < new_size - 1; i++)
    {
        printf("%s, %s :   %d sales\n", n[i].country, n[i].city, n[i].total_sales);
    }

    free(n);
}

int Import(Magazine **m, FILE *file)
{
    int size = 10000;
    int counter = 0;
    char line[1000];

    fgets(line, sizeof(line), file);

    while (fscanf(file, "%d-%d-%d,%d,%99[^,],%99[^,],%99[^,],%f,%d,%99[^,],%99[^\n]\n", &(*m)[counter].year, &(*m)[counter].month, &(*m)[counter].day,
                  &(*m)[counter].id_product, (*m)[counter].product_name, (*m)[counter].product_category, (*m)[counter].sub_category,
                  &(*m)[counter].unit_price, &(*m)[counter].quantity, (*m)[counter].country, (*m)[counter].city) == 11)
    {

        if (counter >= size)
        {
            size = size * 2;
            *m = realloc(*m, size * sizeof(Magazine));
        }

        (*m)[counter].total_income = (*m)[counter].unit_price * (*m)[counter].quantity;

        counter++;
    }

    return counter;
}

void month_income(Magazine **m, int counter)
{
    int j = 0;
    int year;
    printf("\nWhich year are you interested in?\n");
    scanf("%d", &year);
    for (int i = 0; i < 12; i++)
    {
        (*m)->total_month[i] = 0;
        for (int j = 0; j < counter; j++)
        {
            if ((*m)[j].month == i + 1 && (*m)[j].year == year)
            {
                (*m)->total_month[i] += (*m)[j].total_income;
                j++;
            }
        }
    }
    printf("Month,Total Income\n");

    for (int i = 0; i < 12; i++)
    {
        printf("%d,%.2f\n", i + 1, (*m)->total_month[i]);
    }
}

void sales_distribution(Magazine **m, int size)
{
    int count = 0;
    int new_size = 0;

    Magazine *n = malloc(new_size * sizeof(Magazine));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < new_size; j++)
        {
            if (strcmp((*m)[i].product_category, n[j].product_category) == 0)
            {
                count++;
            }
        }

        if (count == 0)
        {
            new_size++;
            n = realloc(n, new_size * sizeof(Magazine));
            n[new_size - 1] = (*m)[i];
        }

        count = 0;
    }

    for (int i = 0; i < new_size; i++)
    {
        n[i].total_sales = 0;
    }

    for (int i = 0; i < new_size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (strcmp(n[i].product_category, (*m)[j].product_category) == 0)
            {
                n[i].total_sales += (*m)[j].quantity;
            }
        }
    }

    printf("\n\nCategories: \n");

    for (int i = 0; i < new_size - 1; i++)
    {
        printf("%d. %s :   %d sales\n", i + 1, n[i].product_category, n[i].total_sales);
    }
}

void best_income(Magazine **m, int size)
{
    int count = 0;
    int new_size = 0;
    Magazine *n = malloc(new_size * sizeof(Magazine));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < new_size; j++)
        {
            if (strcmp((*m)[i].product_name, n[j].product_name) == 0)
            {
                count++;
            }
        }

        if (count == 0)
        {
            new_size++;
            n = realloc(n, new_size * sizeof(Magazine));
            n[new_size - 1] = (*m)[i];
        }

        count = 0;
    }

    for (int i = 0; i < new_size; i++)
    {
        n[i].total_income = 0;
    }

    for (int i = 0; i < new_size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (strcmp(n[i].product_name, (*m)[j].product_name) == 0)
            {
                n[i].total_income += (*m)[j].unit_price * (*m)[j].quantity;
            }
        }
    }

    Magazine temp;
    for (int i = 0; i < new_size; i++)
    {
        for (int j = 0; j < new_size - 1; j++)
        {
            if (n[j].total_income < n[j + 1].total_income)
            {
                temp = n[j];
                n[j] = n[j + 1];
                n[j + 1] = temp;
            }
        }
    }

    printf("\n\nTop 5 products: \n");
    for (int i = 0; i < 5 && i < new_size; i++)
    {
        printf("%d. %s :   %.2f\n", i + 1, n[i].product_name, n[i].total_income);
    }

    free(n);
}

void tendinte_vanzari_lunare(Magazine **m, int counter)
{
    float total_sales_per_month[12] = {0};
    int num_products_per_month[12] = {0};

    int year;
    printf("\nWhich year are you interested in?\n");
    scanf("%d", &year);

    for (int i = 0; i < counter; i++)
    {
        if ((*m)[i].year == year)
        {
            total_sales_per_month[(*m)[i].month - 1] += (*m)[i].total_income;
            num_products_per_month[(*m)[i].month - 1]++;
        }
    }

    float temp, percent;
    printf("\n\nTrends in monthly sales for different product categories:\n\n");
    for (int i = 0; i < 12; i++)
    {
        printf("Month %d:\n", i + 1);

        if (i == 0)
        {
            printf("  Total sales: %f\n", total_sales_per_month[i]);

            temp = total_sales_per_month[i + 1] - total_sales_per_month[i];

            if (temp > 0)
            {
                percent = 100 * (total_sales_per_month[i + 1] - total_sales_per_month[i]) / total_sales_per_month[i];
            }
            else if (temp < 0)
            {
                percent = -100 * (1 - total_sales_per_month[i + 1] / total_sales_per_month[i]);
            }

            continue;
        }

        printf("  Total sales: %f\n", total_sales_per_month[i]);
        printf("  Percentage change: %.2f %%\n", percent);

        temp = total_sales_per_month[i + 1] - total_sales_per_month[i];

        if (temp > 0)
        {
            percent = 100 * (total_sales_per_month[i + 1] - total_sales_per_month[i]) / total_sales_per_month[i];
        }
        else if (temp < 0)
        {
            percent = -100 * (1 - total_sales_per_month[i + 1] / total_sales_per_month[i]);
        }
    }
}

int main()
{
    FILE *file = fopen("sales.csv", "r");

    int size = 10000;
    Magazine *m = malloc(size * sizeof(Magazine));

    int counter = 0;
    counter = Import(&m, file);
    int choice;

    fclose(file);

    while (1)
    {
        printf("\n1: Total income generated per month\n");
        printf("2: Top 5 products by income\n");
        printf("3: Sales distribution by product category\n");
        printf("4: City with the most sales from each country\n");
        printf("5: Sales trends\n");
        printf("6: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            month_income(&m, counter);
            break;
        case 2:
            best_income(&m, counter);
            break;
        case 3:
            sales_distribution(&m, counter);
            break;
        case 4:
            max_sales_city_per_country(m, counter);
            break;
        case 5:
            tendinte_vanzari_lunare(&m, counter);
            break;
        case 6:
            free(m);
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
