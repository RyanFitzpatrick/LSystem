#include "Map.h"
#include "Memory.h"
#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    LS_Tree * ls = LS_BuildSystem(NULL, LS_ZERO, LS_TWO);
    LS_Map * map;
    int i, j;

    LS_Expand(ls, NULL);

    for(i = 0; i < 4; ++i)
    {
        LS_Expand(ls->children[i], NULL);

        for(j = 0; j < 4; ++j)
            LS_Expand(ls->children[i]->children[j], NULL);
    }

    map = LS_BuildMap(ls);

    for(i = 0; i < map->len; ++i)
    {
        printf("%4.2f", map->grid[i][0]);
        for(j = 1; j < map->len; ++j)
            printf(",%5.2f", map->grid[i][j]);

        printf("\n");
    }

    LS_ReleaseMap(map);
    LS_ReleaseSystem(ls);

    return 0;
}
