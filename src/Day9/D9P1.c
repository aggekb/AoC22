#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

#define MAX_STEPS 10000
#define LINE_WIDTH 10

/* Global arrays */
int tailPos[2] = {0, 0};
int headPos[2] = {0, 0};
int positionsVisited[MAX_STEPS][2];

/* Load input */
void loadInput(char lines[MAX_STEPS][LINE_WIDTH]) {
    FILE *file = fopen("src/Day9/data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int i = 0;
    while (fgets(lines[i], sizeof(lines[i]), file)) {
        /* Remove newline character if present */
        char *newline = strchr(lines[i], '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        i++;
        if (i >= MAX_STEPS) {
            break;
        }
    }

    fclose(file);
}

void updateVisited(int *visitedCount){
    /*Check if the tail has already visited the current position*/
    int i;
    int notVisited = true;
    for(i = 0; i < MAX_STEPS; i++){
    if(positionsVisited[i][0] == tailPos[0] && positionsVisited[i][1] == tailPos[1]){
        notVisited = false;
        break;
    }
    }

    /* Update visited count if not visited*/
    if (notVisited){
    positionsVisited[*visitedCount][0] = tailPos[0];
    positionsVisited[*visitedCount][1] = tailPos[1];
    (*visitedCount)++;
    }
}

void moveTail(int *visitedCount) {
    /* Check if the tail must move */
    if (abs(tailPos[0] - headPos[0]) <= 1 && abs(tailPos[1] - headPos[1]) <= 1) {
        return;
    }

    /* Move tail based on head position */
    if (headPos[0] > tailPos[0]) {
        tailPos[0]++;
    } else if (headPos[0] < tailPos[0]) {
        tailPos[0]--;
    }

    if (headPos[1] > tailPos[1]) {
        tailPos[1]++;
    } else if (headPos[1] < tailPos[1]) {
        tailPos[1]--;
    }

    /* Update visited count */
    updateVisited(visitedCount);
}


void moveHead(char moveDirection, int numSteps, int *visitedCount) {
    int i;
    for (i = 0; i < numSteps; i++) {
        /* Move head */
        if (moveDirection == 'U') {
            headPos[1]++;
        } else if (moveDirection == 'R') {
            headPos[0]++;
        } else if (moveDirection == 'D') {
            headPos[1]--;
        } else if (moveDirection == 'L') {
            headPos[0]--;
        } else {
            printf("Invalid move direction\n");
        }

        /* Update the tail position based on the head */
        moveTail(visitedCount);
    }
}

int main() {
    char lines[MAX_STEPS][LINE_WIDTH];
    loadInput(lines);

    /* Initial states and count */
    int visitedCount = 1;
    positionsVisited[0][0] = 0;
    positionsVisited[0][1] = 0;

    /* Read instructions and process them */
    int i;
    for (i = 0; i < MAX_STEPS && lines[i][0] != '\0'; i++) {
        char moveDirection;
        int numSteps;
        sscanf(lines[i], "%c %d", &moveDirection, &numSteps);
        moveHead(moveDirection, numSteps, &visitedCount);
    }

    /* Display results */
    printf("The tail has visited %d positions.\n", visitedCount);

    return 0;
}
