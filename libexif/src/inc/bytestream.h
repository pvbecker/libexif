#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libexif.h"

typedef struct stream{
    struct stream * instance;
    const char* file_name;
    FILE *fd;
    int pointer;
    /* opens file. */
    int (*open)(const char *);
    /*
    reads N bytes from file currently opened and places the read results in
    the pre-allocated buffer set as input argument */
    int (*read)(int, char*);

    int (*close)();
    void (*pretty)(const char *, int);
} bytestream_t;

int init_stream(void * context);