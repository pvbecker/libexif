#include "inc/libexif.h"

int main(int argc, char **argv){
    if(argc < 2){
        printf("Please specify a file to be opened. i.e\n \
                libexif <filepath>\n");
        return -1;
    }
    printf("hello, start parsing...\n");
    printf("%s\n", argv[1]);
    char *result;
    consume(argv[1], result);
    return 0;
}