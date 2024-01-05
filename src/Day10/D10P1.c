#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 10
#define INSTRUCTION_LENGTH 5
#define MAX_INSTRUCTIONS 150

/* Load instructions from file */
void loadinput(char instructions[MAX_INSTRUCTIONS][LINE_WIDTH]) {
    FILE *file = fopen("src/Day10/data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fgets(instructions[i], sizeof(instructions[i]), file)) {
        /* Remove newline character if present */
        char *newline = strchr(instructions[i], '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        i++;
        if (i >= MAX_INSTRUCTIONS) {
            break;
        }
    }

    fclose(file);
}

int main() {
    char instructions[MAX_INSTRUCTIONS][LINE_WIDTH];
    int registerX = 1, cycle = 1, signalSum = 0;
    int i, j, valueToAdd;

    /* Read and store instructions from file */
    loadinput(instructions);

    for (i = 0; i < MAX_INSTRUCTIONS; i++) {
        if (strncmp(instructions[i], "noop", 4) == 0) {
            if ((cycle % 40) == 20) {
                signalSum += (cycle * registerX);
            }
            cycle++;
        } else if (strncmp(instructions[i], "addx", 4) == 0) {
            sscanf(instructions[i] + INSTRUCTION_LENGTH, "%d", &valueToAdd);
            for (j = 0; j < 2; j++) {
                if ((cycle % 40) == 20) {
                    signalSum += (cycle * registerX);
                }
                cycle++;
            }
            registerX += valueToAdd;
        }
    }

    printf("Total Signal Strength: %d\n", signalSum);

    return signalSum;
}
