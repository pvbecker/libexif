#include "inc/libexif.h"
#include "inc/bytestream.h"

char* text =
"Further improvement will be made to this as time passes by; the ideia is to have this as an alternate\n\
way of using metadata tags on c/c++ code i've been working with for the past few months. Instead of \n\
using exiftool via a wrapped shell call, my goal is to have the image's metadata formatted for me,\n\
on a json or ASN1 structure.\n";

int consume(char *file, char* output_data){
    printf("start consuming file...\n");

    char buffer[65535] = {0};
    // need to figure out how to read only whats necessary, then start parsing all the contents appr
    // opriately. Still needs a little research on jpg/exif standards.
    // initialize the stream...
    bytestream_t *context = malloc(sizeof(bytestream_t));
    init_stream(context);

    context->open(file);

    int result = context->read(2, buffer);
    if(!result)
        return -1;
    if(!memcmp(buffer, EXIF_HEADER, sizeof(EXIF_HEADER)))
        printf("EXIF Image.\n");
    else if(!memcmp(buffer, JIFF_HEADER, sizeof(JIFF_HEADER)))
        printf("JIFF Image.\n");

    result = context->read(4, buffer);
    if(!result)
        return -1;

    context->close(context);
    printf("%s", text);

    return 0;
}

