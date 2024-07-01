#include <stdio.h>
#include <stdlib.h>

// Node structure for AVL Tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int height;
} Node;

// Function prototypes
Node* createNode(int data);
int getHeight(Node* node);
#define max(a,b) (((a) > (b)) ? (a) : (b)) // Macro definition for max function
int getBalance(Node* node);
Node* rotateRight(Node* y);
Node* rotateLeft(Node* x);
Node* insert(Node* node, int data);
void inorder(Node* root);
void freeTree(Node* root); // Utility function to free memory

// Helper function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // New node is initially added at leaf
    return newNode;
}

// Helper function to get height of a node
int getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Helper function to get balance factor of node
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    // Return new root
    return x;
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    // Return new root
    return y;
}

// Insertion into AVL Tree
Node* insert(Node* node, int data) {
    // Perform normal BST insertion
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal keys are not allowed in AVL Tree
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor of this ancestor node to check whether it became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are four cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Inorder traversal of AVL Tree
void inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Utility function to free memory
void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Driver program
int main() {
    Node* root = NULL;

    // Insert nodes into the AVL Tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Print inorder traversal of the AVL Tree
    printf("Inorder traversal of the AVL Tree: ");
    inorder(root);
    printf("\n");

    // Free memory allocated for the AVL Tree
    freeTree(root);

    return 0;
}
