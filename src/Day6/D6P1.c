#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  

#define MAX_SIGNAL_LENGTH 5000
#define PACKET_SIZE 4


/* Function to check if a packet contains any duplicates */
bool uniquePack(char packet[], int size) 
{
    int z, y;
    bool foundPack = true;  
    
    for (z = 0; z < size; z++) {
        for (y = z + 1; y < size; y++) 
        {
            if (packet[z] == packet[y]) 
            {
                foundPack = false;  
                break;  
            }
        }
        if (!foundPack) 
        {
            break;  
        }
    }

    return foundPack;  
}

int main() {
    /* Create file pointer and read file */
    FILE *filepointer;
    filepointer = fopen("src/Day6/data.txt", "r");

    /* Check if the file was read correctly */
    if (filepointer == NULL) 
    {
        printf("Unable to read file!\n");
        return 1;
    }

    char readSignal[MAX_SIGNAL_LENGTH];
    char packet[PACKET_SIZE];
    int i;

    /* Read the full signal */
    fgets(readSignal, sizeof(readSignal), filepointer);

    /* Loop through the read signal */
    for (i = 0; i < sizeof(readSignal); i++) 
    {

        /* Check that enought characthers have been read to construct packet */
        if (i >= PACKET_SIZE) 
        {
            /* Construct current packet */
            packet[0] = readSignal[i - 3];
            packet[1] = readSignal[i - 2];
            packet[2] = readSignal[i - 1];
            packet[3] = readSignal[i];

            /* Check if the current packet is unique */
            if (uniquePack(packet, sizeof(packet)))
            {
                printf("First packet with %d unique characters is %c%c%c%c, which occured after processing %d characters \n", PACKET_SIZE, packet[0], packet[1], packet[2], packet[3], i + 1);
                break;
            }
        }
    }

    /* Close the file */
    fclose(filepointer); 

    return 0;
}
