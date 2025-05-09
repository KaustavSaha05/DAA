#include <stdio.h>
#include <stdbool.h>

// Backtracking approach
bool subsetSumBacktrack(int arr[], int n, int target) {
    if (target == 0) return true;
    if (n == 0 || target < 0) return false;
    
    // Exclude the last element
    bool exclude = subsetSumBacktrack(arr, n - 1, target);
    // Include the last element
    bool include = subsetSumBacktrack(arr, n - 1, target - arr[n - 1]);
    
    return include || exclude;
}

// Dynamic Programming approach
bool subsetSumDP(int arr[], int n, int target) {
    bool dp[n + 1][target + 1];
    
    // Initialize DP table
    for (int i = 0; i <= n; i++) dp[i][0] = true;
    for (int j = 1; j <= target; j++) dp[0][j] = false;
    
    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (arr[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    
    return dp[n][target];
}

int main() {
    int arr[] = {3, 34, 4, 12, 5, 2};
    int target = 9;
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Backtracking result: %s\n", subsetSumBacktrack(arr, n, target) ? "Yes" : "No");
    printf("Dynamic Programming result: %s\n", subsetSumDP(arr, n, target) ? "Yes" : "No");
    
    return 0;
}
