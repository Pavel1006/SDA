#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

typedef struct Document
{
    int id;
    char name[50];
    int total_lines;
    int remaining_lines;
    struct Document *next;
} Document;

typedef struct Printer
{
    int id;
    int printing_time_per_line;
    Document *current_document;
    bool functional;
    struct Printer *next;
} Printer;

typedef struct PrintedDocumentInfo
{
    int printer_id;
    char document_name[50];
} PrintedDocumentInfo;

Printer *initializePrinters(int num_printers)
{
    Printer *head = NULL;
    Printer *temp = NULL;

    srand(time(NULL));

    for (int i = 0; i < num_printers; i++)
    {
        Printer *printer = (Printer *)malloc(sizeof(Printer));
        printer->id = i + 1;
        printer->printing_time_per_line = rand() % 5 + 1;
        printer->current_document = NULL;
        printer->functional = true;
        printer->next = NULL;

        if (head == NULL)
        {
            head = printer;
            temp = printer;
        }
        else
        {
            temp->next = printer;
            temp = temp->next;
        }
    }

    return head;
}

void enqueueDocument(Document **queue, int id, char *name, int total_lines)
{
    Document *newDocument = (Document *)malloc(sizeof(Document));
    newDocument->id = id;
    strcpy(newDocument->name, name);
    newDocument->total_lines = total_lines;
    newDocument->remaining_lines = total_lines;
    newDocument->next = NULL;

    if (*queue == NULL)
    {
        *queue = newDocument;
    }
    else
    {
        Document *temp = *queue;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newDocument;
    }
}

void generateRandomDocuments(Document **queue, int num_documents)
{
    for (int i = 0; i < num_documents; i++)
    {
        char name[50];
        sprintf(name, "Document%d", i + 1);
        int total_lines = rand() % 10 + 1;
        enqueueDocument(queue, i + 1, name, total_lines);
    }
}

void distributeDocuments(Document **queue, Printer **printers)
{
    while (*queue != NULL)
    {
        int min_wait_time = INT_MAX;
        Printer *selectedPrinter = NULL;
        Printer *tempPrinter = *printers;

        while (tempPrinter != NULL)
        {
            if (tempPrinter->current_document == NULL && tempPrinter->functional)
            {
                int wait_time = tempPrinter->printing_time_per_line * (*queue)->remaining_lines;
                if (wait_time < min_wait_time)
                {
                    min_wait_time = wait_time;
                    selectedPrinter = tempPrinter;
                }
            }
            tempPrinter = tempPrinter->next;
        }

        if (selectedPrinter != NULL)
        {
            selectedPrinter->current_document = *queue;
            *queue = (*queue)->next;
        }
        else
        {
            break;
        }
    }
}

void updateState(Printer **printers, int *time_elapsed, PrintedDocumentInfo *printedDocuments, int *num_printed_docs, Document **queue)
{
    Printer *tempPrinter = *printers;
    bool all_documents_printed = true;
    bool all_printers_faulty = true;

    while (tempPrinter != NULL)
    {
        if (tempPrinter->functional)
        {
            all_printers_faulty = false;

            if (tempPrinter->current_document != NULL)
            {
                all_documents_printed = false;

                tempPrinter->current_document->remaining_lines -= 1;
                if (tempPrinter->current_document->remaining_lines == 0)
                {

                    printedDocuments[*num_printed_docs].printer_id = tempPrinter->id;
                    strcpy(printedDocuments[*num_printed_docs].document_name, tempPrinter->current_document->name);
                    (*num_printed_docs)++;

                    free(tempPrinter->current_document);
                    tempPrinter->current_document = NULL;
                }
            }
        }
        tempPrinter = tempPrinter->next;
    }

    distributeDocuments(queue, printers);

    if (!all_documents_printed && !all_printers_faulty)
    {
        (*time_elapsed)++;
    }
}

void printStatus(Document *queue, Printer *printers)
{
    printf("Printing Queue:\n");
    Document *tempDoc = queue;
    while (tempDoc != NULL)
    {
        printf("Document ID: %d, Name: %s, Remaining Lines: %d\n", tempDoc->id, tempDoc->name, tempDoc->remaining_lines);
        tempDoc = tempDoc->next;
    }

    printf("\nPrinters:\n");
    Printer *tempPrinter = printers;
    while (tempPrinter != NULL)
    {
        printf("Printer ID: %d, Current Document: %s, Status: %s\n", tempPrinter->id, tempPrinter->current_document != NULL ? tempPrinter->current_document->name : "None", tempPrinter->functional ? "Functional" : "Faulty");
        tempPrinter = tempPrinter->next;
    }
}

void freeDocuments(Document **queue)
{
    Document *temp = *queue;
    while (*queue != NULL)
    {
        temp = *queue;
        *queue = (*queue)->next;
        free(temp);
    }
}

void freePrinters(Printer **printers)
{
    Printer *temp = *printers;
    while (*printers != NULL)
    {
        temp = *printers;
        *printers = (*printers)->next;
        free(temp);
    }
}

int main()
{
    int num_printers = 3;
    int num_of_documents = 100;
    Printer *printers = initializePrinters(num_printers);

    Document *queue = NULL;
    generateRandomDocuments(&queue, num_of_documents);

    printf("Initial Printers:\n");
    Printer *tempPrinter = printers;
    while (tempPrinter != NULL)
    {
        printf("Printer ID: %d, Printing Time Per Line: %d, Functional: %s\n", tempPrinter->id, tempPrinter->printing_time_per_line, tempPrinter->functional ? "Yes" : "No");
        tempPrinter = tempPrinter->next;
    }
    printf("\n");

    printf("Initial Documents Queue:\n");
    Document *tempDoc = queue;
    while (tempDoc != NULL)
    {
        printf("Document ID: %d, Name: %s, Total Lines: %d\n", tempDoc->id, tempDoc->name, tempDoc->total_lines);
        tempDoc = tempDoc->next;
    }
    printf("\n");

    distributeDocuments(&queue, &printers);
    printStatus(queue, printers);
    printf("\n");

    int time_elapsed = 0;
    // este egal cu nr total de documente
    PrintedDocumentInfo printedDocuments[100];
    int num_printed_docs = 0;

    while (true)
    {
        updateState(&printers, &time_elapsed, printedDocuments, &num_printed_docs, &queue);
        printStatus(queue, printers);
        printf("\n");

        bool all_documents_printed = true;
        Document *tempDoc = queue;
        while (tempDoc != NULL)
        {
            if (tempDoc->remaining_lines > 0)
            {
                all_documents_printed = false;
                break;
            }
            tempDoc = tempDoc->next;
        }

        bool all_printers_faulty = true;
        Printer *tempPrinter = printers;
        while (tempPrinter != NULL)
        {
            if (tempPrinter->functional)
            {
                all_printers_faulty = false;
                break;
            }
            tempPrinter = tempPrinter->next;
        }

        if (all_documents_printed || all_printers_faulty)
        {
            break;
        }
    }

    printf("Time elapsed: %d iteration\n", time_elapsed);

    printf("\nPrinted Documents:\n");
    for (int i = 0; i < num_printed_docs; i++)
    {
        printf("Printer ID: %d, Document Name: %s\n", printedDocuments[i].printer_id, printedDocuments[i].document_name);
    }

    freeDocuments(&queue);
    freePrinters(&printers);

    return 0;
}
