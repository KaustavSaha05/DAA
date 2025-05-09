#include <stdio.h>
#include <stdbool.h>

#define N 4  // Change this value for different board sizes

// Function to print the chessboard
void printSolution(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if placing a queen at board[row][col] is safe
bool isSafe(int board[N][N], int row, int col) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Backtracking function to solve N-Queens
bool solveNQueensUtil(int board[N][N], int row) {
    if (row == N) { // All queens are placed
        printSolution(board);
        return true;
    }

    bool success = false;

    // Try placing the queen in each column of the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1; // Place the queen

            // Recur to place the rest of the queens
            success = solveNQueensUtil(board, row + 1) || success;

            // Backtrack (remove the queen)
            board[row][col] = 0;
        }
    }
    return success;
}

// Wrapper function to initialize board and start solving
void solveNQueens() {
    int board[N][N] = {0}; // Initialize board with 0

    if (!solveNQueensUtil(board, 0))
        printf("No solution exists.\n");
}

int main() {
    solveNQueens();
    return 0;
}
