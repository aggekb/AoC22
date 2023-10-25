#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 100
#define GROUP_SIZE 3
#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define MAX_GROUP_SET 300

int main() {
  
    /* Create file pointer and open file */
    FILE *filepointer;
    filepointer = fopen("src/Day3/data.txt", "r");

    /* Check if the file was read correctly  */
    if (filepointer == NULL) {
        printf("Unable to read the file\n");
        return 1;
    }

    int currentGroup = 0;
    int currentElf = 0; 
    int totalp = 0;
    int i, j, y, z, x;
    char equalItem; 
    int foundItem; 
    int lineLength;
    char content[STRING_LENGTH];
    char comp1[STRING_LENGTH];
    char comp2[STRING_LENGTH];
    char comp3[STRING_LENGTH];
    char groupSets[MAX_GROUP_SET][GROUP_SIZE][STRING_LENGTH];
    const int ALPHABET_LENGTH = strlen(ALPHABET);

    while (fgets(content, sizeof(content), filepointer) != NULL) {
        /* Number of characters on the current line */
        lineLength = strlen(content);

        /* Copy the content of the current line to the current set */
        strncpy(groupSets[currentGroup][currentElf], content, lineLength);

        /* Divide data into groups */
        if (currentElf < GROUP_SIZE - 1) {
            currentElf ++; 
        }
        else{
            currentElf = 0; 
            currentGroup ++; 
         }
        
    }

    /* Close the file */
    fclose(filepointer);

    /* Find the common item and assign priority */
    for (i = 0; i < currentGroup; i++) {
        strcpy(comp1, groupSets[i][0]);
        strcpy(comp2, groupSets[i][1]);
        strcpy(comp3, groupSets[i][2]);
        foundItem = 0; 

        /* Loop through comp1 */
        for (j = 0; j < strlen(comp1); j++) {
            /* Loop through comp2 */
            for (y = 0; y < strlen(comp2); y++) {
                if (comp1[j] == comp2[y]) {
                    /* Loop through comp3 */
                    for (z = 0; z < strlen(comp3); z++) {
                        if (comp1[j] == comp3[z] && comp2[y] == comp3[z]) {
                            /* Store the common character in equalItem */
                            equalItem = comp1[j];
                            /* Assign priority to common character */
                            for (x = 0; x < ALPHABET_LENGTH; x++){
                                if (equalItem == ALPHABET[x]){
                                    x++;
                                    break;
                                }
                            }
                            /* Declare item as found */
                            foundItem = 1;
                            break;
                        }
                    }
                }
                if (foundItem) 
                {
                    break;
                }
            }
            if (foundItem) 
            {
                break;
            }
        }
        /* Sum all priorities */
        totalp += x;
    }
    printf("\n The total sum of priorities is: %d \n ", totalp);
    return 0;
}
