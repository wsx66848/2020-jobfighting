#include <iostream>
#include "sort.h"
#include "travelse.h"

using namespace std;

void testSort();
void testTravelse();

int main() {
    testSort();
    //testTravelse();
}

void testSort() {
    int a[17] = {2,6,8,3,1,245,6,7,84,4,2,34,6756,7567,3424,23423,234234};
    selectSort(a, 17);
    for(int i = 0; i < 17; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

}

void testTravelse() {
    int i = 0;
    TreeNode* node = new TreeNode(i++);
    TreeNode* root = node;
    TreeNode* node1 = new TreeNode(i++);
    TreeNode* node2 = new TreeNode(i++);
    node->left = node1;
    node->right = node2;
    node = node1;
    node1 = new TreeNode(i++);
    node->left = node1;
    node1 = node2;
    node2 = new TreeNode(i++);
    node->right = node2;
    node = node1;
    node1 = new TreeNode(i++);
    node->left = node1;
    preOrderTravelse(root);
    midOrderTravelse(root);
    postOrderTravelse(root);
    levelTravelse(root);
}
