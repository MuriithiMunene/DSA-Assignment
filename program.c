#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the Binary Search Tree (BST)
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *newNode(int data) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node into the BST
struct Node *insertNode(struct Node *root, int data) {
    if (root == NULL)
        return newNode(data);
    
    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    
    return root;
}

// Function to delete a node from the BST
struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return root;
    
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        
        struct Node *temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the height of the BST
int height(struct Node *root) {
    if (root == NULL)
        return -1;
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Function to print the level and height of a node in the BST
void printLevelAndHeight(struct Node *root, int data, int level) {
    if (root == NULL)
        return;
    
    if (root->data == data) {
        printf("Level of node %d is: %d\n", data, level);
        printf("Height of node %d is: %d\n", data, height(root));
    } else if (data < root->data)
        printLevelAndHeight(root->left, data, level + 1);
    else
        printLevelAndHeight(root->right, data, level + 1);
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    struct Node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insertNode(root, arr[i]);
    
    printf("BST created successfully.\n");
    
    // Deleting node with value 10
    root = deleteNode(root, 10);
    
    printf("Node with value 10 deleted successfully.\n");
    
    // Printing the height of the BST
    printf("Height of the BST is: %d\n", height(root));
    
    // Printing the level and height of node with value 20
    printLevelAndHeight(root, 20, 0);
    
    return 0;
}

