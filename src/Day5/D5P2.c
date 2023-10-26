#include <stdio.h>
#include <ctype.h>

#define MAX_GRID_WIDTH 40
#define MAX_GRID_HEIGHT 50
#define NMBR_PILES 9
#define INITIAL_PILE_HEIGHT 8

int main() {
    FILE *filepointer;
    filepointer = fopen("src/Day5/data.txt", "r");

    if (filepointer == NULL) {
        printf("Unable to read file!\n");
        return 1;
    }

    char currLine[MAX_GRID_WIDTH];
    char stacks[MAX_GRID_HEIGHT][NMBR_PILES];
    char pickedItems[MAX_GRID_HEIGHT][NMBR_PILES];
    char Result[NMBR_PILES];
    int i, j;
    int nbox, pick, dest, boxesMoved;
    int row = MAX_GRID_HEIGHT - INITIAL_PILE_HEIGHT;
    int col = 0;

    /* Prepare stacks matrix */
    for (i = 0; i < MAX_GRID_HEIGHT; i++) {
        for (j = 0; j < NMBR_PILES; j++) {
            stacks[i][j] = ' ';
            pickedItems[i][j] = ' '; 
        }
    }

    /* Read inital state of the stacks */
    while (row < MAX_GRID_HEIGHT) {
        fgets(currLine, sizeof(currLine), filepointer);

        for (i = 1; i < MAX_GRID_WIDTH && currLine[i] != '\0'; i += 4) {
            stacks[row][col] = currLine[i];
            col++;
        }
        row++;
        col = 0;
    }

    while (fgets(currLine, sizeof(currLine), filepointer) != NULL) {
        if (currLine[0] != ' ' && currLine[0] != '\n') {
            sscanf(currLine, "move %d from %d to %d", &nbox, &pick, &dest);

            /* Reset boxesMoved for the new action */
            boxesMoved = 0;

            /* Pick boxes according to instructions */
            for (i = 0; i < MAX_GRID_HEIGHT; i++) {
                if (stacks[i][pick - 1] != ' ' && boxesMoved < nbox) {
                    pickedItems[boxesMoved][dest - 1] = stacks[i][pick - 1];
                    stacks[i][pick - 1] = ' ';
                    boxesMoved++;
                }
            }
            /* Place boxes in the same order as they were picked */
            for (i = MAX_GRID_HEIGHT-1; i >= 0; i--) {
                if (pickedItems[i][dest - 1] != ' ') {
                    for (j = MAX_GRID_HEIGHT - 1; j >= 0; j--) {
                        if (stacks[j][dest - 1] == ' ') {
                            stacks[j][dest - 1] = pickedItems[i][dest - 1];
                            pickedItems[i][dest - 1] = ' ';
                            break;
                        }
                    }
                }
            }
        }
    }

    /* Close the file */
    fclose(filepointer);

    /* Gather results in string */
    for (i = 0; i < NMBR_PILES; i++) {
        for (j = 0; j < MAX_GRID_HEIGHT; j++) {
            if (isalpha(stacks[j][i])) {
                Result[i] = stacks[j][i];
                break;
            }
        }
        /* NULL terminate the end */
        Result[i + 1] = '\0';
    }

    printf("\nThe top elements are: %s\n", Result);

    return 0;
}
