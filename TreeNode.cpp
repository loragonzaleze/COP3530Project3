#include "TreeNode.h"

//Default TreeNode Constructor
TreeNode::TreeNode()
{
	left = nullptr;
	right = nullptr;
}


//Constructor to create a new TreeNode
TreeNode::TreeNode(float p, int q, TreeNode* l, TreeNode* r)
{
	price = p;
	qty = q;
	left = l;
	right = r;
}