#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "init.h"

#define REPO_DIR ".vcs"
#define STAGING_DIR ".vcs/staging"
#define COMMITS_DIR ".vcs/commits"
#define CONFIG_FILE ".vcs/config"

void create_directory(const char *path) {
#ifdef _WIN32
    if (mkdir(path) != 0) {
#else
    if (mkdir(path, 0777) != 0) {
#endif
        perror("Error creating directory");
        exit(EXIT_FAILURE);
    }
}


void init_repo() {
    if (access(REPO_DIR, F_OK) == 0) {
        fprintf(stderr, "Repository already exists.\n");
        return;
    }

    create_directory(REPO_DIR);
    create_directory(STAGING_DIR);
    create_directory(COMMITS_DIR);

    FILE *head = fopen(REPO_DIR "/HEAD", "w");
    if (!head) {
        perror("Error creating HEAD file");
        exit(EXIT_FAILURE);
    }
    fprintf(head, "main\n");
    fclose(head);

    FILE *config = fopen(CONFIG_FILE, "w");
    if (!config) {
        perror("Error creating config file");
        exit(EXIT_FAILURE);
    }
    fprintf(config, "origin=\n");
    fclose(config);

    printf("Initialized empty repository in %s\n", REPO_DIR);
}
