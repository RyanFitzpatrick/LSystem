/* Tree.h: Defines various types, prototypes, and macros used for LSystem Trees */

#ifndef _LS_TREE_
#define _LS_TREE_

/* The structure used to represent an LSystem Tree */
typedef struct lsTree
{
    /* The symbol associated with a given node in the Tree */
    unsigned char node;
    /* Seed used for stochastic branching */
    unsigned int seed;
    /* The height specified by a given node in the Tree */
    float height;
    /* The height delta applied to a given node */
    float decay;
    /* The nodes parent */
    struct lsTree * parent;
    /* The child nodes of a given Tree node, there must be exactly 4 child nodes */
    struct lsTree ** children;
} lsTree;

lsTree * _lsBuildSystem(lsTree *, unsigned char, unsigned int, float, float);
int _lsExpand(lsTree *, unsigned int, lsTree ** (*)(lsTree *));
void lsReleaseSystem(lsTree *);

#define lsBuildSystem(tree, parent, node, seed, height, decay) if ((tree = _lsBuildSystem(parent, node, seed, height, decay)) == NULL) goto FAIL
#define lsExpand(tree, depth, func) if (!_lsExpand(tree, depth, func)) goto FAIL

#endif
