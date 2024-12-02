#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "stage.h"
#include "commit.h"
#include "network_transfer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "init") == 0) {
        init_repo();
    } else if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s add <file>\n", argv[0]);
            return EXIT_FAILURE;
        }
        stage_file(argv[2]);
    } else if (strcmp(argv[1], "commit") == 0) {
        if (argc < 4 || strcmp(argv[2], "-m") != 0) {
            fprintf(stderr, "Usage: %s commit -m <message>\n", argv[0]);
            return EXIT_FAILURE;
        }
        commit_changes(argv[3]);
    } else if (strcmp(argv[1], "set-origin") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s set-origin <url>\n", argv[0]);
            return EXIT_FAILURE;
        }
        set_origin(argv[2]);
    } else if (strcmp(argv[1], "push") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s push <server_ip> <port>\n", argv[0]);
            return EXIT_FAILURE;
        }
        push_to_server(argv[2], atoi(argv[3]));
    } else if (strcmp(argv[1], "fetch") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s fetch <server_ip> <port>\n", argv[0]);
            return EXIT_FAILURE;
        }
        fetch_from_server(argv[2], atoi(argv[3]));
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
