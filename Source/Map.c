#include "Map.h"
#include "Memory.h"
#include <math.h>
#include <stdlib.h>

static void FillMap(lsMap *, lsTree *, unsigned int, unsigned int, unsigned int);

lsMap * _lsBuildMap(lsTree * ls, unsigned int depth)
{
    lsMap * map = NULL;
    unsigned int i;

    /* This function requires the tree to not be null, otherwiss there is no data for the grid */
    if(ls == NULL)
        return NULL;

    /* Initialize the map, determine the depth of the tree, and then build the grid using the tree values */
    lsNewMem(map, sizeof(lsMap));
    map->len = 1 << depth;

    lsNewMem(map->grid, sizeof(float *) * map->len);

    for (i = 0; i < map->len; ++i)
        lsNewMem(map->grid[i], sizeof(float) * map->len);

    FillMap(map, ls, 0, 0, map->len);
    return map;

    FAIL:
        lsReleaseMap(map);
        return NULL;
}

void lsReleaseMap(lsMap * map)
{
    unsigned int i;

    if (map == NULL)
        return;

    for (i = 0; i < map->len; ++i)
        lsDiscardMem(map->grid[i]);

    lsDiscardMem(map->grid);
    lsDiscardMem(map);
}

static void FillMap(lsMap * map, lsTree * ls, unsigned int x, unsigned int y, unsigned int len)
{
    unsigned int xa, ya;

    if (len == 1)
    {
        map->grid[x][y] = ls->height;
        return;
    }

    len >>= 1;
    xa = x + len;
    ya = y + len;

    if (ls->children == NULL)
        lsExpand(ls, 1, NULL);

    FillMap(map, ls->children[0], x, y, len);
    FillMap(map, ls->children[1], xa, y, len);
    FillMap(map, ls->children[2], x, ya, len);
    FillMap(map, ls->children[3], xa, ya, len);

    FAIL:
        return;
}
