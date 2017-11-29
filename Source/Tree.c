#include "Tree.h"
#include "Memory.h"
#include <stdlib.h>
#include <time.h>

static lsTree ** Expand(lsTree *);

lsTree * _lsBuildSystem(lsTree * parent, unsigned char node, unsigned int seed, float height, float decay)
{
    lsTree * ls = NULL;
    lsNewMem(ls, sizeof(lsTree));

    /* Initalize the new tree node using the given parameters */
    ls->node = node;
    ls->seed = seed;
    ls->height = height;
    ls->decay = decay;
    ls->parent = parent;
    ls->children = NULL;

    return ls;

    FAIL:
        return NULL;
}

int _lsExpand(lsTree * ls, unsigned int depth, lsTree ** (* expand)(lsTree *))
{
    int success = 1;

    /* If the node is NULL or if it already has children then stop */
    if(depth == 0 || ls == NULL || ls->children != NULL)
        return 1;

    /* If no expand function is given then use a default one */
    if(expand == NULL)
        expand = Expand;

    /* Initalize all of the nodes children */
    if ((ls->children = expand(ls)) == NULL)
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

static lsTree ** Expand(lsTree * parent)
{
    /* Initalize the 4 children */
    lsTree ** children = NULL;
    lsNewMem(children, sizeof(lsTree *) * 4);

    /* Assign all the symbols and heights using a default set of expansion rules */
    switch(parent->node)
    {
        case 0:
            lsBuildSystem(children[0], parent, 4, parent->seed, parent->height + (-0.080073 * (parent->decay)), parent->decay * 0.500058);
            lsBuildSystem(children[1], parent, 4, parent->seed, parent->height + (-0.080073 * (parent->decay)), parent->decay * 0.500058);
            lsBuildSystem(children[2], parent, 5, parent->seed, parent->height + (-0.080073 * (parent->decay)), parent->decay * 0.500058);
            lsBuildSystem(children[3], parent, 2, parent->seed, parent->height + (-0.080073 * (parent->decay)), parent->decay * 0.500058);
            return children;
        case 1:
            lsBuildSystem(children[0], parent, 1, parent->seed, parent->height + (-0.004651 * (parent->decay)), parent->decay * 0.581664);
            lsBuildSystem(children[1], parent, 1, parent->seed, parent->height + (-0.004651 * (parent->decay)), parent->decay * 0.581664);
            lsBuildSystem(children[2], parent, 3, parent->seed, parent->height + (-0.004651 * (parent->decay)), parent->decay * 0.581664);
            lsBuildSystem(children[3], parent, 3, parent->seed, parent->height + (-0.004651 * (parent->decay)), parent->decay * 0.581664);
            return children;
        case 2:
            lsBuildSystem(children[0], parent, 2, parent->seed, parent->height + (0.440361 * (parent->decay)), parent->decay * 0.977725);
            lsBuildSystem(children[1], parent, 1, parent->seed, parent->height + (0.440361 * (parent->decay)), parent->decay * 0.977725);
            lsBuildSystem(children[2], parent, 1, parent->seed, parent->height + (0.440361 * (parent->decay)), parent->decay * 0.977725);
            lsBuildSystem(children[3], parent, 3, parent->seed, parent->height + (0.440361 * (parent->decay)), parent->decay * 0.977725);
            return children;
        case 3:
            lsBuildSystem(children[0], parent, 1, parent->seed, parent->height + (-0.128067 * (parent->decay)), parent->decay * 0.507773);
            lsBuildSystem(children[1], parent, 1, parent->seed, parent->height + (-0.128067 * (parent->decay)), parent->decay * 0.507773);
            lsBuildSystem(children[2], parent, 3, parent->seed, parent->height + (-0.128067 * (parent->decay)), parent->decay * 0.507773);
            lsBuildSystem(children[3], parent, 3, parent->seed, parent->height + (-0.128067 * (parent->decay)), parent->decay * 0.507773);
            return children;
        case 4:
            lsBuildSystem(children[0], parent, 0, parent->seed, parent->height + (0.214676 * (parent->decay)), parent->decay * 0.800868);
            lsBuildSystem(children[1], parent, 0, parent->seed, parent->height + (0.214676 * (parent->decay)), parent->decay * 0.800868);
            lsBuildSystem(children[2], parent, 4, parent->seed, parent->height + (0.214676 * (parent->decay)), parent->decay * 0.800868);
            lsBuildSystem(children[3], parent, 4, parent->seed, parent->height + (0.214676 * (parent->decay)), parent->decay * 0.800868);
            return children;
        default:
            lsBuildSystem(children[0], parent, 1, parent->seed, parent->height + (0.434368 * (parent->decay)), parent->decay * 0.974003);
            lsBuildSystem(children[1], parent, 5, parent->seed, parent->height + (0.434368 * (parent->decay)), parent->decay * 0.974003);
            lsBuildSystem(children[2], parent, 3, parent->seed, parent->height + (0.434368 * (parent->decay)), parent->decay * 0.974003);
            lsBuildSystem(children[3], parent, 1, parent->seed, parent->height + (0.434368 * (parent->decay)), parent->decay * 0.974003);
            return children;
    }

    FAIL:
        return NULL;
}
