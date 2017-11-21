#include "Tree.h"
#include "Memory.h"
#include <stdlib.h>

static lsTree ** Expand(lsTree *, unsigned char);

lsTree * _lsBuildSystem(lsTree * parent, unsigned char node, unsigned char height)
{
    lsTree * ls = NULL;
    lsNewMem(ls, sizeof(lsTree));

    /* Initalize the new tree node using the given parameters */
    ls->node = node;
    ls->height = height;
    ls->parent = parent;
    ls->children = NULL;

    return ls;

    FAIL:
        return NULL;
}

int _lsExpand(lsTree * ls, unsigned int depth, lsTree ** (* expand)(lsTree *, unsigned char))
{
    int success = 1;

    /* If the node is NULL or if it already has children then stop */
    if(depth == 0 || ls == NULL || ls->children != NULL)
        return 1;

    /* If no expand function is given then use a default one */
    if(expand == NULL)
        expand = Expand;

    /* Initalize all of the nodes children */
    if ((ls->children = expand(ls, ls->node)) == NULL)
        return 0;

    success &= _lsExpand(ls->children[0], --depth, expand);
    success &= _lsExpand(ls->children[1], depth, expand);
    success &= _lsExpand(ls->children[2], depth, expand);
    success &= _lsExpand(ls->children[3], depth, expand);

    return success;
}

void lsReleaseSystem(lsTree * ls)
{
    /* No action is required if the tree is NULL */
    if(ls == NULL)
        return;

    /* Recursively free all the child nodes */
    if(ls->children != NULL)
    {
        lsReleaseSystem(ls->children[0]);
        lsReleaseSystem(ls->children[1]);
        lsReleaseSystem(ls->children[2]);
        lsReleaseSystem(ls->children[3]);
        lsDiscardMem(ls->children);
    }

    /* Free the tree node */
    lsDiscardMem(ls);
}

static lsTree ** Expand(lsTree * parent, unsigned char node)
{
    /* Initalize the 4 children */
    lsTree ** children = NULL;
    lsNewMem(children, sizeof(lsTree *) * 4);

    /* Assign all the symbols and heights using a default set of expansion rules */
    switch(node)
    {
        case 0:
            lsBuildSystem(children[0], parent, 1, 2);
            lsBuildSystem(children[1], parent, 2, 0);
            lsBuildSystem(children[2], parent, 1, 3);
            lsBuildSystem(children[3], parent, 0, 1);
            return children;
        case 1:
            lsBuildSystem(children[0], parent, 2, 1);
            lsBuildSystem(children[1], parent, 3, 2);
            lsBuildSystem(children[2], parent, 2, 0);
            lsBuildSystem(children[3], parent, 3, 2);
            return children;
        case 2:
            lsBuildSystem(children[0], parent, 3, 3);
            lsBuildSystem(children[1], parent, 0, 1);
            lsBuildSystem(children[2], parent, 1, 3);
            lsBuildSystem(children[3], parent, 0, 2);
            return children;
        default:
            lsBuildSystem(children[0], parent, 3, 0);
            lsBuildSystem(children[1], parent, 2, 3);
            lsBuildSystem(children[2], parent, 1, 0);
            lsBuildSystem(children[3], parent, 0, 1);
            return children;
    }

    FAIL:
        return NULL;
}
