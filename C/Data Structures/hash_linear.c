#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10 // Size of the hash set

// Structure for the hash set using linear probing
struct HashSet {
    int *array; // Array to store elements
    bool *isOccupied; // Array to track if a slot is occupied
};

// Function to create a new hash set
struct HashSet* createHashSet() {
    struct HashSet* hashSet = (struct HashSet*) malloc(sizeof(struct HashSet));
    if (hashSet == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    hashSet->array = (int*) malloc(SIZE * sizeof(int));
    if (hashSet->array == NULL) {
        perror("Memory allocation failed");
        free(hashSet);
        exit(EXIT_FAILURE);
    }
    hashSet->isOccupied = (bool*) malloc(SIZE * sizeof(bool));
    if (hashSet->isOccupied == NULL) {
        perror("Memory allocation failed");
        free(hashSet->array);
        free(hashSet);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < SIZE; ++i) {
        hashSet->isOccupied[i] = false;
    }
    return hashSet;
}

// Hash function to generate an index for a key
int hash(int key) {
    return key % SIZE;
}

// Function to insert a key into the hash set
void insert(struct HashSet* hashSet, int key) {
    int index = hash(key);
    while (hashSet->isOccupied[index]) {
        index = (index + 1) % SIZE; // Linear probing
    }
    hashSet->array[index] = key;
    hashSet->isOccupied[index] = true;
}

// Function to check if a key exists in the hash set
bool contains(struct HashSet* hashSet, int key) {
    int index = hash(key);
    while (hashSet->isOccupied[index]) {
        if (hashSet->array[index] == key) {
            return true;
        }
        index = (index + 1) % SIZE; // Linear probing
    }
    return false;
}

// Function to remove a key from the hash set
void removeKey(struct HashSet* hashSet, int key) {
    int index = hash(key);
    while (hashSet->isOccupied[index]) {
        if (hashSet->array[index] == key) {
            hashSet->isOccupied[index] = false;
            return;
        }
        index = (index + 1) % SIZE; // Linear probing
    }
    printf("Key %d not found in the hash set\n", key);
}

// Function to display the elements of the hash set
void displayHashSet(struct HashSet* hashSet) {
    printf("Hash Set: ");
    for (int i = 0; i < SIZE; ++i) {
        if (hashSet->isOccupied[i]) {
            printf("%d ", hashSet->array[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Function to free memory allocated to the hash set
void freeHashSet(struct HashSet* hashSet) {
    free(hashSet->array);
    free(hashSet->isOccupied);
    free(hashSet);
}

int main() {
    // Create a hash set
    struct HashSet* hashSet = createHashSet();

    // Insert elements into the hash set
    insert(hashSet, 10);
    insert(hashSet, 20);
    insert(hashSet, 30);
    insert(hashSet, 40);
    insert(hashSet, 50);

    // Display the hash set
    displayHashSet(hashSet);

    // Check if elements exist in the hash set
    int keyToFind = 30;
    if (contains(hashSet, keyToFind)) {
        printf("Hash set contains %d\n", keyToFind);
    } else {
        printf("Hash set does not contain %d\n", keyToFind);
    }

    // Remove an element from the hash set
    int keyToRemove = 20;
    removeKey(hashSet, keyToRemove);
    printf("After removing %d:\n", keyToRemove);
    displayHashSet(hashSet);

    // Free memory allocated to the hash set
    freeHashSet(hashSet);

    return 0;
}
