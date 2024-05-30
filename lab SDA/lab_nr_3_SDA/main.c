#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;


Node *create_node(int key) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


Node *insert_node(Node *root, int key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->key) {
        root->left = insert_node(root->left, key);
    } else if (key > root->key) {
        root->right = insert_node(root->right, key);
    }
    return root;
}


void preorder_traversal(Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}


int calculate_depth(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int left_depth = calculate_depth(root->left);
    int right_depth = calculate_depth(root->right);
    return (left_depth > right_depth) ? left_depth + 1 : right_depth + 1;
}


Node *search_node(Node *root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (root->key < key) {
        return search_node(root->right, key);
    }
    return search_node(root->left, key);
}


int calculate_height(Node *node) {
    if (node == NULL) {
        return -1;
    }
    int left_height = calculate_height(node->left);
    int right_height = calculate_height(node->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}


void print_leaves(Node *root) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            printf("%d ", root->key);
        }
        print_leaves(root->left);
        print_leaves(root->right);
    }
}


void free_tree(Node *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}


void menu() {
    printf("\n1. Insert node into tree\n");
    printf("2. Print tree in preorder\n");
    printf("3. Calculate tree depth\n");
    printf("4. Search node in tree\n");
    printf("5. Calculate node height in tree\n");
    printf("6. Print tree leaves\n");
    printf("7. Clear tree\n");
    printf("8. Free tree memory\n");
    printf("9. Exit\n");
}

int main() {
    Node *root = NULL;
    int choice, key;

    while (1) {
        menu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key for the new node: ");
                scanf("%d", &key);
                root = insert_node(root, key);
                break;
            case 2:
                printf("Tree in preorder: ");
                preorder_traversal(root);
                printf("\n");
                break;
            case 3:
                printf("Depth of the tree: %d\n", calculate_depth(root));
                break;
            case 4:
                printf("Enter the search key: ");
                scanf("%d", &key);
                if (search_node(root, key) != NULL) {
                    printf("Node with key %d was found in the tree.\n", key);
                } else {
                    printf("Node with key %d was not found in the tree.\n", key);
                }
                break;
            case 5:
                printf("Enter the key to calculate node height: ");
                scanf("%d", &key);
                Node *node = search_node(root, key);
                if (node != NULL) {
                    printf("Height of node with key %d is: %d\n", key, calculate_height(node));
                } else {
                    printf("Node with key %d was not found in the tree.\n", key);
                }
                break;
            case 6:
                printf("Tree leaves: ");
                print_leaves(root);
                printf("\n");
                break;
            case 7:
                root = NULL;
                break;
            case 8:
                free_tree(root);
                root = NULL;
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
