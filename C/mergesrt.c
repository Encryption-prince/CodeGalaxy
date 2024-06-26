#include <stdio.h>
void merge(int arr[], int lb, int mid, int ub)
{
    int left = lb;
    int right = mid + 1;
    int brr[lb + ub + 1];
    int k = lb;
    while (left <= mid && right <= ub)
    {
        if (arr[left] <= arr[right])
        {
            brr[k] = arr[left];
            left++;

        }
        else
        {
            brr[k] = arr[right];
            right++;

        }
        k++;
    }

    while (right <= ub)
    {
        brr[k] = arr[right];
        right++;
        k++;
    }

    while (left <= mid)
    {
        brr[k] = arr[left];
        left++;
        k++;
    }

    for (int i = lb; i <= ub; i++)
    {
        arr[i] = brr[i];
    }
}
void mergeSort(int arr[], int lb, int ub)
{
    if (lb < ub)
    {
        int mid = (lb + ub) / 2;
        mergeSort(arr, lb, mid);
        mergeSort(arr, mid + 1, ub);
        merge(arr, lb, mid, ub);
    }

}

int main()
{
    int ub;
    printf("Enter the size of array:");
    scanf("%d", &ub);
    int arr[ub];
    printf("Enter the elements of array:");
    for (int i = 0; i < ub; i++)
    {
        scanf("%d", &arr[i]);
    }
   printf("\nBefore sorting:\n");
    for (int i = 0; i < ub; i++)
    {
        printf("%d ", arr[i]);
    }

    mergeSort(arr, 0, ub-1);
    printf("\nAfter sorting:\n");

    for (int i = 0; i < ub; i++)
    {
        printf("%d ", arr[i]);
    }


    return 0;
}
