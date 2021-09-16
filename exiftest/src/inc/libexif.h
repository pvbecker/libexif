#include <stdio.h>
#include <stdlib.h>


#define EXIF_HEADER "\x49\x49"
#define JIFF_HEADER "\xff\xd8"

int consume(char *file, char* output_data);