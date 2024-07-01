#include <stdio.h>

// Define the maximum size of the input array
#define MAXN 100000

// Initialize the segment tree
int tree[4 * MAXN];

// Build the segment tree
void Build_Segment_Tree(int arr[], int start, int end, int treeNode) {
    if (start == end) {
        tree[treeNode] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    Build_Segment_Tree(arr, start, mid, 2 * treeNode);
    Build_Segment_Tree(arr, mid + 1, end, 2 * treeNode + 1);
    tree[treeNode] = tree[2 * treeNode] + tree[2 * treeNode + 1];
}

// Query the segment tree
int Query_Segment_Tree(int start, int end, int treeNode, int left, int right) {
    if (start > right || end < left)
        return 0; // No overlap
    if (start >= left && end <= right)
        return tree[treeNode]; // Complete overlap
    int mid = (start + end) / 2;
    int ans1 = Query_Segment_Tree(start, mid, 2 * treeNode, left, right);
    int ans2 = Query_Segment_Tree(mid + 1, end, 2 * treeNode + 1, left, right);
    return ans1 + ans2; // Partial overlap
}

int main() {
    int arr[] = {1, 3, 5, 7, 9}; // Example input array
    int n = sizeof(arr) / sizeof(arr[0]);

    // Build the segment tree
    Build_Segment_Tree(arr, 0, n - 1, 1);

    // Query the segment tree (e.g., sum between indices 1 and 3)
    int left = 1, right = 3;
    int result = Query_Segment_Tree(0, n - 1, 1, left, right);

    printf("Sum between indices %d and %d: %d\n", left, right, result);

    // Update an element (e.g., change arr[2] to 6)
    int idx = 2, value = 6;
    arr[idx] = value;
    Build_Segment_Tree(arr, 0, n - 1, 1); // Rebuild the segment tree

    // Query again after the update
    result = Query_Segment_Tree(0, n - 1, 1, left, right);
    printf("Updated sum between indices %d and %d: %d\n", left, right, result);

    return 0;
}
