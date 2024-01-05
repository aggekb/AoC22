#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 99
#define MAX_COLS 99

int grid[MAX_ROWS][MAX_COLS];

void getgrid() {
    FILE *file = fopen("src/Day8/data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    int row = 0;
    int col;
    while (fscanf(file, "%1d", &grid[row][0]) != EOF) {
        for (col = 1; col < MAX_COLS; col++) {
            fscanf(file, "%1d", &grid[row][col]);
        }

        row++;
        if (row >= MAX_ROWS) {
            break; 
        }
    }

    fclose(file);
}

int VisabilityScore(int grid[MAX_ROWS][MAX_COLS], int row, int col) {
    int height = grid[row][col];
    int rowAbove, rowBelow, colLeft, colRight;
    int above = 0;
    for (rowAbove = row - 1; rowAbove >= 0; rowAbove--) {
        above += 1;
        if (grid[rowAbove][col] >= height) {
            break;
        }
    }

    int below = 0;
    for (rowBelow = row + 1; rowBelow < MAX_ROWS; rowBelow++) {
        below += 1;
        if (grid[rowBelow][col] >= height) {
            break;
        }
    }

    int left = 0;
    for (colLeft = col - 1; colLeft >= 0; colLeft--) {
        left += 1;
        if (grid[row][colLeft] >= height) {
            break;
        }
    }

    int right = 0;
    for (colRight = col + 1; colRight < MAX_COLS; colRight++) {
        right += 1;
        if (grid[row][colRight] >= height) {
            break;
        }
    }

    return above * below * left * right;
}

void getResult(int grid[MAX_ROWS][MAX_COLS]) {
    int row, col;
    int currentScore; 
    int maxScore = 0; 
    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_COLS; col++) {
            currentScore = VisabilityScore(grid, row, col);
            if (currentScore > maxScore) {
                maxScore = currentScore;
            }
        }
    }
    printf("The maximum score is: %d\n", maxScore);
}

int main() {
    getgrid();
    getResult(grid);
    return 0;
}
