#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    int key;
    char name[50];
    int age;
    float average_grade;
    char specialization[50];
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int key, char name[], int age, float average_grade, char specialization[])
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    strcpy(new_node->name, name);
    new_node->age = age;
    new_node->average_grade = average_grade;
    strcpy(new_node->specialization, specialization);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *insert_node(Node *root, int key, char name[], int age, float average_grade, char specialization[])
{
    if (root == NULL)
    {
        return create_node(key, name, age, average_grade, specialization);
    }
    if (key < root->key)
    {
        root->left = insert_node(root->left, key, name, age, average_grade, specialization);
    }
    else if (key > root->key)
    {
        root->right = insert_node(root->right, key, name, age, average_grade, specialization);
    }
    else
    {
        printf("Key %d already exists in the tree.\n", key);
    }
    return root;
}

void print_node(Node *node)
{
    printf("Key: %d, Name: %s, Age: %d, Average Grade: %.2f, Specialization: %s\n",
           node->key, node->name, node->age, node->average_grade, node->specialization);
}

void inorder_traversal(Node *root)
{
    if (root != NULL)
    {
        inorder_traversal(root->left);
        print_node(root);
        inorder_traversal(root->right);
    }
}

void preorder_traversal(Node *root)
{
    if (root != NULL)
    {
        print_node(root);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void postorder_traversal(Node *root)
{
    if (root != NULL)
    {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        print_node(root);
    }
}

void dfs(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        dfs(root->left);
        dfs(root->right);
    }
}

typedef struct QueueNode
{
    Node *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *create_queue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

bool is_empty(Queue *queue)
{
    return (queue->front == NULL);
}

void enqueue(Queue *queue, Node *data)
{
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    if (new_node == NULL)
    {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = new_node;
        queue->rear = new_node;
    }
    else
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

Node *dequeue(Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue is empty!\n");
        exit(EXIT_FAILURE);
    }
    QueueNode *temp = queue->front;
    Node *data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

void destroy_queue(Queue *queue)
{
    while (!is_empty(queue))
    {
        dequeue(queue);
    }
    free(queue);
}

void bfs(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    Queue *queue = create_queue();
    enqueue(queue, root);

    while (!is_empty(queue))
    {
        Node *current = dequeue(queue);
        print_node(current);
        if (current->left != NULL)
        {
            enqueue(queue, current->left);
        }
        if (current->right != NULL)
        {
            enqueue(queue, current->right);
        }
    }

    destroy_queue(queue);
}

Node *search_node(Node *root, int key)
{
    if (root == NULL || root->key == key)
    {
        return root;
    }
    if (key < root->key)
    {
        return search_node(root->left, key);
    }
    return search_node(root->right, key);
}

void free_tree(Node *root)
{
    if (root != NULL)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void menu()
{
    printf("\n1. Insert node into binary search tree\n");
    printf("2. Print binary search tree in inorder\n");
    printf("3. Print binary search tree in preorder\n");
    printf("4. Print binary search tree in postorder\n");
    printf("5. Depth-First Search (DFS)\n");
    printf("6. Breadth-First Search (BFS)\n");
    printf("7. Search node by key\n");
    printf("8. Exit\n");
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    Node *root = NULL;
    int choice, key, age;
    float average_grade;
    char name[50], specialization[50];

    while (1)
    {
        menu();
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("Enter key, name, age, average grade, specialization for the new node: ");
            if (scanf("%d %49s %d %f %49s", &key, name, &age, &average_grade, specialization) != 5)
            {
                printf("Invalid input. Please enter valid values.\n");
                clear_input_buffer();
                continue;
            }
            root = insert_node(root, key, name, age, average_grade, specialization);
            break;
        case 2:
            printf("Binary search tree in inorder:\n");
            inorder_traversal(root);
            printf("\n");
            break;
        case 3:
            printf("Binary search tree in preorder:\n");
            preorder_traversal(root);
            printf("\n");
            break;
        case 4:
            printf("Binary search tree in postorder:\n");
            postorder_traversal(root);
            printf("\n");
            break;
        case 5:
            printf("Depth-First Search (DFS):\n");
            dfs(root);
            printf("\n");
            break;
        case 6:
            printf("Breadth-First Search (BFS):\n");
            bfs(root);
            printf("\n");
            break;
        case 7:
            printf("Enter the key to search for: ");
            if (scanf("%d", &key) != 1)
            {
                printf("Invalid input. Please enter a number.\n");
                clear_input_buffer();
                continue;
            }
            Node *found_node = search_node(root, key);
            if (found_node != NULL)
            {
                printf("Node found: ");
                print_node(found_node);
            }
            else
            {
                printf("Node with key %d not found.\n", key);
            }
            break;
        case 8:
            free_tree(root);
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
