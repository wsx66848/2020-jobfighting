#include "travelse.h"

using namespace std;

void recursivePreOrderTravelse(TreeNode* root) {
      if(root != NULL) {
          printf("%d ", root->val);
          preOrderTravelse(root->left);
          preOrderTravelse(root->right);
      }
      printf("\n");
}

void preOrderTravelse(TreeNode* root) {
      stack<TreeNode*> treenodeStack;
      TreeNode* node = root;
      while(node != NULL || ! treenodeStack.empty()) {
          while(node != NULL) {
              printf("%d ", node->val);
              treenodeStack.push(node);
              node = node->left;
          }

          if(!treenodeStack.empty()) {
              node = treenodeStack.top();
              treenodeStack.pop();
              node = node->right;
          }
      }
      printf("\n");
}

void recursiveMidOrderTravelse(TreeNode* root) {
      if(root != NULL) {
          preOrderTravelse(root->left);
          printf("%d ", root->val);
          preOrderTravelse(root->right);
      }
      printf("\n");
}

void midOrderTravelse(TreeNode* root) {
      stack<TreeNode*> treenodeStack;
      TreeNode* node = root;
      while(node != NULL || ! treenodeStack.empty()) {
          while(node != NULL) {
              treenodeStack.push(node);
              node = node->left;
          }

          if(!treenodeStack.empty()) {
              node = treenodeStack.top();
              treenodeStack.pop();
              printf("%d ", node->val);
              node = node->right;
          }
      }
      printf("\n");
}

void recursivePostOrderTravelse(TreeNode* root) {
    if(root != NULL) {
        postOrderTravelse(root->left);
        postOrderTravelse(root->right);
        printf("%d ", root->val);
    }
    printf("\n");
}

void postOrderTravelse(TreeNode* root) {
    stack<TreeNode*> treenodeStack;
    TreeNode* node = root;
    TreeNode* lastVisit = NULL;
    while(node != NULL || ! treenodeStack.empty()) {
        while(node != NULL) {
            treenodeStack.push(node);
            node = node->left;
        }

        if(!treenodeStack.empty()) {
            node = treenodeStack.top();
            if(node->right == NULL || node->right == lastVisit) {
                treenodeStack.pop();
                printf("%d ", node->val);
                lastVisit = node;
                node = NULL;
            } else {
                node = node->right;
            }
        }
    }
    printf("\n");
}

void levelTravelse(TreeNode* root) {
    queue<TreeNode*> treenodeQueue;
    treenodeQueue.push(root);
    while(! treenodeQueue.empty()) {
        TreeNode* node = treenodeQueue.front();
        treenodeQueue.pop();
        printf("%d ", node->val);
        if(node->left) treenodeQueue.push(node->left);
        if(node->right) treenodeQueue.push(node->right);
    }
    printf("\n");

}
