#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the binary tree
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node with given data
struct TreeNode* createNode(int data) {
    struct TreeNode *newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the binary tree
struct TreeNode* insertNode(struct TreeNode *root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else {
        if (data <= root->data) {
            root->left = insertNode(root->left, data);
        } else {
            root->right = insertNode(root->right, data);
        }
    }
    return root;
}

// Function to perform inorder traversal of the binary tree
void inorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to perform preorder traversal of the binary tree
void preorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to perform postorder traversal of the binary tree
void postorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Function to free memory allocated to the binary tree nodes
void freeBinaryTree(struct TreeNode *root) {
    if (root != NULL) {
        freeBinaryTree(root->left);
        freeBinaryTree(root->right);
        free(root);
    }
}

int main() {
    struct TreeNode *root = NULL; // Initialize an empty binary tree

    // Insert nodes into the binary tree
    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 70);
    root = insertNode(root, 60);
    root = insertNode(root, 80);

    // Perform inorder traversal and display nodes
    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Perform preorder traversal and display nodes
    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    // Perform postorder traversal and display nodes
    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");

    // Free memory allocated to the binary tree nodes
    freeBinaryTree(root);

    return 0;
}
