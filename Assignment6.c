#include <stdio.h>
#include <stdlib.h>

// Structure for an item (used for Fractional Knapsack)
struct Item {
    int value;
    int weight;
};

// Comparison function for sorting items by value-to-weight ratio (Fractional Knapsack)
int compare(const void *a, const void *b) {
    double r1 = (double)((struct Item *)b)->value / ((struct Item *)b)->weight;
    double r2 = (double)((struct Item *)a)->value / ((struct Item *)a)->weight;
    return (r1 > r2) - (r1 < r2);
}

// Fractional Knapsack (Greedy approach)
double fractional_knapsack(int capacity, struct Item items[], int n) {
    qsort(items, n, sizeof(struct Item), compare);

    double total_value = 0.0;

    for (int i = 0; i < n; i++) {
        if (capacity == 0)
            break;

        int amount = (items[i].weight <= capacity) ? items[i].weight : capacity;
        total_value += amount * ((double)items[i].value / items[i].weight);
        capacity -= amount;
    }

    return total_value;
}

// 0/1 Knapsack - Recursive approach
int knapsack_recursive(int W, int wt[], int val[], int n) {
    if (n == 0 || W == 0)
        return 0;
    
    if (wt[n - 1] > W)
        return knapsack_recursive(W, wt, val, n - 1);

    int include = val[n - 1] + knapsack_recursive(W - wt[n - 1], wt, val, n - 1);
    int exclude = knapsack_recursive(W, wt, val, n - 1);

    return include > exclude ? include : exclude;
}

// 0/1 Knapsack - Memoization approach
int knapsack_memo(int W, int wt[], int val[], int n, int memo[][101]) {
    if (n == 0 || W == 0)
        return 0;

    if (memo[n][W] != -1)
        return memo[n][W];

    if (wt[n - 1] > W)
        return memo[n][W] = knapsack_memo(W, wt, val, n - 1, memo);

    int include = val[n - 1] + knapsack_memo(W - wt[n - 1], wt, val, n - 1, memo);
    int exclude = knapsack_memo(W, wt, val, n - 1, memo);

    return memo[n][W] = include > exclude ? include : exclude;
}

// 0/1 Knapsack - Dynamic Programming approach
int knapsack_dp(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w) {
                int include = val[i - 1] + dp[i - 1][w - wt[i - 1]];
                int exclude = dp[i - 1][w];
                dp[i][w] = include > exclude ? include : exclude;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

// Main function to test all implementations
int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int capacity = 55;
    int n = sizeof(val) / sizeof(val[0]);

    // Preparing items for Fractional Knapsack
    struct Item items[n];
    for (int i = 0; i < n; i++) {
        items[i].value = val[i];
        items[i].weight = wt[i];
    }

    // 0/1 Knapsack - Recursive approach
    printf("0/1 Knapsack (Recursive): %d\n", knapsack_recursive(capacity, wt, val, n));

    // 0/1 Knapsack - Memoization approach
    int memo[101][101];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= capacity; j++)
            memo[i][j] = -1;
    printf("0/1 Knapsack (Memoization): %d\n", knapsack_memo(capacity, wt, val, n, memo));

    // 0/1 Knapsack - Dynamic Programming approach
    printf("0/1 Knapsack (DP): %d\n", knapsack_dp(capacity, wt, val, n));

    // Fractional Knapsack
    printf("Fractional Knapsack (Greedy): %.2lf\n", fractional_knapsack(capacity, items, n));

    return 0;
}
