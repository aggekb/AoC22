#include <stdio.h>
#include <string.h>


#define MAX_LINE_LENGTH 20

int main(){

    /* Create filepointer and read file */
    FILE * filepointer; 
    filepointer = fopen("src/Day4/data.txt","r");

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

        /* Find the overlapping pairs and add to totalp */
        if ((num2 >= num3 && num2 <= num4) || (num3 >= num1 && num3 <= num2) ||
            (num1 >= num3 && num1 <= num4) || (num4 >= num1 && num4 <= num2)) 
        {
            totalp++;
        }
    }

    printf("\n The total number of overlapping pairs is: %d \n",totalp);
    return 0;
}