#include <stdio.h>
#include <string.h>


#define MAX_LINE_LENGTH 20

int main(){

    /* Create filepointer and read file */
    FILE * filepointer; 
    filepointer = fopen("/Users/agatonoberg/Desktop/Git/AoC22/src/Day4/data.txt","r");

    /* Check if file was read correctly */
    if (filepointer == NULL) {
        printf("Unable to read file!\n");
        return 1;
    }

    char content[MAX_LINE_LENGTH];  
    int num1, num2, num3, num4;
    int totalp = 0;

    while (fgets(content, sizeof(content), filepointer) != NULL) {
        
        /* Find numbers on line and store in num variable */
        sscanf(content, "%d-%d,%d-%d", &num1, &num2, &num3, &num4);

        if ((num1 >= num3) && (num2 <= num4)){
            /* Pair 1 is in Pair 2*/
            totalp ++;
        }
        else if ((num3 >= num1) && (num4 <= num2)){
            /* Pair 2 is in Pair 1 */
            totalp ++;
        }
    }

    printf("\n The total number of fully overlapping pairs is: %d \n",totalp);
    return 0;
}