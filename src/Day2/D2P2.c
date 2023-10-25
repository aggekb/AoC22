#include <stdio.h>

int main() {
    /* Specify constants */
    int LISTL = 5000;

    /* Specify arrays */
    char chararr[LISTL];

    /* Specify variables */
    int i = 0;
    char c;
    char roundEnd;
    char opDraw;
    int drawPoint = 0;
    int roundPoint = 0;
    int totalPoints = 0;

    /* Create file pointer and open file */
    FILE *filepointer;
    filepointer = fopen("src/Day2/data.txt", "r");

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
        roundEnd = chararr[i + 1];
        
        /* Grade the draw */
        switch (roundEnd) {
            case 'X':
                /* Needs to loose */
                if (opDraw == 'A'){
                    drawPoint = 3;
                }
                else if(opDraw == 'B'){
                    drawPoint = 1;
                }
                else{
                    drawPoint = 2;
                }
                roundPoint = 0; 
                break;
            case 'Y':
                /* End round in draw  */
                if (opDraw == 'A'){
                    drawPoint = 1;
                }
                else if(opDraw == 'B'){
                    drawPoint = 2;
                }
                else{
                    drawPoint = 3;
                }
                roundPoint = 3; 
                break;
            case 'Z':
                /* End round in Win */
                if (opDraw == 'A'){
                    drawPoint = 2;
                }
                else if(opDraw == 'B'){
                    drawPoint = 3;
                }
                else{
                    drawPoint = 1;
                }
                roundPoint = 6; 
                break;
            default:
                break;
        }
        
        /* Accumulate points for each round */
        totalPoints += (drawPoint + roundPoint);  
    }
    
    printf("\nTotal number of points from all rounds: %d \n", totalPoints);
    return 0;
}
