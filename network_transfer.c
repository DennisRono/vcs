#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> 
#include "network_transfer.h"

#pragma comment(lib, "ws2_32.lib") 

#define BUFFER_SIZE 1024
#define CONFIG_FILE ".vcs/config"


void initialize_winsock() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}


void cleanup_winsock() {
    WSACleanup();
}



void set_origin(const char *url) {
    FILE *config = fopen(CONFIG_FILE, "r+");
    if (!config) {
        perror("Error accessing config file");
        exit(EXIT_FAILURE);
    }

    fseek(config, 0, SEEK_END);
    fprintf(config, "origin=%s\n", url);
    fclose(config);

    printf("Set origin: %s\n", url);
}


void push_to_server(const char *server_ip, int port) {
    initialize_winsock();

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "Socket creation failed. Error Code: %d\n", WSAGetLastError());
        cleanup_winsock();
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Connection to server failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sock);
        cleanup_winsock();
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Sending repository data...\n");

    
    char buffer[BUFFER_SIZE];
    FILE *repo_data = fopen(".vcs/repository.zip", "rb");
    if (!repo_data) {
        fprintf(stderr, "Error: Could not open repository data for sending.\n");
        closesocket(sock);
        cleanup_winsock();
        exit(EXIT_FAILURE);
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, repo_data)) > 0) {
        if (send(sock, buffer, bytes_read, 0) < 0) {
            fprintf(stderr, "Error: Failed to send data. Error Code: %d\n", WSAGetLastError());
            fclose(repo_data);
            closesocket(sock);
            cleanup_winsock();
            exit(EXIT_FAILURE);
        }
    }
    fclose(repo_data);

    printf("Repository data sent successfully.\n");

    closesocket(sock);
    cleanup_winsock();
}


void fetch_from_server(const char *server_ip, int port) {
    initialize_winsock();

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "Socket creation failed. Error Code: %d\n", WSAGetLastError());
        cleanup_winsock();
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Connection to server failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sock);
        cleanup_winsock();
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Receiving repository data...\n");

    
    char buffer[BUFFER_SIZE];
    FILE *repo_data = fopen(".vcs/repository_received.zip", "wb");
    if (!repo_data) {
        fprintf(stderr, "Error: Could not open file for receiving data.\n");
        closesocket(sock);
        cleanup_winsock();
        exit(EXIT_FAILURE);
    }

    int bytes_received;
    while ((bytes_received = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, repo_data);
    }
    if (bytes_received < 0) {
        fprintf(stderr, "Error: Failed to receive data. Error Code: %d\n", WSAGetLastError());
        fclose(repo_data);
        closesocket(sock);
        cleanup_winsock();
        exit(EXIT_FAILURE);
    }
    fclose(repo_data);

    printf("Repository data received successfully.\n");

    closesocket(sock);
    cleanup_winsock();
}
