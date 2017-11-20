#ifndef _LS_MAP_
#define _LS_MAP_

#include "Tree.h"

typedef struct LS_Map
{
    float ** grid;
    int len;
} LS_Map;

LS_Map * LS_BuildMap(LS_Tree *);
void LS_ReleaseMap(LS_Map *);

#endif
