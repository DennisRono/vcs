#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "stage.h"

#define STAGING_DIR ".vcs/staging"

void stage_file(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0) {
        fprintf(stderr, "File not found: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char command[256];
    snprintf(command, sizeof(command), "cp %s %s", filename, STAGING_DIR);
    if (system(command) != 0) {
        fprintf(stderr, "Error staging file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    printf("Staged file: %s\n", filename);
}
