#include <stdio.h>

int main() {
    // Define an array of integers
    int arr[5] = {2, 4, 6, 8, 10};
    
    // Calculate the sum of all elements in the array
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += arr[i];
    }
    
    // Print the sum
    printf("Sum of the array elements: %d\n", sum);
    
    return 0;
}
