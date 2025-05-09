#include <stdio.h>
#include <limits.h>

// Function to find the maximum profit from cutting the rod
int rodCutting(int price[], int n) {
    int dp[n + 1]; // DP array to store maximum profit for each length
    dp[0] = 0; // Base case: No rod, no profit

    // Build the table dp[] in bottom-up manner
    for (int i = 1; i <= n; i++) {
        int max_val = INT_MIN;
        for (int j = 0; j < i; j++) {
            max_val = (max_val > price[j] + dp[i - j - 1]) ? max_val : (price[j] + dp[i - j - 1]);
        }
        dp[i] = max_val;
    }
    return dp[n]; // Maximum profit for rod of length n
}

int main() {
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20}; // Example price list
    int n = sizeof(price) / sizeof(price[0]);  // Length of the rod
    printf("Maximum profit: %d\n", rodCutting(price, n));
    return 0;
}