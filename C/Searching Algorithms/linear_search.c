#include <stdio.h>

// Function for linear search
int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i; // Return the index of the element if found
        }
    }
    return -1; // Return -1 if the element is not found
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 22; // Element to search for

    printf("Array elements:");
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    int index = linearSearch(arr, n, x);

    if (index != -1) {
        printf("Element %d found at index %d.\n", x, index);
    } else {
        printf("Element %d not found in the array.\n", x);
    }

    return 0;
}
