#pragma once
//TreeNode class representing the individual nodes inside the AVL tree
struct TreeNode
{
	float price;
	int qty;
	TreeNode* left;
	TreeNode* right;
	int height = 1;
	TreeNode();
	TreeNode(float p, int q, TreeNode* l, TreeNode* r);
};

