#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#define FOLDER_SIZE_LIMIT 100000
#define MAX_SUB_LEVELS 8

/* Define the struct for the folders. */
struct Folder {
    struct Folder* topLevel;
    struct Folder* subLevels[MAX_SUB_LEVELS];
    int size;
    int subLevelCount;
};

/*  Set alias for the struct tag */
typedef struct Folder Folder;

/* Make directory */
Folder* makeDir(Folder* topLevel) {
    Folder* newFolder = (Folder*)calloc(1, sizeof(Folder));

    if (topLevel != NULL) {
        topLevel->subLevels[topLevel->subLevelCount++] = newFolder;
        newFolder->topLevel = topLevel;
    }

    return newFolder;
}

/* Update the sizes of the top-level folders. */
void updateTopLevelSizes(Folder* currentFolder, int size) {
    Folder* folder = currentFolder;

    while (folder->topLevel != NULL) {
        folder = folder->topLevel;
        folder->size += size;
    }
}

/* Find size of folders to delete  */
int foldersToDelete(Folder* root) {
    int totalSize = 0;
    int i;

    for (i = 0; i < root->subLevelCount; ++i) {
        Folder* subLevelFolder = root->subLevels[i];

        if (subLevelFolder->size <= FOLDER_SIZE_LIMIT) {
            totalSize += subLevelFolder->size;
        }

        totalSize += foldersToDelete(subLevelFolder);
    }

    return totalSize;
}

/* Process input commands */
void processCommands(FILE* filePointer, Folder* root) {
    char buffer[64];
    Folder* currentFolder = root;

    /* Read each line from the file */
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        char argument[16];

        /* Check if the line is a "change directory" command */
        if (sscanf(buffer, "$ cd %s", argument) > 0) {
            /* If it's not the root directory */
            if (strcmp(argument, "/") != 0) {
                /* If it's moving up one level */
                if (strcmp(argument, "..") == 0) {
                    /* Move to the parent folder */
                    currentFolder = currentFolder->topLevel;
                } else {
                    /* Create a new sub-folder under the current folder */
                    currentFolder = makeDir(currentFolder);
                }
            }
        } else {
            /* If the line is not a "change directory" command, assume it's a size value */
            /* Convert the size to an int */
            int size = atoi(buffer); 
             /* Update the size of the current folder */
            currentFolder->size += size;
            /* Update the sizes of top-level */
            updateTopLevelSizes(currentFolder, size); 
        }
    }
}


int main() {

    /* Read input */
    FILE* filePointer;
    filePointer = fopen("src/Day7/data.txt", "r");

    if (filePointer == NULL) {
        printf("Unable to read file!\n");
        return 1;
    }

    int result;

    /* Initialize the root folder. */
    Folder* root = makeDir(NULL);

    /* Read and process commands from input. */
    processCommands(filePointer, root);

    /* Get the sum of folders to delete (size < FOLDER_SIZE_LIMIT). */
    result = foldersToDelete(root);

    /* Print result */
    printf("The sum of the sub-level directories is: %d\n", result);

    fclose(filePointer);
    return 0;
}
