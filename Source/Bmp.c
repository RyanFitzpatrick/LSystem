#include "Bmp.h"
#include <stdio.h>
#include <string.h>

void lsSaveBmp(float ** map, const char * name, unsigned int width, unsigned int height)
{
    FILE * file;
    lsBmpFileHeader bitmapFileHeader;
    lsBmpInfoHeader bitmapInfoHeader;
    unsigned char grayscale[5];
    char bmpFileStr[sizeof(lsBmpFileHeader) + 1];
    char bmpInfoStr[sizeof(lsBmpInfoHeader) + 1];
    char pixel;
    int i, j;

    memset(&bitmapFileHeader, 0xff, sizeof(lsBmpFileHeader));
    bitmapFileHeader.type = ( 'B' | 'M' << 8 );
    bitmapFileHeader.offBits = sizeof(lsBmpFileHeader) + sizeof(lsBmpFileHeader);
    bitmapFileHeader.size = bitmapFileHeader.offBits + (width + (width % 4 ? (4 - width % 4) : 0)) * height;
    memcpy(bmpFileStr, &bitmapFileHeader, sizeof(lsBmpFileHeader));
    bmpFileStr[sizeof(lsBmpFileHeader)] = '\0';

    memset(&bitmapInfoHeader, 0, sizeof(lsBmpInfoHeader));
    bitmapInfoHeader.size = sizeof(lsBmpInfoHeader);
    bitmapInfoHeader.width = width;
    bitmapInfoHeader.height = height;
    bitmapInfoHeader.planes = 1;
    bitmapInfoHeader.bitCount = 8;
    memcpy(bmpInfoStr, &bitmapInfoHeader, sizeof(lsBmpInfoHeader));
    bmpInfoStr[sizeof(lsBmpInfoHeader)] = '\0';

    file = fopen(name, "wb");
    fprintf(file, "%s%s", bmpFileStr, bmpInfoStr);


    for (i = 0; i < 256; ++i)
    {
        memset(grayscale, i, sizeof(grayscale));
        grayscale[4] = '\0';
        fprintf(file, "%s", grayscale);
    }

    for (i = 0; i < height; ++i)
    {
        for (j = 0; j < width; ++j)
        {
                pixel = (char)(200 * map[i][j]);
                fprintf(file, "%c", pixel);
        }
    }

    fclose(file);
}
