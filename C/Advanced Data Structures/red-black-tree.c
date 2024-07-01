#include <stdio.h>
#include <stdlib.h>

// Node structure for Red-Black Tree
typedef enum { RED, BLACK } node_color;

typedef struct Node {
    int data;
    node_color color;
    struct Node *left, *right, *parent;
} Node;

// Function prototypes
Node* createNode(int data);
void inorder(Node* root);
void fixViolation(Node** root, Node* newNode);
void rotateLeft(Node** root, Node* x);
void rotateRight(Node** root, Node* x);
void insert(Node** root, int data);

// Helper function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED; // New nodes are always RED
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function to do inorder traversal of Red-Black Tree
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Function to fix the Red-Black Tree violations after insertion
void fixViolation(Node** root, Node* newNode) {
    Node* parent = NULL;
    Node* grandparent = NULL;

    while (newNode != *root && newNode->color == RED && newNode->parent->color == RED) {
        parent = newNode->parent;
        grandparent = parent->parent;

        // Case 1: Parent is left child of grandparent
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            // Case 1.1: Uncle is RED, only recoloring required
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                // Case 1.2: Uncle is BLACK or NULL, rotation(s) required
                if (newNode == parent->right) {
                    rotateLeft(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rotateRight(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                newNode = parent;
            }
        } else { // Case 2: Parent is right child of grandparent (mirror of case 1)
            Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == parent->left) {
                    rotateRight(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rotateLeft(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                newNode = parent;
            }
        }
    }

    (*root)->color = BLACK; // Root always black
}

// Left rotation
void rotateLeft(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right rotation
void rotateRight(Node** root, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Insertion into Red-Black Tree
void insert(Node** root, int data) {
    Node* newNode = createNode(data);
    Node* parent = NULL;
    Node* current = *root;

    // Find the appropriate position for the new node
    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    // Set parent for the new node
    newNode->parent = parent;

    // If the tree is empty, make newNode as root
    if (parent == NULL)
        *root = newNode;
    else if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    // Fix Red-Black Tree violations
    fixViolation(root, newNode);
}

// Driver program
int main() {
    Node* root = NULL;

    // Insert nodes into the Red-Black Tree
    insert(&root, 7);
    insert(&root, 3);
    insert(&root, 18);
    insert(&root, 10);
    insert(&root, 22);
    insert(&root, 8);
    insert(&root, 11);

    // Print inorder traversal of the Red-Black Tree
    printf("Inorder traversal of the Red-Black Tree: ");
    inorder(root);
    printf("\n");

    return 0;
}
