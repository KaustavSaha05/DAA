#include <stdio.h>

// Problem 1: Finding the Peak Element in an Array
int findPeakElement(int arr[], int low, int high, int n) {
    int mid = low + (high - low) / 2;
    
    if ((mid == 0 || arr[mid - 1] <= arr[mid]) && (mid == n - 1 || arr[mid + 1] <= arr[mid])) {
        return arr[mid];
    }
    
    if (mid > 0 && arr[mid - 1] > arr[mid]) {
        return findPeakElement(arr, low, mid - 1, n);
    }
    
    return findPeakElement(arr, mid + 1, high, n);
}

// Problem 2: Searching in a Rotated Sorted Array
int searchInRotatedArray(int arr[], int low, int high, int target) {
    if (low > high) return -1;
    
    int mid = (low + high) / 2;
    if (arr[mid] == target) return mid;
    
    if (arr[low] <= arr[mid]) {
        if (target >= arr[low] && target <= arr[mid]) {
            return searchInRotatedArray(arr, low, mid - 1, target);
        }
        return searchInRotatedArray(arr, mid + 1, high, target);
    }
    
    if (target >= arr[mid] && target <= arr[high]) {
        return searchInRotatedArray(arr, mid + 1, high, target);
    }
    return searchInRotatedArray(arr, low, mid - 1, target);
}

// Problem 3: Finding Square Root Using Binary Search
int findSquareRoot(int num) {
    if (num == 0 || num == 1) return num;
    
    int low = 1, high = num, ans;
    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (mid * mid == num) return mid;
        
        if (mid * mid < num) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    // Testing Problem 1
    int arr1[] = {1, 3, 20, 4, 1, 0};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Peak Element: %d\n", findPeakElement(arr1, 0, n1 - 1, n1));
    
    // Testing Problem 2
    int arr2[] = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Index of Target: %d\n", searchInRotatedArray(arr2, 0, n2 - 1, target));
    
    // Testing Problem 3
    int num = 16;
    printf("Square Root: %d\n", findSquareRoot(num));
    
    return 0;
}
