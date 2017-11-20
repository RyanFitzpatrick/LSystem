#include "Tree.h"
#include "Memory.h"
#include <stdlib.h>

static LS_Tree ** Expand(LS_Tree *, LS_NUM);

LS_Tree * LS_BuildSystem(LS_Tree * parent, LS_NUM node, LS_NUM height)
{
    LS_Tree * ls = LS_BuildResource(sizeof(LS_Tree));

    /* Initalize the new tree node using the given parameters */
    ls->node = node;
    ls->height = height;
    ls->parent = parent;
    ls->children = NULL;

    return ls;
}

void LS_Expand(LS_Tree * ls, LS_Tree ** (* expand)(LS_Tree *, LS_NUM))
{
    /* If the node is NULL or if it already has children then stop */
    if(ls == NULL || ls->children != NULL)
        return;

    /* If no expand function is given then use a default one */
    if(expand == NULL)
        expand = Expand;

    /* Initalize all of the nodes children */
    ls->children = expand(ls, ls->node);
}

int LS_Depth(LS_Tree * ls)
{
    LS_Tree * temp;
    int depth;

    /* A NULL tree has no depth */
    if(ls == NULL)
        return 0;

    temp = ls;
    depth = 1;

    /* Count all the nodes on the way to the end of the complete tree */
    while(temp->children != NULL)
    {
        temp = temp->children[0];
        ++depth;
    }

    return depth;
}

void LS_ReleaseSystem(LS_Tree * ls)
{
    int i;

    /* No action is required if the tree is NULL */
    if(ls == NULL)
        return;

    /* Recursively free all the child nodes */
    if(ls->children != NULL)
    {
        for(i = 0; i < 4; ++i)
            LS_ReleaseSystem(ls->children[i]);
    }

    /* Free the tree node */
    free(ls);
}

static LS_Tree ** Expand(LS_Tree * parent, LS_NUM node)
{
    /* Initalize the 4 children */
    LS_Tree ** children = LS_BuildResource(sizeof(LS_Tree *) * 4);

    /* Assign all the symbols and heights using a default set of expansion rules */
    switch(node)
    {
        case LS_ZERO:
            children[0] = LS_BuildSystem(parent, LS_ONE, LS_TWO);
            children[1] = LS_BuildSystem(parent, LS_TWO, LS_ZERO);
            children[2] = LS_BuildSystem(parent, LS_ONE, LS_THREE);
            children[3] = LS_BuildSystem(parent, LS_ZERO, LS_ONE);
            return children;
        case LS_ONE:
            children[0] = LS_BuildSystem(parent, LS_TWO, LS_ONE);
            children[1] = LS_BuildSystem(parent, LS_THREE, LS_TWO);
            children[2] = LS_BuildSystem(parent, LS_TWO, LS_ZERO);
            children[3] = LS_BuildSystem(parent, LS_THREE, LS_TWO);
            return children;
        case LS_TWO:
            children[0] = LS_BuildSystem(parent, LS_THREE, LS_THREE);
            children[1] = LS_BuildSystem(parent, LS_ZERO, LS_ONE);
            children[2] = LS_BuildSystem(parent, LS_ONE, LS_THREE);
            children[3] = LS_BuildSystem(parent, LS_ZERO, LS_TWO);
            return children;
        default:
            children[0] = LS_BuildSystem(parent, LS_THREE, LS_ZERO);
            children[1] = LS_BuildSystem(parent, LS_TWO, LS_THREE);
            children[2] = LS_BuildSystem(parent, LS_ONE, LS_ZERO);
            children[3] = LS_BuildSystem(parent, LS_ZERO, LS_ONE);
            return children;
    }
}
