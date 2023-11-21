#include "shell.h"

typedef struct {
    char name[MAX_ALIAS_NAME];
    char value[MAX_ALIAS_VALUE];
} Alias;

Alias aliases[MAX_ALIASES];
int num_aliases = 0;

void my_alias(char **args) {
    if (args[1] == NULL) {
        int i;
        for (i = 0; i < num_aliases; i++) {
            char *name = aliases[i].name;
            char *value = aliases[i].value;
            while (*name)
                _putchar(*name++);
            _putchar('=');
            while (*value)
                _putchar(*value++);
            _putchar('\n');
        }
    } else {
        int i;
        for (i = 1; args[i]; i++) {
            char *name = args[i];
            char *value = strchr(args[i], '=');
            if (value) {
                *value++ = '\0';
            } else {
                value = "";
            }
            if (num_aliases >= MAX_ALIASES) {
                _putserr("Max number of aliases reached.\n");
                return;
            }
            if (len_str(name) >= MAX_ALIAS_NAME || len_str(value) >= MAX_ALIAS_VALUE) {
                _putserr("Alias name or value too long.\n");
                return;
            }
            _strcpy(aliases[num_aliases].name, name);
            _strcpy(aliases[num_aliases].value, value);
            num_aliases++;
        }
    }
}

