/* post-api.c */

#include <post.h>
#include <api.h>

void send_response(SOCKET client_socket, const char* status, const char* content_type, const char* body) {
    char response[BUFFER_SIZE];

    snprintf(response, sizeof(response),
        "HTTP/1.1 %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %llu\r\n"  // Use %llu for size_t cast to unsigned long long
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status, content_type, (unsigned long long)strlen(body), body);

    send(client_socket, response, strlen(response), 0);
}

void log_request(char *buffer, size_t length) {
    char *path = buffer + length;
    char *end_path = strchr(path, ' ');

    if (end_path) {
        *end_path = '\0';
    }

    printf("Requested path: %s\n", path);
}

void handle_post_request(SOCKET client_socket, const char *body) {
    /* GETTING THE TITLE */
    const char *title_str = "\"title\": \"";
    char *title_pos = strstr(body, title_str);

    if (!title_pos) {
        send_response(client_socket, BAD_REQUEST_400, APPLICATION_JSON_CONTENT_TYPE, "{\"message\": \"Missing title\"}");
        return;
    }

    title_pos += strlen(title_str); // Move the pointer to the start of the title value
    char *end_title_pos = strchr(title_pos, '"');
    if (!end_title_pos) {
        send_response(client_socket, BAD_REQUEST_400, APPLICATION_JSON_CONTENT_TYPE, "{\"message\": \"Invalid title format\"}");
        return;
    }

    // Dynamically allocate memory for the title string
    size_t title_length = end_title_pos - title_pos;
    char *title = malloc(title_length + 1);
    if (!title) {
        send_response(client_socket, INTERNAL_ERROR_500, APPLICATION_JSON_CONTENT_TYPE, "{\"message\": \"Memory allocation failed\"}");
        return;
    }
    strncpy(title, title_pos, title_length);
    title[title_length] = '\0'; // Null terminate the string

    printf("Received title: %s\n", title);

    /* GETTING THE DESCRIPTION */
    const char *description_str = "\"description\": \"";
    char *description_pos = strstr(body, description_str);

    if (!description_pos) {
        free(title);
        send_response(client_socket, BAD_REQUEST_400, APPLICATION_JSON_CONTENT_TYPE, "{\"message\": \"Missing description\"}");
        return;
    }

    description_pos += strlen(description_str); // Move the pointer to the start of the description value
    char *end_description_pos = strchr(description_pos, '"');
    if (!end_description_pos) {
        free(title);
        send_response(client_socket, BAD_REQUEST_400, APPLICATION_JSON_CONTENT_TYPE, "{\"message\": \"Invalid description format\"}");
        return;
    }

    // Dynamically allocate memory for the description string
    size_t description_length = end_description_pos - description_pos;
    char *description = malloc(description_length + 1);
    if (!description) {
        free(title);
        send_response(client_socket, INTERNAL_ERROR_500, APPLICATION_JSON_CONTENT_TYPE, "{\"message\": \"Memory allocation failed\"}");
        return;
    }
    strncpy(description, description_pos, description_length);
    description[description_length] = '\0'; // Null terminate the string

    printf("Received description: %s\n", description);

    /* SAVE THE POST IN MEMORY */
    
    char* id = add_post(title, description);
    if (!id) {
        free(title);
        free(description);
        send_response(client_socket, INTERNAL_ERROR_500, APPLICATION_JSON_CONTENT_TYPE, "{\"message\": \"Memory allocation failed\"}");
        return;
    }

    char response_body[BUFFER_SIZE];
    snprintf(
        response_body,
        sizeof(response_body), 
        "{\"message\": \"Post created successfully\", \"id\": \"%s\"}", id);

    // Send success response with a JSON message
    send_response(client_socket, OK_200, APPLICATION_JSON_CONTENT_TYPE, response_body);

    free(title);         // Free the allocated memory
    free(description);   // Free the allocated memory
}

void handle_post_client(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    int recv_size;
    char *headers_end;

    // Receive data from the client
    recv_size = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (recv_size == SOCKET_ERROR) {
        printf("Post recv failed with error code: %d\n", WSAGetLastError());
        return;
    }

    buffer[recv_size] = '\0';

    headers_end = strstr(buffer, "\r\n\r\n");
    if (!headers_end) {
        send_response(client_socket, BAD_REQUEST_400, TEXT_PLAIN_CONTENT_TYPE, "Invalid request format");
        closesocket(client_socket);
        return;
    }

    // Move to the start of the body (which is after the headers)
    char *body = headers_end + 4;

    if (strncmp(buffer, "POST ", 5) == 0) {
        log_request(buffer, 5);
        handle_post_request(client_socket, body);
    } else {
        send_response(client_socket, BAD_REQUEST_400, TEXT_PLAIN_CONTENT_TYPE, "Method not supported");
    }

    closesocket(client_socket);
}
