#include "Map.h"
#include "Memory.h"
#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>

#define DEPTH 8

int main()
{
    lsTree * ls = NULL;
    lsMap * map = NULL;
    int i, j;

    lsBuildSystem(ls, NULL, 0, 2);
    lsExpand(ls, DEPTH, NULL);
    lsBuildMap(map, ls, DEPTH, 0);

    for(i = 0; i < map->len; ++i)
    {
        printf("%4.2f", map->grid[i][0]);

        for(j = 1; j < map->len; ++j)
            printf(",%5.2f", map->grid[i][j]);

        printf("\n");
    }

    lsReleaseMap(map);
    lsReleaseSystem(ls);

    return 0;

    FAIL:
        printf("ERROR: Memory Error\n");
        lsReleaseSystem(ls);
        return -1;
}
