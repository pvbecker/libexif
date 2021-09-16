#include "inc/bytestream.h"

// bad practice, gonna think a little better on how to proceed.
bytestream_t *instance = NULL;

int open(const char *file_name){
    instance->file_name = file_name;
    instance->fd = fopen(file_name, "rb");

    return instance->fd != NULL;
}

int read(int num_bytes, char *buffer){
    size_t bytes_read = fread(buffer, sizeof(char), num_bytes, instance->fd);
    if(bytes_read > 0){
        instance->pointer += bytes_read;
        return bytes_read == num_bytes;
    }
    return bytes_read;
}

int close(void *context){
    int result = fclose(instance->fd);
    if(!result){
        free(context);
        free(instance);
    }
    return result;
}

void pretty(const char *data, int size){
    int i = 0;
    const char * stop = data + size;
    while(data != stop){
        printf("0x%1x ", *(data)++ & 0xffU);
    }
    printf("\n");
}

int init_stream(void * context){
    instance = malloc(sizeof(bytestream_t));
    instance->open = open;
    instance->read = read;
    instance->close = close;
    instance->pretty = pretty;
    instance->pointer = 0;

    memcpy(context, instance, sizeof(bytestream_t));

    return 0;
}