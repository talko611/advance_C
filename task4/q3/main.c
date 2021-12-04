#include "q3Funcs.h"

#define SIZE 100


void main() {
    int size, i;
    int arr[SIZE];
    Tree tr;
    TreeNode *p;
    int parentData, data, branchSelect;

//     printf("Please enter the number of items: ");
    scanf("%d", &size);
    for (i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d%d%d", &parentData, &data, &branchSelect);
    tr = BuildTreeFromArrayWithLeafList(arr, size);
    p = findParent(tr, parentData, branchSelect);
    tr = AddLeaf(tr, p, branchSelect, data);
    printTreeInorder(tr); //Print the tree in-order (LDR)
    printLeafList(tr); //Print the leaves from left to right
    freeTree(tr);


}