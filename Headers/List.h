#ifndef _LS_LIST_
#define _LS_LIST_

#include "Tree.h"

typedef struct LS_List
{
    LS_NUM num;
    struct LS_List * next;
} LS_List;

LS_List * LS_Append(LS_List *, LS_NUM);
LS_List * BuildList(LS_List *, LS_Tree *, unsigned int);
void LS_ReleaseList(LS_List *);

#endif
