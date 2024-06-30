#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the binary search tree
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

// Function to insert a new node into the binary search tree
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

// Function to search for a node with given data in the binary search tree
struct TreeNode* search(struct TreeNode *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// Function to find the minimum element in the binary search tree
struct TreeNode* findMin(struct TreeNode *root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to find the maximum element in the binary search tree
struct TreeNode* findMax(struct TreeNode *root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Function to perform inorder traversal of the binary search tree
void inorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to delete a node with given data from the binary search tree
struct TreeNode* deleteNode(struct TreeNode *root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // Case 2: Node with two children
        struct TreeNode *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to free memory allocated to the binary search tree nodes
void freeBinarySearchTree(struct TreeNode *root) {
    if (root != NULL) {
        freeBinarySearchTree(root->left);
        freeBinarySearchTree(root->right);
        free(root);
    }
}

int main() {
    struct TreeNode *root = NULL; // Initialize an empty binary search tree

    // Insert nodes into the binary search tree
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

    // Search for a node in the binary search tree
    int searchData = 30;
    struct TreeNode *searchResult = search(root, searchData);
    if (searchResult != NULL) {
        printf("%d found in the tree.\n", searchData);
    } else {
        printf("%d not found in the tree.\n", searchData);
    }

    // Find minimum and maximum elements in the binary search tree
    struct TreeNode *minNode = findMin(root);
    struct TreeNode *maxNode = findMax(root);
    if (minNode != NULL) {
        printf("Minimum element in the tree: %d\n", minNode->data);
    }
    if (maxNode != NULL) {
        printf("Maximum element in the tree: %d\n", maxNode->data);
    }

    // Delete a node from the binary search tree
    int deleteData = 30;
    root = deleteNode(root, deleteData);
    printf("Deleted node with data %d from the tree.\n", deleteData);

    // Perform inorder traversal after deletion and display nodes
    printf("Inorder traversal after deletion: ");
    inorderTraversal(root);
    printf("\n");

    // Free memory allocated to the binary search tree nodes
    freeBinarySearchTree(root);

    return 0;
}
