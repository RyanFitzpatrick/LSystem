#ifndef _LS_TREE_
#define _LS_TREE_

typedef enum
{
    LS_ZERO = 0,
    LS_ONE = 1,
    LS_TWO = 2,
    LS_THREE = 3
} LS_NUM;

typedef struct LS_Tree
{
    LS_NUM node;
    LS_NUM height;
    struct LS_Tree * parent;
    struct LS_Tree ** children;
} LS_Tree;

LS_Tree * LS_BuildSystem(LS_Tree *, LS_NUM, LS_NUM);
void LS_Expand(LS_Tree *, LS_Tree ** (*)(LS_Tree *, LS_NUM));
int LS_Depth(LS_Tree *);
void LS_ReleaseSystem(LS_Tree *);

#endif
