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

int checkVisability(int grid[MAX_ROWS][MAX_COLS], int row, int col) {
    int height = grid[row][col];

    if (row == 0 || row == MAX_ROWS - 1 || col == 0 || col == MAX_COLS - 1) {
        return 1;
    }

    int above = 1, below = 1, left = 1, right = 1;
    int rowAbove, rowBelow, colLeft, colRight;

    for (rowAbove = 0; rowAbove < row; rowAbove++) {
        if (grid[rowAbove][col] >= height) {
            above = 0;
        }
    }

    for (rowBelow = row + 1; rowBelow < MAX_ROWS; rowBelow++) {
        if (grid[rowBelow][col] >= height) {
            below = 0;
        }
    }

    for (colLeft = 0; colLeft < col; colLeft++) {
        if (grid[row][colLeft] >= height) {
            left = 0;
        }
    }

    for (colRight = col + 1; colRight < MAX_COLS; colRight++) {
        if (grid[row][colRight] >= height) {
            right = 0;
        }
    }

    return above || below || left || right;
}

void getResult(int grid[MAX_ROWS][MAX_COLS]) {
    int visibleTrees = 0;
    int row, col;
    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_COLS; col++) {
            if (checkVisability(grid, row, col)) {
                visibleTrees++;
            }
        }
    }
    printf("The number of visible trees are: %d\n", visibleTrees);
}

int main() {
    getgrid();
    getResult(grid);
    return 0;
}
