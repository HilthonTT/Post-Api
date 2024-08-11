/* post.h */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct Post {
    char id[37];
    char title[256];
    char description[512];
    struct Post *next;
} Post;

char* generate_identifier();

void add_post(const char *title, const char *description);

void remove_post(const char *id);

Post* get_post(const char *id);

void free_posts();
