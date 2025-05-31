#ifndef DYN_STR
#define DYN_STR

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#define INIT_CAP 2

typedef struct {
    const char** str; 
    size_t len;
    size_t cap;
}string_buf;


#define do_append(buf, new_elem, elem_type)                                            \
    do {                                                                               \
        if ((buf)->cap == (buf)->len) {                                                \
            (buf)->cap = ((buf)->cap == 0) ? INIT_CAP : (buf)->cap * 2;                    \
            (buf)->str = (elem_type*)realloc((buf)->str, sizeof(elem_type) * (buf)->cap); \
            assert((buf)->str != NULL && "Unable to allocate new memory");                 \
        }                                                                              \
        (buf)->str[(buf)->len++] = new_elem;                                            \
    }while(0);

#define append(elem, ...) append_with_null(elem, __VA_ARGS__, NULL) 

void append_with_null(string_buf* elem, ...) {
    va_list args;
    va_start(args, elem);
    const char* arg = va_arg(args, const char*);
    while (arg != NULL) {
        do_append(elem, arg, const char*);
        arg = va_arg(args, const char*);
    }
    va_end(args);
}

void clear_str_buff(string_buf* str);

#endif
