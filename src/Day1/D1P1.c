#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    /* Specify constans */
    int LENGTH = 2250;
    int LINELEN = 10;

    /* Specify arrays */
    int dataList[LENGTH]; 
    char line[LINELEN];
    
    /* Specify variables */
    int i = 0;
    int j = 0;
    int sumCal = 0;
    int maxCal = 0; 

    /* Create file pointer and open file*/
    FILE * filepointer;
    filepointer = fopen("/Users/agatonoberg/Desktop/Git/AoC22/src/Day1/data.txt","r");
    
    /* Check if file was read correctly */
    if (filepointer == NULL) {
        printf("Unable to read file\n");
        return 1;
    }

    /* Fill datalist and replace \n with zeros */
    while(i < LENGTH && fgets(line, LINELEN, filepointer))
    {
        if(strcmp(line, "\n") == 0)
        {
            dataList[i] = 0; 
        }
        else{
            dataList[i] = atoi(line);
        }
        i++;
    }

    /* Close file */
    fclose(filepointer);

    /* Find the elf carrying the most calories*/
    for (j=0; j < LENGTH; j++){
        if(dataList[j] != 0){
            sumCal = sumCal + dataList[j];
            if (sumCal > maxCal){
            maxCal = sumCal;
            }
        }
        else{
            sumCal = 0;
        }
    }

    /* Print results */
    printf("\n The elf with the most calories hold: %d",maxCal);

    return 0;
}



