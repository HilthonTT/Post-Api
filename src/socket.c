/* socket.c */

#include "socket.h"
#include <api.h>

int initialize_socket() {
    WSADATA wsa;

    printf("Initializing Winsock...\n");

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize winsock with error code: %d\n", WSAGetLastError());
        return -1;
    }

    return 0;
}

SOCKET initialize_server_socket() {
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == INVALID_SOCKET) {
        printf("Failed to create the server socket with error code: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed with error code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        return INVALID_SOCKET;
    }

    if (listen(server_socket, 3) == SOCKET_ERROR) {
        printf("Listening failed for server_socekt with error code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        return INVALID_SOCKET;
    }

    return server_socket;
}

void cleanup(SOCKET socket) {
    if (socket != INVALID_SOCKET) {
        closesocket(socket);
    }

    WSACleanup();
}

int main() {
    if (initialize_socket() != 0) {
        fprintf(stderr, "Failed to initialize Winsock\n");
        return 1;
    }

    SOCKET server_socket = initialize_server_socket();
    if (server_socket == INVALID_SOCKET) {
        cleanup(server_socket);
    }

    printf("Waiting for incoming connections on %d\n", PORT);

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    SOCKET client_socket;

    while (true) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_socket == INVALID_SOCKET) {
            printf("Accept failed with error code: %d\n", WSAGetLastError());
            break;
        }

        handle_post_client(client_socket);
    }

    cleanup(server_socket);

    return 0;
}