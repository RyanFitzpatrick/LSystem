/* Tree.h: Defines various types, prototypes, and macros used for LSystem Trees */

#ifndef _LS_TREE_
#define _LS_TREE_

/* The structure used to represent an LSystem Tree */
typedef struct lsTree
{
    /* The symbol associated with a given node in the Tree */
    unsigned char node;
    /* The height specified by a given node in the Tree */
    unsigned char height;
    /* The nodes parent */
    struct lsTree * parent;
    /* The child nodes of a given Tree node, there must be exactly 4 child nodes */
    struct lsTree ** children;
} lsTree;

lsTree * _lsBuildSystem(lsTree *, unsigned char, unsigned char);
int _lsExpand(lsTree *, unsigned int, lsTree ** (*)(lsTree *, unsigned char));
void lsReleaseSystem(lsTree *);

#define lsBuildSystem(tree, parent, node, height) if ((tree = _lsBuildSystem(parent, node, height)) == NULL) goto FAIL
#define lsExpand(tree, depth, func) if (!_lsExpand(tree, depth, func)) goto FAIL

#endif
