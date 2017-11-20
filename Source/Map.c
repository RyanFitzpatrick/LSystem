#include "Map.h"
#include "Memory.h"
#include <stdlib.h>

static void BuildGrid(LS_Map *, LS_Tree *, int);
static void BuildNWGrid(LS_Map *, LS_Tree *, int, int, int, int, int, float);
static void BuildNEGrid(LS_Map *, LS_Tree *, int, int, int, int, int, float);
static void BuildSEGrid(LS_Map *, LS_Tree *, int, int, int, int, int, float);
static void BuildSWGrid(LS_Map *, LS_Tree *, int, int, int, int, int, float);

LS_Map * LS_BuildMap(LS_Tree * ls)
{
    LS_Map * map;

    /* This function requires the tree to not be null, otherwiss there is no data for the grid */
    if(ls == NULL)
        return NULL;

    /* Initialize the map, determine the depth of the tree, and then build the grid using the tree values */
    map = LS_BuildResource(sizeof(LS_Map));
    map->len = (1 << LS_Depth(ls)) + 1;
    BuildGrid(map, ls, map->len);

    return map;
}

static void BuildGrid(LS_Map * map, LS_Tree * ls, int len)
{
    float height = (float)(ls->height);
    int middle, end, i, j;

    map->grid = LS_BuildResource(sizeof(float *) * len);

    for(i = 0; i < len; ++i)
    {
        map->grid[i] = LS_BuildResource(sizeof(float) * len);

        for(j = 0; j < len; j++)
            map->grid[i][j] = 0.0;
    }

    end = len - 1;
    middle = len >> 1;
    map->grid[middle][middle] = height;

    if(ls->children != NULL)
    {
        BuildNWGrid(map, ls->children[0], 0, middle, 0, middle, 1, height);
        BuildNEGrid(map, ls->children[1], 0, middle, middle, end, 1, height);
        BuildSEGrid(map, ls->children[2], middle, end, middle, end, 1, height);
        BuildSWGrid(map, ls->children[3], middle, end, 0, middle, 1, height);
    }
}

static void BuildNWGrid(LS_Map * map, LS_Tree * ls, int xmin, int xmax, int ymin, int ymax, int depth, float height)
{
    float current = height + ((float)(ls->height) / (1 << depth));
    int x = (xmin + xmax) >> 1, y = (ymin + ymax) >> 1;

    map->grid[x][y] = current;
    map->grid[x][ymin] = (map->grid[xmin][ymin] + map->grid[xmax][ymin]) / 2;
    map->grid[xmin][y] = (map->grid[xmin][ymin] + map->grid[xmin][ymax]) / 2;
    map->grid[x][ymax] = (map->grid[xmin][ymax] + map->grid[xmax][ymax]) / 2;

    if(ls->children != NULL)
    {
        BuildNWGrid(map, ls->children[0], xmin, x, ymin, y, depth + 1, current);
        BuildNEGrid(map, ls->children[1], xmin, x, y, ymax, depth + 1, current);
        BuildSEGrid(map, ls->children[2], x, xmax, y, ymax, depth + 1, current);
        BuildSWGrid(map, ls->children[3], x, xmax, ymin, y, depth + 1, current);
    }
}

static void BuildNEGrid(LS_Map * map, LS_Tree * ls, int xmin, int xmax, int ymin, int ymax, int depth, float height)
{
    float current = height + ((float)(ls->height) / (1 << depth));
    int x = (xmin + xmax) >> 1, y = (ymin + ymax) >> 1;

    map->grid[x][y] = current;
    map->grid[xmin][y] = (map->grid[xmin][ymin] + map->grid[xmin][ymax]) / 2;
    map->grid[x][ymax] = (map->grid[xmin][ymax] + map->grid[xmax][ymax]) / 2;
    map->grid[xmax][y] = (map->grid[xmax][ymin] + map->grid[xmax][ymax]) / 2;

    if(ls->children != NULL)
    {
        BuildNWGrid(map, ls->children[0], xmin, x, ymin, y, depth + 1, current);
        BuildNEGrid(map, ls->children[1], xmin, x, y, ymax, depth + 1, current);
        BuildSEGrid(map, ls->children[2], x, xmax, y, ymax, depth + 1, current);
        BuildSWGrid(map, ls->children[3], x, xmax, ymin, y, depth + 1, current);
    }
}

static void BuildSEGrid(LS_Map * map, LS_Tree * ls, int xmin, int xmax, int ymin, int ymax, int depth, float height)
{
    float current = height + ((float)(ls->height) / (1 << depth));
    int x = (xmin + xmax) >> 1, y = (ymin + ymax) >> 1;

    map->grid[x][y] = current;
    map->grid[x][ymax] = (map->grid[xmin][ymax] + map->grid[xmax][ymax]) / 2;
    map->grid[xmax][y] = (map->grid[xmax][ymin] + map->grid[xmax][ymax]) / 2;
    map->grid[x][ymin] = (map->grid[xmin][ymin] + map->grid[xmax][ymin]) / 2;

    if(ls->children != NULL)
    {
        BuildNWGrid(map, ls->children[0], xmin, x, ymin, y, depth + 1, current);
        BuildNEGrid(map, ls->children[1], xmin, x, y, ymax, depth + 1, current);
        BuildSEGrid(map, ls->children[2], x, xmax, y, ymax, depth + 1, current);
        BuildSWGrid(map, ls->children[3], x, xmax, ymin, y, depth + 1, current);
    }
}

static void BuildSWGrid(LS_Map * map, LS_Tree * ls, int xmin, int xmax, int ymin, int ymax, int depth, float height)
{
    float current = height + ((float)(ls->height) / (1 << depth));
    int x = (xmin + xmax) >> 1, y = (ymin + ymax) >> 1;

    map->grid[x][y] = current;
    map->grid[xmax][y] = (map->grid[xmax][ymin] + map->grid[xmax][ymax]) / 2;
    map->grid[x][ymin] = (map->grid[xmin][ymin] + map->grid[xmax][ymin]) / 2;
    map->grid[xmin][y] = (map->grid[xmin][ymin] + map->grid[xmin][ymax]) / 2;

    if(ls->children != NULL)
    {
        BuildNWGrid(map, ls->children[0], xmin, x, ymin, y, depth + 1, current);
        BuildNEGrid(map, ls->children[1], xmin, x, y, ymax, depth + 1, current);
        BuildSEGrid(map, ls->children[2], x, xmax, y, ymax, depth + 1, current);
        BuildSWGrid(map, ls->children[3], x, xmax, ymin, y, depth + 1, current);
    }
}
