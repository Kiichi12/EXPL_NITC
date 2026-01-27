#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Create a new leaf node
tnode* makeLeafNode(int n) {
    tnode *node = (tnode*)malloc(sizeof(tnode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->val = n;
    node->op = NULL;   // no operator for leaf
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Create a new operator node
tnode* makeOperatorNode(char *op, tnode *l, tnode *r) {
    tnode *node = (tnode*)malloc(sizeof(tnode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->val = 0;              // value is not meaningful for operator node
    node->op = strdup(op);      // to allocate its own copy of the operator string.
    node->left = l;
    node->right = r;
    return node;
}


void inorderTraversal(tnode *root) {
    if (!root) return;
    inorderTraversal(root->left);

    if (root->op)          // interior node
        printf(" %s ", root->op);
    else                   // leaf node
        printf(" %d ", root->val);

    inorderTraversal(root->right);
}


void preorderTraversal(tnode *root) {
    if (!root) return;

    if (root->op)
        printf(" %s ", root->op);
    else
        printf(" %d ", root->val);

    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder (left → right → root)
void postorderTraversal(tnode *root) {
    if (!root) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);

    if (root->op)
        printf(" %s ", root->op);
    else
        printf(" %d ", root->val);
}

// Free the tree
void deleteTree(tnode *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);

    if (root->op) free(root->op); // free copied operator string
    free(root);
}
