#include <stdio.h>
#include <limits.h>

#define MAX 100
int dp[MAX][MAX];
int bracket[MAX][MAX];

int recursive(int a[], int i, int j){
    if(i==j){
        return 0;
    }
    int mincost = INT_MAX;
    for(int k=i; k<j; k++){
        int cost = recursive(a, i, k) + recursive(a, k+1, j) + a[i-1]*a[k]*a[j];
        if(cost < mincost){
            mincost = cost;
        }
    }
    return mincost;
}

int memoization(int a[], int i, int j){
    if(i==j){
        return 0;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    int mincost = INT_MAX;
    for(int k=i; k<j; k++){
        int cost = memoization(a, i, k) + memoization(a, k+1, j) + a[i-1]*a[k]*a[j];
        if(cost < mincost){
            mincost = cost;
        }
    }
    return dp[i][j] = mincost;
}

int matrixchaindp(int a[], int n){
    int dp[n][n];
    for(int i=1; i<n; i++){
        dp[i][i] = 0;
    }
    for(int L=2; L<n; L++){
        for(int i=1; i<n-L+1; i++){
            int j = i+L-1;
            dp[i][j] = INT_MAX;
            for(int k=i; k<j; k++){
                int cost = dp[i][k] + dp[k+1][j] + a[i-1]*a[k]*a[j];
                if (cost<dp[i][j]){
                    dp[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }
    return dp[1][n-1];
}

void optimalparenthesis(int i, int j, int n, char name){
    if(i==j){
        printf("%c", name++);
        return;
    }
    printf("(");
    optimalparenthesis(i, bracket[i][j], n, name);
    optimalparenthesis(bracket[i][j]+1, j, n, name);
    printf(")");
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);
    int p[n + 1];
    printf("Enter the dimensions array: ");
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }
    
    // Recursive Approach
    printf("Minimum cost (Recursive): %d\n", recursive(p, 1, n));
    
    // Memoization Approach
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = -1;
    printf("Minimum cost (Memoization): %d\n", memoization(p, 1, n));
    
    // Dynamic Programming Approach
    printf("Minimum cost (DP): %d\n", matrixchaindp(p, n + 1));
    
    // Optimal Parenthesization
    printf("Optimal Parenthesization: ");
    optimalparenthesis(1, n, n + 1, 'A');
    printf("\n");
    
    return 0;
}
