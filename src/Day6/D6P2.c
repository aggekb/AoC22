#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIGNAL_LENGTH 5000
#define PACKET_SIZE 14

/* Function to check if a packet contains any duplicates */
bool uniquePack(char packet[], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (packet[i] == packet[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    /* Create file pointer and read file */
    FILE *filepointer;
    filepointer = fopen("src/Day6/data.txt", "r");

    /* Check if the file was read correctly */
    if (filepointer == NULL) {
        printf("Unable to read the file!\n");
        return 1;
    }

    char readSignal[MAX_SIGNAL_LENGTH];
    char packet[PACKET_SIZE];
    int i, j, signalLength;

    /* Read the full signal */
    fgets(readSignal, sizeof(readSignal), filepointer);
    signalLength = strlen(readSignal);

    /* Loop through the read signal */
    for (i = 0; i <= signalLength - PACKET_SIZE; i++) {
        
        /* Pick out the current packet */
        for (j = 0; j < PACKET_SIZE; j++) {
            /* Construct the current packet */
            packet[j] = readSignal[i + j];
            packet[j+1] = '\0';
        }

        /* Check if the current packet is unique */
        if (uniquePack(packet, PACKET_SIZE)) {
            printf("\nFirst packet with %d unique characters is %s, which occurred after processing %d characters\n", PACKET_SIZE, packet, i + j);
            break;
        }
    }

    /* Close the file */
    fclose(filepointer);

    return 0;
}
