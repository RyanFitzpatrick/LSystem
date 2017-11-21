#ifndef _LS_MAP_
#define _LS_MAP_

#include "Tree.h"

typedef struct lsMap
{
    float ** grid;
    unsigned int len;
} lsMap;

lsMap * _lsBuildMap(lsTree *, unsigned int, unsigned int);
void lsReleaseMap(lsMap *);

#define lsBuildMap(map, tree, depth, height) if ((map = _lsBuildMap(tree, depth, height)) == NULL) goto FAIL

#endif
