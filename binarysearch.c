#include <stdio.h>

// Function to perform binary search
int binarySearch(int arr[], int low, int high, int target) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        // If the element is present at the middle itself
        if (arr[mid] == target)
            return mid;

        // If element is smaller than mid, then it can only be present in left subarray
        if (arr[mid] > target)
            return binarySearch(arr, low, mid - 1, target);

        // Else the element can only be present in right subarray
        return binarySearch(arr, mid + 1, high, target);
    }

    // Element is not present in array
    return -1;
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 10;
    int result = binarySearch(arr, 0, n - 1, target);
    if (result == -1)
        printf("Element is not present in array\n");
    else
        printf("Element is present at index %d\n", result);
    return 0;
}
