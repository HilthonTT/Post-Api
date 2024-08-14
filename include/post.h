/* post.h */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <rpc.h>

#ifdef _MSC_VER
#pragma comment(lib, "Rpcrt4.lib")
#endif

#define POST_ID_SIZE 37

typedef struct Post {
    char id[POST_ID_SIZE];
    char title[256];
    char description[512];
    struct Post *next;
} Post;

char* generate_identifier();

char* add_post(const char *title, const char *description);

void remove_post(const char *id);

Post* get_post(const char *id);

void free_posts();

bool update_post(const char *id, const char *new_title, const char *new_description);
