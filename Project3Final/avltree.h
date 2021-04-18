#ifndef AVLTREE_H
#define AVLTREE_H


#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "treenode.h"

using namespace std;

class AVLTree
{
private:
    TreeNode* root = nullptr;
    int height(TreeNode* n);
    TreeNode* RotateLeft(TreeNode* node);
    TreeNode* RotateRight(TreeNode* node);
    TreeNode* RotateLeftRight(TreeNode* node);
    TreeNode* RotateRightLeft(TreeNode* node);
    TreeNode* BalanceTheTree(TreeNode* root, vector<TreeNode*>& st);
    TreeNode* Insert(TreeNode* root, float pricePoint, vector<TreeNode*>& st);
    bool Search(TreeNode* node, float pricePoint);
    void TraverseInorder(TreeNode* node, vector<TreeNode*>& v);
public:
    void LoadDataSet(float pricePoint);
    int FindQuantityDemanded(float pricePoint);
    int PrintMarketStatus(float m, float c, float pricePoint);
    void FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity);
};



#endif // AVLTREE_H
