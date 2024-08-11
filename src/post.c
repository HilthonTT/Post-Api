/* post.c */

#include <post.h>

Post *post_list = NULL;

char* generate_identifier() {
    static char identifier[37];

    srand(time(NULL));

    // Generate four 32-bit random numbers
    unsigned int num1 = rand();
    unsigned int num2 = rand();
    unsigned int num3 = rand();
    unsigned int num4 = rand();

    // Convert the random numbers to a string
    sprintf(
        identifier, 
        "%08x-%04x-%04x-%04x-%08x%04x",
        num1, num2 >> 16, num2 & 0xFFFF,
        num3 >> 16, num3 & 0xFFFF, num4);

    printf("Generated identifier!");

    return identifier;
}

void add_post(const char *title, const char *description) {
    Post *new_post = (Post *)malloc(sizeof(Post));
    
    if (new_post == NULL) {
        printf("Memory allocated failed for the new post\n");
        return;
    }

    char *id = generate_identifier();

    strncpy(new_post->id, id, sizeof(new_post->id)- 1);
    new_post->id[sizeof(new_post->id) - 1] = '\0';

    strncpy(new_post->title, title, sizeof(new_post->title) -1);
    new_post->title[sizeof(new_post->title) - 1] = '\0';

    strncpy(new_post->description, description, sizeof(new_post->description) - 1);
    new_post->description[sizeof(new_post->description) -1 ] = '\0';

    new_post->next = post_list;
    post_list = new_post;
}

void remove_post(const char *id) {
    Post *current = post_list;
    Post *previous = NULL;

    while (current != NULL) {
        bool post_found = (strcmp(current->id, id) == 0);

        if (post_found) {
            // Post with matching id found
            if (previous == NULL) {
                // The post to delete is the head of the list
                post_list = current->next;
            } else {
                // Bypass the current post
                previous->next = current->next;
            }

            // Free the memory allocated for the post
            free(current);
            printf("Post with Id = '%s' was found and deleted.\n", id);

            // Move to the next post in the list
            current = (previous == NULL) ? post_list : previous->next;

            // If you want to remove only the first occurrence, break the loop here
            return;
        }

        // Move to the next post in the list
        previous = current;
        current = current->next;
    }

    // If no post with the given id was found
    printf("The post with Id = '%s' was not found in the posts.\n", id);
}

Post* get_post(const char *id) {
    Post *current = post_list;

    while (current != NULL) {
        bool post_found = (strcmp(current->id, id) == 0);
        
        if (post_found) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void free_posts() {
    Post *current = post_list;

    while (current != NULL) {
        Post *next = current->next;
        free(current);
        current = next;
    }

    post_list = NULL;
}
