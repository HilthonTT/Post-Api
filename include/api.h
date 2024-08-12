/* api.h */

#include <WinSock2.h>

#define BUFFER_SIZE 1024

#define BAD_REQUEST_400 "400 Bad Request"
#define OK_200 "200 Ok"
#define NOT_FOUND_400 "400 Not found"

#define TEXT_PLAIN_CONTENT_TYPE "text/plain"
#define APPLICATION_JSON_CONTENT_TYPE "application/json"

void handle_post_client(SOCKET client_socket);

static void send_response(SOCKET client_socket, const char* status, const char* content_type, const char* body) {
    char response[BUFFER_SIZE];

    snprintf(response, sizeof(response),
        "HTTP/1.1 %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %lu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status, content_type, strlen(body), body);

    send(client_socket, response, strlen(response), 0);
}

static int get_content_length(const char *headers) {
    const char *content_length_str = "Content-Length: ";
    char *content_length_pos = strstr(headers, content_length_str);

    // If Content-Length is found
    if (content_length_pos) {
        // Convert the content length from a string to an integer and return it
        return atoi(content_length_pos + strlen(content_length_str));
    }

    return 0;
}

static void log_request(char *buffer, size_t length) {
    char *path = buffer + length;
    char *end_path = strchr(path, ' ');

    if (end_path) {
        *end_path = '\0';
    }

    printf("Requested path: %s\n", path);
}