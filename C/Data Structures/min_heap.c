#include <stdio.h>
#include <stdlib.h>

#define MIN_HEAP_SIZE 100

// Structure for the heap
struct MinHeap {
    int *array; // Array to store heap elements
    int size;   // Current number of elements in the heap
    int capacity; // Maximum capacity of the heap
};

// Function to create a new min heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap *minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    if (minHeap == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (int*) malloc(capacity * sizeof(int));
    if (minHeap->array == NULL) {
        printf("Memory allocation failed!\n");
        free(minHeap);
        return NULL;
    }
    return minHeap;
}

// Function to swap two elements in the heap
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree with the root at given index
void minHeapify(struct MinHeap *minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Compare with left child
    if (left < minHeap->size && minHeap->array[left] < minHeap->array[smallest]) {
        smallest = left;
    }

    // Compare with right child
    if (right < minHeap->size && minHeap->array[right] < minHeap->array[smallest]) {
        smallest = right;
    }

    // If smallest is not root
    if (smallest != index) {
        swap(&minHeap->array[index], &minHeap->array[smallest]);
        // Recursively heapify the affected subtree
        minHeapify(minHeap, smallest);
    }
}

// Function to insert a new element into the heap
void insert(struct MinHeap *minHeap, int data) {
    if (minHeap->size >= minHeap->capacity) {
        printf("Heap overflow! Cannot insert %d\n", data);
        return;
    }
    // Insert the new element at the end of the heap
    int index = minHeap->size;
    minHeap->array[index] = data;
    minHeap->size++;

    // Heapify the new element upwards
    while (index > 0 && minHeap->array[(index - 1) / 2] > minHeap->array[index]) {
        swap(&minHeap->array[index], &minHeap->array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Function to extract the minimum element from the heap
int extractMin(struct MinHeap *minHeap) {
    if (minHeap->size <= 0) {
        printf("Heap underflow! Cannot extract minimum element\n");
        return -1; // Return -1 indicating failure
    }
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    // Store the minimum element and remove it from the heap
    int min = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;

    // Heapify the root downwards
    minHeapify(minHeap, 0);

    return min;
}

// Function to display the elements of the heap
void displayHeap(struct MinHeap *minHeap) {
    if (minHeap->size <= 0) {
        printf("Heap is empty. No elements to display\n");
        return;
    }
    printf("Heap elements: ");
    for (int i = 0; i < minHeap->size; ++i) {
        printf("%d ", minHeap->array[i]);
    }
    printf("\n");
}

// Function to free memory allocated to the heap
void freeMinHeap(struct MinHeap *minHeap) {
    free(minHeap->array);
    free(minHeap);
}

int main() {
    struct MinHeap *minHeap = createMinHeap(MIN_HEAP_SIZE);

    insert(minHeap, 10);
    insert(minHeap, 20);
    insert(minHeap, 15);
    insert(minHeap, 40);
    insert(minHeap, 50);
    insert(minHeap, 100);

    printf("Min heap after insertions:\n");
    displayHeap(minHeap);

    printf("Extracted min element: %d\n", extractMin(minHeap));
    printf("Extracted min element: %d\n", extractMin(minHeap));

    printf("Min heap after extractions:\n");
    displayHeap(minHeap);

    freeMinHeap(minHeap);

    return 0;
}
