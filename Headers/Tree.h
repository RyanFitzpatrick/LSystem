#ifndef _LS_TREE_
#define _LS_TREE_

typedef struct lsTree
{
    unsigned char node;
    unsigned char height;
    struct lsTree * parent;
    struct lsTree ** children;
} lsTree;

lsTree * _lsBuildSystem(lsTree *, unsigned char, unsigned char);
int _lsExpand(lsTree *, unsigned int, lsTree ** (*)(lsTree *, unsigned char));
void lsReleaseSystem(lsTree *);

#define lsBuildSystem(tree, parent, node, height) if ((tree = _lsBuildSystem(parent, node, height)) == NULL) goto FAIL
#define lsExpand(tree, depth, func) if (!_lsExpand(tree, depth, func)) goto FAIL

#endif
