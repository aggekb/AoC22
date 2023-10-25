#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_GRID_WIDTH 40
#define MAX_GRID_HEIGTH 50
#define NMBR_PILES 9
#define INITIAL_PILE_HEIGTH 8

int main() {
    /* Create filepointer and read file */
    FILE * filepointer; 
    filepointer = fopen("src/Day5/data.txt","r");

    /* Check if the file was read correctly */
    if (filepointer == NULL) {
        printf("Unable to read file!\n");
        return 1;
    }

    char currLine[MAX_GRID_WIDTH];
    char stacks[MAX_GRID_HEIGTH][NMBR_PILES];
    char pickedItem;
    char Result[NMBR_PILES];
    int i, j;
    int nbox, pick, dest;
    int row = MAX_GRID_HEIGTH - INITIAL_PILE_HEIGTH;
    int col = 0;
    int actionsDone = 0;

    /* Prepare stacks matrix */
    for (i = 0; i < MAX_GRID_HEIGTH; i++) {
        for (j = 0; j < NMBR_PILES; j++) {
            stacks[i][j] = ' ';
        }
    }

    /* Read the initial state of the piles and save in stacks */
    while (row < MAX_GRID_HEIGTH) {
        fgets(currLine, sizeof(currLine), filepointer);

        for (i = 1; i < MAX_GRID_WIDTH && currLine[i] != '\0'; i += 4) {
            stacks[row][col] = currLine[i];
            col++;
        }
        row++;
        col = 0;
    }

    /* Read the instructions from the file and save in num */
    while (fgets(currLine, sizeof(currLine), filepointer) != NULL) {
        if (currLine[0] != ' ' && currLine[0] != '\n') {
            sscanf(currLine, "move %d from %d to %d", &nbox, &pick, &dest);
            
            /* Keep track of done actions */
            actionsDone = 0;
            
            /* Perform actions until the current instructions are fullfilled */
            while (actionsDone < nbox) {
                if (actionsDone == nbox) {
                    break;
                }

                /* Start from the top and go down */
                for (i = 0; i < MAX_GRID_HEIGTH; i++) {
                    /* Pick the first item that occurs */
                    if (stacks[i][pick - 1] != ' ') {
                        pickedItem = stacks[i][pick - 1];
                        /* Item has been picked, empty the space */
                        stacks[i][pick - 1] = ' ';
                        
                        /* Move from the bottom and up to place the object at the top */
                        for (j = MAX_GRID_HEIGTH - 1; j >= 0; j--) {
                            if (stacks[j][dest - 1] != ' ' && stacks[j - 1][dest - 1] == ' ') {
                                stacks[j - 1][dest - 1] = pickedItem;
                                actionsDone++;
                                break;
                            } else if (stacks[j][dest - 1] == ' ' && j == 0) {
                                stacks[j][dest - 1] = pickedItem;
                                actionsDone++;
                                break;
                            } else if (j == (MAX_GRID_HEIGTH - 1) && !isalpha(stacks[j][dest - 1]) && !isalpha(stacks[j - 1][dest - 1])) {
                                stacks[j][dest - 1] = pickedItem;
                                actionsDone++;
                                break;
                            }
                        }
                        if (actionsDone == nbox) {
                            break;
                        }
                    }
                }
            }
        }
    }
    
    /* Close the file */
    fclose(filepointer); 

    /* Gather results in array */
    for (i = 0; i < NMBR_PILES; i++) {
        for (j = 0; j < MAX_GRID_HEIGTH; j++) {
            if (isalpha(stacks[j][i])) {
                Result[i] = stacks[j][i];
                break; 
            }
        }
        /* NULL terminate the end */
        Result[i + 1] = '\0';
    }
    
    /* Print results */
    printf("\n The top elements are: %s \n", Result);
    
    return 0;
}
