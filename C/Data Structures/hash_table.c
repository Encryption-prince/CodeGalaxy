#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 // Size of the hash table

// Structure for a node in the linked list used for chaining
struct Node {
    int key;
    int value;
    struct Node* next;
};

// Structure for the hash table
struct HashTable {
    struct Node* table[SIZE];
};

// Function to create a new node
struct Node* createNode(int key, int value) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new hash table
struct HashTable* createHashTable() {
    struct HashTable* hashTable = (struct HashTable*) malloc(sizeof(struct HashTable));
    if (hashTable == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < SIZE; ++i) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Hash function to generate an index for a key
int hash(int key) {
    return key % SIZE;
}

// Function to insert a key-value pair into the hash table
void insert(struct HashTable* hashTable, int key, int value) {
    int index = hash(key);
    struct Node* newNode = createNode(key, value);

    // Insert at the beginning of the linked list at index
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

// Function to search for a key in the hash table and return its value
int search(struct HashTable* hashTable, int key) {
    int index = hash(key);
    struct Node* current = hashTable->table[index];

    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Key not found
}

// Function to display the contents of the hash table
void displayHashTable(struct HashTable* hashTable) {
    printf("Hash Table:\n");
    for (int i = 0; i < SIZE; ++i) {
        printf("[%d]: ", i);
        struct Node* current = hashTable->table[i];
        while (current != NULL) {
            printf("(%d, %d) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

// Function to free memory allocated to the hash table
void freeHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < SIZE; ++i) {
        struct Node* current = hashTable->table[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);
}

int main() {
    struct HashTable* hashTable = createHashTable();

    // Insert key-value pairs into the hash table
    insert(hashTable, 1, 10);
    insert(hashTable, 11, 20);
    insert(hashTable, 21, 30);
    insert(hashTable, 2, 40);
    insert(hashTable, 12, 50);
    insert(hashTable, 22, 60);
    insert(hashTable, 3, 70);
    insert(hashTable, 13, 80);

    // Display the hash table
    displayHashTable(hashTable);

    // Search for a key in the hash table
    int keyToSearch = 22;
    int value = search(hashTable, keyToSearch);
    if (value != -1) {
        printf("Value found for key %d: %d\n", keyToSearch, value);
    } else {
        printf("Value not found for key %d\n", keyToSearch);
    }

    // Free memory allocated to the hash table
    freeHashTable(hashTable);

    return 0;
}
