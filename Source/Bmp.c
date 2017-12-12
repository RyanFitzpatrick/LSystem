#include "Bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lsSaveBmp(float ** map, const char * name, unsigned int width, unsigned int height)
{
    FILE * file;
    unsigned char * img = NULL;
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};
    unsigned int filesize = 54 + (3 * width * height), i , j, x, y, pixel;

    img = malloc(3 * width * height);
    memset(img, 0, (3 * width * height));

    for (i = 0; i < width; ++i)
    {
        for(j = 0; j < height; ++j)
        {
            x = i;
            y = (height - 1) - j;
            pixel = (unsigned int)(map[i][j] * 10);
            if (pixel > 255) pixel = 255;
            img[(x + (y * width)) * 3] = pixel;
            img[(x + (y * width)) * 3 + 1] = pixel;
            img[(x + (y * width)) * 3 + 2] = pixel;
        }
    }

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4] = (unsigned char)(width);
    bmpinfoheader[5] = (unsigned char)(width >> 8);
    bmpinfoheader[6] = (unsigned char)(width >> 16);
    bmpinfoheader[7] = (unsigned char)(width >> 24);
    bmpinfoheader[8] = (unsigned char)(height);
    bmpinfoheader[9] = (unsigned char)(height >> 8);
    bmpinfoheader[10] = (unsigned char)(height >> 16);
    bmpinfoheader[11] = (unsigned char)(height >> 24);

    file = fopen("Resources/heightmap.bmp","wb");
    fwrite(bmpfileheader,1,14,file);
    fwrite(bmpinfoheader,1,40,file);

    for(i = 0; i < height; ++i)
    {
        fwrite(img + (width * (height - i - 1) * 3), 3, width, file);
        fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, file);
    }

    free(img);
    fclose(file);
}
