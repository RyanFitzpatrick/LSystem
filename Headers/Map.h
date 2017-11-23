/* Map.h: Defines various types, prototypes, and macros used for height maps */

#ifndef _LS_MAP_
#define _LS_MAP_

/* Map.h requires the Tree type defined in Tree.h */
#include "Tree.h"

/* The structure used to represent a height map */
typedef struct lsMap
{
    /* The square matrix of floats containing the heights */
    float ** grid;
    /* The side length of the square height matrix */
    unsigned int len;
} lsMap;

/* Initializes a new height map based on an existing LSystem Tree */
/* NOTE: It's recommended to use the lsBuildMap macro instead of calling this directly */
/* Param1 lsTree *: The Tree used to define the heights for the map */
/* Param2 unsigned int: The max depth to search the Tree for height values */
/* Param3 unsigned int: The initial heights for the map */
/* Returns: A newly allocated height map containing values from the Tree */
lsMap * _lsBuildMap(lsTree *, unsigned int, unsigned int);

/* Frees all memory associated with a height map */
/* Param1 lsMap *: The map to be released */
void lsReleaseMap(lsMap *);

/* Calls the _lsBuildMap function and jumps to the FAIL label on error */
/* This is the recommened way to Build a height map */
#define lsBuildMap(map, tree, depth, height) if ((map = _lsBuildMap(tree, depth, height)) == NULL) goto FAIL

#endif
