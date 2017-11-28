#include "Map.h"
#include "Memory.h"
#include <math.h>
#include <stdlib.h>

static int BuildGrid(lsMap *, lsTree *, unsigned int);
static void BuildSubGrid(lsMap *, lsTree *, int, int, int, int, int, float);
static float Normal(lsMap * map, int, int);

lsMap * _lsBuildMap(lsTree * ls, unsigned int depth)
{
    lsMap * map = NULL;

    /* This function requires the tree to not be null, otherwiss there is no data for the grid */
    if(ls == NULL)
        return NULL;

    /* Initialize the map, determine the depth of the tree, and then build the grid using the tree values */
    lsNewMem(map, sizeof(lsMap));
    map->len = (1 << (depth + 1)) + 1;

    if (!BuildGrid(map, ls, map->len))
    {
        lsDiscardMem(map);
        return NULL;
    }

    return map;

    FAIL:
        return NULL;
}

void lsReleaseMap(lsMap * map)
{
    int i;

    if (map == NULL)
        return;

    for (i = 0; i < map->len; ++i)
        lsDiscardMem(map->grid[i]);

    lsDiscardMem(map->grid);
    lsDiscardMem(map);
}

static int BuildGrid(lsMap * map, lsTree * ls, unsigned int len)
{
    float height = (float)(ls->height);
    int middle, end, i, j, l = len - 1;

    lsNewMem(map->grid, sizeof(float *) * len);

    for (i = 0; i < len; ++i)
    {
        lsNewMem(map->grid[i], sizeof(float) * len);

        for (j = 0; j < len; j++)
            map->grid[i][j] = 0.0;
    }

    end = len - 1;
    middle = len >> 1;
    map->grid[middle][middle] = height;

    if (ls->children != NULL)
    {
        BuildSubGrid(map, ls->children[0], 0, middle, 0, middle, 1, height);
        BuildSubGrid(map, ls->children[1], middle, end, 0, middle, 1, height);
        BuildSubGrid(map, ls->children[2], 0, middle, middle, end, 1, height);
        BuildSubGrid(map, ls->children[3], middle, end, middle, end, 1, height);
    }

    for (i = 1; i < l; ++i)
    {
        for (j = 1; j < l; j++)
        {
            if (map->grid[i][j] == 0.0)
                map->grid[i][j] = Normal(map, i, j);
        }
    }

    return 1;

    FAIL:
        lsDiscardMem(map->grid);
        return 0;
}

static void BuildSubGrid(lsMap * map, lsTree * ls, int xmin, int xmax, int ymin, int ymax, int depth, float height)
{
    float current = ls->height * pow(0.95, depth);
    int x = (xmin + xmax) >> 1, y = (ymin + ymax) >> 1;

    map->grid[x][y] = current;

    if (ls->children != NULL)
    {
        BuildSubGrid(map, ls->children[0], xmin, x, ymin, y, depth + 1, current);
        BuildSubGrid(map, ls->children[1], x, xmax, ymin, y, depth + 1, current);
        BuildSubGrid(map, ls->children[2], xmin, x, y, ymax, depth + 1, current);
        BuildSubGrid(map, ls->children[3], x, xmax, y, ymax, depth + 1, current);
    }
}

static float Normal(lsMap * map, int x, int y)
{
    float total = 0.0;
    unsigned int count = 0, xmax = x + 1, ymax = y + 1, i, j;

    for (i = x - 1; i <= xmax; ++i)
    {
        for (j = y - 1; j <= ymax; ++j)
        {
            if (map->grid[i][j] != 0.0)
            {
                total += map->grid[i][j];
                ++count;
            }
        }
    }

    return count != 0 ? total / count : 0.0;
}
