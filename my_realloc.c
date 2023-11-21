#include "shell.h"


/**
 * my_realloc - reallocate a new size buffer
 * @ptr: new string to save
 * @new_size: new size to allocate
 * 
 * return : a pointer to new allocated memory
*/

void *my_realloc(void *ptr, unsigned int new_size) {
    void *mem;
    char *ptr_copy, *filler;
    size_t old_size, index;

    if (ptr == NULL) {
        mem = malloc(new_size);
        if (mem == NULL) {
            return NULL;
        }

        return mem;
    }

    old_size = len_str((char *)ptr) + 1;

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    ptr_copy = ptr;
    mem = malloc(sizeof(*ptr_copy) * new_size);
    if (mem == NULL) {
        free(ptr);
        return NULL;
    }

    filler = mem;

    for (index = 0; index < old_size && index < new_size; index++) {
        filler[index] = *ptr_copy++;
    }

    free(ptr);
    return mem;
}

