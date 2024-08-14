/* api.h */

#include <WinSock2.h>

#define BUFFER_SIZE 1024

#define BAD_REQUEST_400 "400 Bad Request"
#define OK_200 "200 Ok"
#define NOT_FOUND_404 "404 Not found"
#define INTERNAL_ERROR_500 "500 Internal Server Error"

#define TEXT_PLAIN_CONTENT_TYPE "text/plain"
#define APPLICATION_JSON_CONTENT_TYPE "application/json"

void handle_post_client(SOCKET client_socket);
