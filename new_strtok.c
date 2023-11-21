#include "shell.h"


/**
 * new_strtok - function that split a string based on delimiters
 * @str: pointer to the string to split
 * @delim: delimiters
 *
 * return:  pointer to the new string splitted
*/
char* new_strtok(char* str, const char* delim) {
    static char* next = NULL;
    char* start;
    int in_token = 0;
    int is_delim = 0;
    const char* d;
    int found_delim = 0;

    if (str == NULL) {
        str = next;
    }

    if (str == NULL) {
        
        return NULL;
    }
    while (*str) {
        

        for (d = delim; *d; d++) {
            if (*str == *d) {
                is_delim = 1;
                break;
            }
        }

        if (!in_token && is_delim) {
            str++;
        } else {
            if (!in_token) {
                start = str;
                in_token = 1;
            }

            
            for (d = delim; *d; d++) {
                if (*str == *d) {
                    *str = '\0';
                    next = str + 1; 
                    in_token = 0;
                    found_delim = 1;
                    break;
                }
            }

            if (!found_delim) 
                str++;
            else 
                return start;
        }
    }


    if (in_token) {
        next = NULL;
        return start;
    }

    return NULL;
}

