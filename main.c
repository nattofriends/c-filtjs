#include <stdio.h>
#include <stdlib.h>
#include "msvcrt.h"
#include "demangle.h"

#include "talloc.h"

#define BUFFER_SIZE 1024

/* Parent for allocations */
static void* dummy_parent;

char* __cdecl __unDName(char *, const char*, int, malloc_func_t, free_func_t, unsigned short int);

char* undname(const char*);

char* __cxa_demangle (const char *mangled, char *buf, size_t *len, int *status);

char* cplus_demangle_v3 (const char *mangled, int options);

char* demangle(const char*);

void* und_alloc(struct parsed_symbol* sym, unsigned int len) {
    return talloc(len, dummy_parent);
}

void und_free_all(struct parsed_symbol* sym) {
    tfree(dummy_parent);
}

char* undname(const char* decorated) {
    dummy_parent = talloc(sizeof(int), NULL);

    char* undecorated = calloc(BUFFER_SIZE, sizeof(char));

    __unDName(undecorated, decorated, BUFFER_SIZE, malloc, free, UNDNAME_COMPLETE);

    // __unDName's behavior in case of failure is to return the mangled string
    // (despite what the documentation says).
    if (0 == strcmp(decorated, undecorated))
        return NULL;

    return undecorated;
}

char* demangle(const char* mangled) {
    // Note: __cxa_demangle default is DMGL_PARAMS | DMGL_TYPES,
    // while standalone default is  DMGL_PARAMS | DMGL_TYPES
    char* demangled = cplus_demangle_v3(mangled, DMGL_PARAMS | DMGL_TYPES);

    return demangled;
}
