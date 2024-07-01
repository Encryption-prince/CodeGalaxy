#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100 // Maximum length of the input string

// Suffix tree node structure
struct SuffixTreeNode {
    struct SuffixTreeNode *children[256]; // Assuming ASCII characters
};

// Function to create a new suffix tree node
struct SuffixTreeNode* createNode() {
    struct SuffixTreeNode* node = (struct SuffixTreeNode*) malloc(sizeof(struct SuffixTreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 256; ++i) {
        node->children[i] = NULL;
    }
    return node;
}

// Function to insert a suffix into the suffix tree
void insertSuffix(struct SuffixTreeNode *root, const char *suffix) {
    struct SuffixTreeNode *current = root;
    for (int i = 0; suffix[i] != '\0'; ++i) {
        int index = (unsigned char)suffix[i];
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
}

// Function to build the suffix tree for a given string
struct SuffixTreeNode* buildSuffixTree(const char *text) {
    // Calculate the length of text safely
    size_t n = strnlen(text, MAX_LEN);
    
    struct SuffixTreeNode *root = createNode();
    
    // Insert all suffixes into the suffix tree
    for (size_t i = 0; i < n; ++i) {
        insertSuffix(root, text + i);
    }
    
    return root;
}

// Function to search for a pattern in the suffix tree
int searchPattern(struct SuffixTreeNode *root, const char *pattern) {
    struct SuffixTreeNode *current = root;
    for (int i = 0; pattern[i] != '\0'; ++i) {
        int index = (unsigned char)pattern[i];
        if (!current->children[index]) {
            return 0; // Pattern not found
        }
        current = current->children[index];
    }
    return 1; // Pattern found
}

// Function to free memory allocated for the suffix tree
void freeSuffixTree(struct SuffixTreeNode *root) {
    if (!root) return;
    for (int i = 0; i < 256; ++i) {
        freeSuffixTree(root->children[i]);
    }
    free(root);
}

int main() {
    char *text = (char *)malloc(MAX_LEN + 1);
    if (!text) {
        fprintf(stderr, "Memory allocation for text failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (!fgets(text, MAX_LEN + 1, stdin)) {
        fprintf(stderr, "Error reading input string.\n");
        free(text);
        return EXIT_FAILURE;
    }
    text[strcspn(text, "\n")] = '\0'; // Remove newline character if present

    // Build suffix tree
    struct SuffixTreeNode *root = buildSuffixTree(text);

    char *pattern = (char *)malloc(MAX_LEN + 1);
    if (!pattern) {
        fprintf(stderr, "Memory allocation for pattern failed.\n");
        free(text);
        freeSuffixTree(root);
        return EXIT_FAILURE;
    }

    printf("Enter a pattern to search: ");
    if (!fgets(pattern, MAX_LEN + 1, stdin)) {
        fprintf(stderr, "Error reading pattern.\n");
        free(text);
        free(pattern);
        freeSuffixTree(root);
        return EXIT_FAILURE;
    }
    pattern[strcspn(pattern, "\n")] = '\0'; // Remove newline character if present

    if (searchPattern(root, pattern)) {
        printf("Pattern '%s' found in the string.\n", pattern);
    } else {
        printf("Pattern '%s' not found in the string.\n", pattern);
    }

    // Free memory allocated for text, pattern, and suffix tree
    free(text);
    free(pattern);
    freeSuffixTree(root);

    return 0;
}
