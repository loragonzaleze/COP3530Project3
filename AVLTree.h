#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "TreeNode.h"

using namespace std;

//AVL Tree Implementation
//(Based a bit on the code from the GatorAVL Project)
class AVLTree
{
private:
	//private variables and functions which do not need to be accessed by the user
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
	//public functions that perform the required tasks
	void LoadDataSet(float pricePoint);
	int FindQuantityDemanded(float pricePoint);
	int PrintMarketStatus(float m, float c, float pricePoint);
	void FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity);
};

