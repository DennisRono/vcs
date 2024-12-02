#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "commit.h"

#define STAGING_DIR ".vcs/staging"
#define COMMITS_DIR ".vcs/commits"

void commit_changes(const char *message) {
    time_t now = time(NULL);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", localtime(&now));

    char commit_dir[256];
    snprintf(commit_dir, sizeof(commit_dir), "%s/%s", COMMITS_DIR, timestamp);
    create_directory(commit_dir);

    char command[256];
    snprintf(command, sizeof(command), "cp -r %s/* %s", STAGING_DIR, commit_dir);
    if (system(command) != 0) {
        fprintf(stderr, "Error committing changes.\n");
        exit(EXIT_FAILURE);
    }

    char commit_file[256];
    snprintf(commit_file, sizeof(commit_file), "%s/message.txt", commit_dir);
    FILE *commit_msg = fopen(commit_file, "w");
    if (!commit_msg) {
        perror("Error creating commit message file");
        exit(EXIT_FAILURE);
    }
    fprintf(commit_msg, "%s\n", message);
    fclose(commit_msg);

    printf("Committed changes with message: %s\n", message);

    snprintf(command, sizeof(command), "rm -rf %s/*", STAGING_DIR);
    if (system(command) != 0) {
        fprintf(stderr, "Error clearing staging area.\n");
        exit(EXIT_FAILURE);
    }
}
