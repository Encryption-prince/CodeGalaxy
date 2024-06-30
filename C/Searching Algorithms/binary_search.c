#include <stdio.h>

// Function for binary search
int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < x)
            left = mid + 1;
        // If x is smaller, ignore right half
        else
            right = mid - 1;
    }

    // If we reach here, then the element was not present
    return -1;
}

int main() {
    int arr[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 22; // Element to search for

    printf("Array elements:");
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    int index = binarySearch(arr, 0, n - 1, x);

    if (index != -1) {
        printf("Element %d found at index %d.\n", x, index);
    } else {
        printf("Element %d not found in the array.\n", x);
    }

    return 0;
}
