/* api.h */

#include <winsock2.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define PORT 8080
#define BUFFER_SIZE = 1024

/* Function definitions */

int initialize_socket();

SOCKET initialize_server_socket();

void cleanup(SOCKET socket);
