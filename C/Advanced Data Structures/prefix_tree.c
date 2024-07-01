#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};

// Function to create a new Trie node
struct TrieNode *createNode() {
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    newNode->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to insert a word into the Trie
void insert(struct TrieNode *root, const char *word) {
    struct TrieNode *current = root;
    
    // Calculate the length of the word manually
    int len = 0;
    while (word[len] != '\0') {
        len++;
    }
    
    // Iterate through each character of the word
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    
    // Mark the end of the word in the Trie
    current->isEndOfWord = 1;
}

// Function to search for a word in the Trie
int search(struct TrieNode *root, const char *word) {
    struct TrieNode *current = root;
    
    // Calculate the length of the word manually
    int len = 0;
    while (word[len] != '\0') {
        len++;
    }
    
    // Iterate through each character of the word
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    
    // Check if the end of the word is reached in the Trie
    return (current != NULL && current->isEndOfWord);
}

// Function to delete a word from the Trie
int delete(struct TrieNode *root, const char *word) {
    struct TrieNode *current = root;
    
    // Calculate the length of the word manually
    int len = 0;
    while (word[len] != '\0') {
        len++;
    }
    
    // Allocate memory for the stack
    struct TrieNode **stack = (struct TrieNode **)malloc(len * sizeof(struct TrieNode *));
    if (stack == NULL) {
        return 0; // Memory allocation failed
    }
    
    int top = -1;

    // Traverse till the end of the word
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            free(stack); // Free allocated memory
            return 0; // Word not found
        }
        stack[++top] = current;
        current = current->children[index];
    }

    // If the end of word flag is not set, word doesn't exist in Trie
    if (!current->isEndOfWord) {
        free(stack); // Free allocated memory
        return 0; // Word not found
    }

    // Remove end of word flag
    current->isEndOfWord = 0;

    // If current node has no other children, delete nodes till a node has more children or isEndOfWord is set
    while (top >= 0) {
        current = stack[top--];
        int i;
        for (i = 0; i < ALPHABET_SIZE; i++) {
            if (current->children[i] != NULL) {
                break;
            }
        }
        if (i < ALPHABET_SIZE || current->isEndOfWord) {
            break;
        }
        free(current);
    }
    
    free(stack); // Free allocated memory
    return 1; // Word deleted successfully
}

// Function to free memory allocated for Trie nodes
void freeTrie(struct TrieNode *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freeTrie(root->children[i]);
    }
    free(root);
}

// Function to demonstrate Trie operations
void demonstrateTrie() {
    struct TrieNode *root = createNode();

    // Insert words into the Trie
    insert(root, "hello");
    insert(root, "world");
    insert(root, "hi");
    insert(root, "hey");

    // Search for words in the Trie
    printf("Searching for 'hello': %s\n", search(root, "hello") ? "Found" : "Not Found");
    printf("Searching for 'world': %s\n", search(root, "world") ? "Found" : "Not Found");
    printf("Searching for 'hi': %s\n", search(root, "hi") ? "Found" : "Not Found");
    printf("Searching for 'openai': %s\n", search(root, "openai") ? "Found" : "Not Found");

    // Delete a word from the Trie
    printf("Deleting 'hello' from Trie...\n");
    if (delete(root, "hello")) {
        printf("'hello' deleted successfully.\n");
    } else {
        printf("'hello' not found in Trie.\n");
    }

    // Search for 'hello' after deletion
    printf("Searching for 'hello': %s\n", search(root, "hello") ? "Found" : "Not Found");

    // Clean up memory by freeing Trie nodes
    freeTrie(root);
}

int main() {
    demonstrateTrie();
    return 0;
}
