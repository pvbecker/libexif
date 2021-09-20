#include <stdint.h>

#define STARTER "\xff"
// start of image
#define SOI     0xd8
/*
Start of frame: this metadata will go from 0 to n, with the 4 least-significant
bits mapping to the nth Start-of-Frame. i.e.,
SOF0 -> \xff\xc0
SOF2 -> \xff\xc2
Can only go until 3
*/
#define SOFn    0xc0
/*
Define Huffman Table(s)
*/
#define DHT     0xc4
/*
Define Quantization Table
 */
#define DQT     0xdb
/*
Define Restart Interval
*/
#define DRI     0xdd
/*
Start of Scan
*/
#define SOS     0xda
/*
Restart, inserted at every R macroblocks, where R is set by the DRI interval.
This will not be used if DRI has not defined the interval.
*/
#define RSTn    0xd0
/*
Application-specific tag. APP1 is normally used for Exif JPEG.
*/
#define APPn    0xe0
// Comment
#define COM     0xfe
// End-of-Image
#define EOI     0xd9

typedef struct marker{
    char id[2];
    char len[2];
    int payload_size;
    char *payload;
} marker_t;
