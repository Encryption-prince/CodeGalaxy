#include <stdio.h>
#include <stdlib.h>

#define T 3

// B-Tree node structure
struct BTreeNode {
    int *keys;      // Array of keys
    struct BTreeNode **children; // Array of child pointers
    int n;          // Current number of keys
    int leaf;       // Is true if node is a leaf, false otherwise
};

// Function prototypes
void splitChild(struct BTreeNode *parent, int i);
void insertNonFull(struct BTreeNode *node, int key);

// Function to create a new B-Tree node
struct BTreeNode *createNode(int leaf) {
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->leaf = leaf;
    newNode->keys = (int *)malloc(sizeof(int) * (2*T - 1));
    newNode->children = (struct BTreeNode **)malloc(sizeof(struct BTreeNode *) * (2*T));
    newNode->n = 0;
    return newNode;
}

// Function to search key in a B-Tree rooted with this node
void search(struct BTreeNode *root, int key) {
    int i = 0;
    while (i < root->n && key > root->keys[i]) {
        i++;
    }
    if (root->keys[i] == key) {
        printf("Key %d found in the tree.\n", key);
        return;
    }
    if (root->leaf) {
        printf("Key %d not found in the tree.\n", key);
        return;
    }
    search(root->children[i], key);
}

// Function to traverse all nodes in a subtree rooted with this node
void traverse(struct BTreeNode *root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf) {
            traverse(root->children[i]);
        }
        printf(" %d", root->keys[i]);
    }
    if (!root->leaf) {
        traverse(root->children[i]);
    }
}

// Function to insert a new key in the B-Tree
void insert(struct BTreeNode **root, int key) {
    struct BTreeNode *temp = *root;
    if (temp->n == (2*T - 1)) {
        struct BTreeNode *newNode = createNode(0);
        newNode->children[0] = temp;
        *root = newNode;
        // Split the old root and move one key to the new root
        splitChild(newNode, 0);
        // Insert the key into the B-Tree
        insertNonFull(newNode, key);
    } else {
        // Insert the key into the B-Tree
        insertNonFull(temp, key);
    }
}

// Function to split the child of a node
void splitChild(struct BTreeNode *parent, int i) {
    struct BTreeNode *z = parent->children[i];
    struct BTreeNode *y = parent->children[i];
    struct BTreeNode *x = createNode(y->leaf);
    x->n = T - 1;
    for (int j = 0; j < T - 1; j++) {
        x->keys[j] = y->keys[j + T];
    }
    if (!y->leaf) {
        for (int j = 0; j < T; j++) {
            x->children[j] = y->children[j + T];
        }
    }
    y->n = T - 1;
    for (int j = parent->n; j >= i; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = x;
    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = y->keys[T - 1];
    parent->n++;
}

// Function to insert a new key in the B-Tree
void insertNonFull(struct BTreeNode *node, int key) {
    int i = node->n - 1;
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->n == (2*T - 1)) {
            splitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to create a B-Tree
struct BTreeNode *createBTree() {
    struct BTreeNode *root = createNode(1);
    return root;
}

int main() {
    struct BTreeNode *root = createBTree();

    int keys[] = {3, 7, 1, 8, 5, 2, 9, 4, 6};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insert(&root, keys[i]);
    }

    printf("In-order traversal of B-tree:\n");
    traverse(root);
    printf("\n");

    int searchKey = 6;
    search(root, searchKey);

    return 0;
}
