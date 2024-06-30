#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

// Structure for the heap
struct MaxHeap {
    int *array; // Array to store heap elements
    int size;   // Current number of elements in the heap
    int capacity; // Maximum capacity of the heap
};

// Function to create a new max heap
struct MaxHeap* createMaxHeap(int capacity) {
    struct MaxHeap *maxHeap = (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    if (maxHeap == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    maxHeap->capacity = capacity;
    maxHeap->size = 0;
    maxHeap->array = (int*) malloc(capacity * sizeof(int));
    if (maxHeap->array == NULL) {
        printf("Memory allocation failed!\n");
        free(maxHeap);
        return NULL;
    }
    return maxHeap;
}

// Function to swap two elements in the heap
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree with the root at given index
void maxHeapify(struct MaxHeap *maxHeap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Compare with left child
    if (left < maxHeap->size && maxHeap->array[left] > maxHeap->array[largest]) {
        largest = left;
    }

    // Compare with right child
    if (right < maxHeap->size && maxHeap->array[right] > maxHeap->array[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != index) {
        swap(&maxHeap->array[index], &maxHeap->array[largest]);
        // Recursively heapify the affected subtree
        maxHeapify(maxHeap, largest);
    }
}

// Function to insert a new element into the heap
void insert(struct MaxHeap *maxHeap, int data) {
    if (maxHeap->size >= maxHeap->capacity) {
        printf("Heap overflow! Cannot insert %d\n", data);
        return;
    }
    // Insert the new element at the end of the heap
    int index = maxHeap->size;
    maxHeap->array[index] = data;
    maxHeap->size++;

    // Heapify the new element upwards
    while (index > 0 && maxHeap->array[(index - 1) / 2] < maxHeap->array[index]) {
        swap(&maxHeap->array[index], &maxHeap->array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Function to extract the maximum element from the heap
int extractMax(struct MaxHeap *maxHeap) {
    if (maxHeap->size <= 0) {
        printf("Heap underflow! Cannot extract maximum element\n");
        return -1; // Return -1 indicating failure
    }
    if (maxHeap->size == 1) {
        maxHeap->size--;
        return maxHeap->array[0];
    }

    // Store the maximum element and remove it from the heap
    int max = maxHeap->array[0];
    maxHeap->array[0] = maxHeap->array[maxHeap->size - 1];
    maxHeap->size--;

    // Heapify the root downwards
    maxHeapify(maxHeap, 0);

    return max;
}

// Function to display the elements of the heap
void displayHeap(struct MaxHeap *maxHeap) {
    if (maxHeap->size <= 0) {
        printf("Heap is empty. No elements to display\n");
        return;
    }
    printf("Heap elements: ");
    for (int i = 0; i < maxHeap->size; ++i) {
        printf("%d ", maxHeap->array[i]);
    }
    printf("\n");
}

// Function to free memory allocated to the heap
void freeMaxHeap(struct MaxHeap *maxHeap) {
    free(maxHeap->array);
    free(maxHeap);
}

int main() {
    struct MaxHeap *maxHeap = createMaxHeap(MAX_HEAP_SIZE);

    insert(maxHeap, 10);
    insert(maxHeap, 20);
    insert(maxHeap, 15);
    insert(maxHeap, 40);
    insert(maxHeap, 50);
    insert(maxHeap, 100);

    printf("Max heap after insertions:\n");
    displayHeap(maxHeap);

    printf("Extracted max element: %d\n", extractMax(maxHeap));
    printf("Extracted max element: %d\n", extractMax(maxHeap));

    printf("Max heap after extractions:\n");
    displayHeap(maxHeap);

    freeMaxHeap(maxHeap);

    return 0;
}
