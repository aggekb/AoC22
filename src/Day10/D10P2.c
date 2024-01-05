#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 10
#define INSTRUCTION_LENGTH 5
#define MAX_INSTRUCTIONS 150
#define CRT_WIDTH 40
#define CRT_HEIGHT 6

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
    int X = 1, cycle = 0, i, j, to_add;
    int nr_inst = 0;

    /* Read and store instructions from file */
    loadinput(instructions);

    /* Count the total number of instructions */
    for (i = 0; i < MAX_INSTRUCTIONS; i++) {
        if (strncmp(instructions[i], "noop", 4) == 0) {
            nr_inst += 1;
        } else if (strncmp(instructions[i], "addx", 4) == 0) {
            nr_inst += 2;
        }
    }

    char pixels[nr_inst];
    /* Initialize pixels to dots */
    for (i = 0; i < nr_inst; i++) {
        pixels[i] = '.';
    }

    for (i = 0; i < MAX_INSTRUCTIONS; i++) {
        if (strncmp(instructions[i], "noop", 4) == 0) {
            cycle++;
        } else if (strncmp(instructions[i], "addx", 4) == 0) {
            sscanf(instructions[i] + INSTRUCTION_LENGTH, "%d", &to_add);
            for (j = 0; j < 2; j++) {
                if (X - (cycle % 40) >= -1 && X - (cycle % 40) <= 1) {
                    pixels[cycle] = '#';
                }
                cycle++;
            }
            X += to_add;
        }

        if (X - (cycle % 40) >= -1 && X - (cycle % 40) <= 1) {
            pixels[cycle] = '#';
        }
    }

    /* Print the final image on CRT */
    for (i = 0; i < nr_inst; i += 40) {
        for (j = 0; j < 40; j++) {
            printf("%c", pixels[i + j]);
        }
        printf("\n");
    }

    return 0;
}
