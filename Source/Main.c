#include "Bmp.h"
#include "Map.h"
#include "Memory.h"
#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEPTH 4

int main()
{
    lsTree * ls = NULL;
    lsMap * map = NULL;
    int i, j;

    srand(time(NULL));
    lsBuildSystem(ls, NULL, 0, 0, 10.0, 1.0);
    lsExpand(ls, DEPTH, NULL);
    lsBuildMap(map, ls, DEPTH);

    for(i = 0; i < map->len; ++i)
    {
        printf("%4.2f", map->grid[i][0]);

        for(j = 1; j < map->len; ++j)
            printf(",%5.2f", map->grid[i][j]);

        printf("\n");
    }

    lsSaveBmp(map->grid, "Resources/cool.bmp", map->len, map->len);
    lsReleaseMap(map);
    lsReleaseSystem(ls);

    return 0;

    FAIL:
        printf("ERROR: Memory Error\n");
        lsReleaseSystem(ls);
        return -1;
}
