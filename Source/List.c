#include "List.h"
#include "Memory.h"
#include <stdlib.h>

LS_List * LS_Append(LS_List * node, LS_NUM num)
{
    LS_List * head = LS_BuildResource(sizeof(LS_List));

    /* Initalize a new node using the given number and have it point to the current head of the list */
    head->num = num;
    head->next = node;

    return head;
}

LS_List * BuildList(LS_List * list, LS_Tree * ls, unsigned int height)
{
    int i;

    if(ls->children != NULL)
    {
        /* Recursively add all the child heights from the tree to the list while keeping track of the current height */
        for(i = 3; i != 0; --i)
            list = BuildList(list, ls->children[i], height + ls->height);
    }

    /* Add the current height at the leaf node to the list */
    return LS_Append(list, height + ls->height);
}

void LS_ReleaseList(LS_List * head)
{
    if(head == NULL)
        return;

    /* Recursively free all nodes in the list */
    if(head->next != NULL)
        LS_ReleaseList(head->next);

    free(head);
}
