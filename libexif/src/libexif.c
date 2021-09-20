#include "inc/libexif.h"
#include "inc/bytestream.h"
#include "inc/jpg_meta.h"

char* text =
"Further improvement will be made to this as time passes by; the ideia is to have this as an alternate\n\
way of using metadata tags on c/c++ code i've been working with for the past few months. Instead of \n\
using exiftool via a wrapped shell call, my goal is to have the image's metadata formatted for me,\n\
on a json or ASN1 structure.\n";

void parse_jiff(bytestream_t *context, char * buffer);

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
        parse_jiff(context, buffer);

    context->close(context);
    printf("%s", text);

    return 0;
}

void parse_jiff(bytestream_t *context, char * buffer){
    bool read_eof = false;
    do{
        marker_t *data = malloc(sizeof(marker_t));
        context->read(2, data->id);
        context->pretty(data->id, 2);
        // check if its still a correct marker (i.e., first byte is FF)
        if(!memcmp(&data->id[0], "\xff", sizeof(char)))
            read_eof = true;
            break;
        context->read(2, data->len);
        context->pretty(data->len, 2);
        int msb = (unsigned char)data->len[0] << 2;
        int lsb = (unsigned char)data->len[1];
        if(msb + lsb == 0)
            break;
        data->payload_size = msb + lsb - 2;
        printf("payload length: %d\n", data->payload_size);
        data->payload = malloc(data->payload_size);
        context->read(data->payload_size, data->payload);

        printf("data read: \n");
        printf("id: ");
        context->pretty(data->id, 2);
        printf("len: ");
        context->pretty(data->len, 2);
    }while(!read_eof);

    context->pretty(buffer, 20);
}