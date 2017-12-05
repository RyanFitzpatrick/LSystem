typedef struct lsBmpFileHeader
{
    unsigned short  type;
    unsigned int    size;
    unsigned short  reserved1;
    unsigned short  reserved2;
    unsigned int    offBits;
} lsBmpFileHeader;

typedef struct lsBmpInfoHeader
{
    unsigned int    size;
    int             width;
    int             height;
    unsigned short  planes;
    unsigned short  bitCount;
    unsigned int    compression;
    unsigned int    sizeImage;
    int             xPelsPerMeter;
    int             yPelsPerMeter;
    unsigned int    clrUsed;
    unsigned int    clrImportant;
} lsBmpInfoHeader;

void lsSaveBmp(float **, const char *, unsigned int, unsigned int);
