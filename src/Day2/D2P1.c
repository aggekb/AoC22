#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    /* Specify constants */
    int LISTL = 5000;

    /* Specify arrays */
    char chararr[LISTL];

    /* Specify variables */
    int i = 0;
    char c;
    char myDraw;
    char opDraw;
    int drawPoint = 0;
    int roundPoint = 0;
    int totalPoints = 0;

    /* Create file pointer and open file */
    FILE *filepointer;
    filepointer = fopen("/Users/agatonoberg/Desktop/Git/AoC22/src/Day2/data.txt", "r");

    /* Check if the file was read correctly */
    if (filepointer == NULL) {
        printf("Unable to read the file\n");
        return 1;
    }

    /* Extract characters from data, skip space and new line */
    while ((c = fgetc(filepointer)) != EOF) {
        if (c != ' ' && c != '\n') {
            chararr[i] = c;
            i++;
        }
    }

    /* Close the file */
    fclose(filepointer);

    /* Close the string */
    chararr[i] = 0;

    for (i = 0; i < LISTL; i += 2) {
        opDraw = chararr[i];
        myDraw = chararr[i + 1];

        /* Grade the draw */
        switch (myDraw) {
            case 'X':
                /* Rock */
                drawPoint = 1;
                break;
            case 'Y':
                /* Paper */
                drawPoint = 2;
                break;
            case 'Z':
                /* Scissors */
                drawPoint = 3;
                break;
            default:
                break;
        }

        /* Grade the outcome of the round */
        if ((myDraw == 'X' && opDraw == 'A') ||
            (myDraw == 'Y' && opDraw == 'B') ||
            (myDraw == 'Z' && opDraw == 'C')) {
            /* Draw */
            roundPoint = 3;
        } else if ((myDraw == 'X' && opDraw == 'C') ||
                   (myDraw == 'Y' && opDraw == 'A') ||
                   (myDraw == 'Z' && opDraw == 'B')) {
            /* Winning round */
            roundPoint = 6;
        } else {
            /* Loosing round */
            roundPoint = 0;
        }
        
        /* Accumulate points for each round */
        totalPoints += (drawPoint + roundPoint);  
    }
    
    printf("\nTotal number of points from all rounds: %d \n", totalPoints);
    return 0;
}
