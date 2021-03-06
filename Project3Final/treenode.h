#ifndef TREENODE_H
#define TREENODE_H

#pragma once
struct TreeNode
{
    float price;
    int qty;
    TreeNode* left;
    TreeNode* right;
    int height = 1;
    TreeNode(float p, int q, TreeNode* l, TreeNode* r);
};


#endif // TREENODE_H
