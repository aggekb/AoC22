#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 100
#define COMPARTMENT_LENGTH 50
#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

int main() {

    /* Create file pointer and open file */
    FILE *filepointer;
    filepointer = fopen("/Users/agatonoberg/Desktop/Git/AoC22/src/Day3/data.txt", "r");

    /* Check if the file was read correctly */
    if (filepointer == NULL) {
        printf("Unable to read the file\n");
        return 1;
    }

    char content[STRING_LENGTH];
    int lineLength;
    int compLength;
    char comp1[COMPARTMENT_LENGTH];
    char comp2[COMPARTMENT_LENGTH];
    int i, j, y;
    char equalItem;
    const int ALPHABET_LENGTH = strlen(ALPHABET);
    int totalp = 0;

    while (fgets(content, sizeof(content), filepointer) != NULL) {
        /* Number of characters on the current line */
        lineLength = strlen(content);
        compLength = lineLength/2;

        /* Divide the strings into two compartments */
        strncpy(comp1, content, compLength);
        comp1[compLength] = '\0';
        strncpy(comp2, content + compLength, compLength);
        comp2[compLength] = '\0';

        /* Find the equal character */
        for (i = 0; i < compLength; i++) {
            for (j = 0; j < compLength; j++) {
                if (comp1[i] == comp2[j]) {
                    equalItem = comp1[i];
                }
            }
        }

        /* Asign priority to item */
        for (y = 0; y < ALPHABET_LENGTH; y++){
            if (equalItem == ALPHABET[y]){
                y++;
                break;
            }
        }
        /* Sum priorites */
        totalp += y;
    }

    /* Close the file */
    fclose(filepointer);

    /* Display the sum of all priorites */
    printf("\n The sum of all priorities is: %d \n", totalp);

    return 0;
}