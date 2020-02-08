#ifndef MY_TRAVELSE_H
#define MY_TRAVELSE_H

#include <stdio.h>
#include <stack>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value): val(value), left(NULL), right(NULL) {};
};

void recursivePreOrderTravelse(TreeNode* root);
void preOrderTravelse(TreeNode* root);
void recursiveMidOrderTravelse(TreeNode* root);
void midOrderTravelse(TreeNode* root);
void recursivePostOrderTravelse(TreeNode* root);
void postOrderTravelse(TreeNode* root);
void levelTravelse(TreeNode* root);


#endif