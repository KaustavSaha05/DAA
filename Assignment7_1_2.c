#include <stdio.h>

#define N 5 // Change this value to solve for a different N

// Function to print the board
void printSolution(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if a queen can be placed at board[row][col]
int isSafe(int board[N][N], int row, int col) {
    // Check row (before the column)
    for (int j = 0; j < col; j++)
        if (board[row][j])
            return 0;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Check lower-left diagonal
    for (int i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

// Recursive function to solve N-Queens column by column
int solveNQueens(int board[N][N], int col) {
    if (col == N) { // If all queens are placed, print solution
        printSolution(board);
        return 1; // Return 1 to indicate at least one solution exists
    }

    int foundSolution = 0;
    for (int row = 0; row < N; row++) { // Try placing queen in each row
        if (isSafe(board, row, col)) { // Check if it's safe
            board[row][col] = 1; // Place queen
            solveNQueens(board, col + 1); // Recur for next column
            board[row][col] = 0; // Backtrack
        }
    }

    return foundSolution;
}

int main() {
    int board[N][N] = {0}; // Initialize board with zeros

    solveNQueens(board, 0);
}
