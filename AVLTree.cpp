#include "AVLTree.h"


int AVLTree::height(TreeNode* n)
{
    if (n == nullptr)
    {
        return  0;
    }
    return n->height;
}


TreeNode* AVLTree::RotateLeft(TreeNode* node)
{
    TreeNode* grandchild = node->right->left;
    TreeNode* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    int l, r, m;

    l = height(newParent->left);
    r = height(newParent->right);
    m = l;
    if (r > m)
    {
        m = r;
    }
    newParent->height = m + 1;

    l = height(newParent->left->left);
    r = height(newParent->left->right);
    m = l;
    if (r > m)
    {
        m = r;
    }
    newParent->left->height = m + 1;

    return newParent;
}


TreeNode* AVLTree::RotateRight(TreeNode* node)
{
    TreeNode* grandchild = node->left->right;
    TreeNode* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    int l, r, m;

    l = height(newParent->left);
    r = height(newParent->right);
    m = l;
    if (r > m)
    {
        m = r;
    }
    newParent->height = m + 1;

    l = height(newParent->right->left);
    r = height(newParent->right->right);
    m = l;
    if (r > m)
    {
        m = r;
    }
    newParent->right->height = m + 1;

    return newParent;
}


TreeNode* AVLTree::RotateLeftRight(TreeNode* node)
{
    node->left = RotateLeft(node->left);
    node = RotateRight(node);
    return node;
}


TreeNode* AVLTree::RotateRightLeft(TreeNode* node)
{
    node->right = RotateRight(node->right);
    node = RotateLeft(node);
    return node;
}


TreeNode* AVLTree::BalanceTheTree(TreeNode* root, vector<TreeNode*>& st)
{
    for (int i = st.size() - 1; i >= 0; i--)
    {

        TreeNode* temp = st[i];
        TreeNode* lchild = temp->left;
        TreeNode* rchild = temp->right;
        int l = 0, r = 0;
        if (lchild)
        {
            l = lchild->height;
        }
        if (rchild)
        {
            r = rchild->height;
        }
        int parentBalanceFactor = l - r;
        int leftChildBalanceFactor = 0;
        int rightChildBalanceFactor = 0;
        if (temp->left)
        {
            TreeNode* lchild = temp->left->left;
            TreeNode* rchild = temp->left->right;
            l = 0;
            r = 0;
            if (lchild)
            {
                l = lchild->height;
            }
            if (rchild)
            {
                r = rchild->height;
            }
            leftChildBalanceFactor = l - r;
        }
        if (temp->right)
        {
            TreeNode* lchild = temp->right->left;
            TreeNode* rchild = temp->right->right;
            l = 0;
            r = 0;
            if (lchild)
            {
                l = lchild->height;
            }
            if (rchild)
            {
                r = rchild->height;
            }
            rightChildBalanceFactor = l - r;
        }
        if (parentBalanceFactor > -2 && parentBalanceFactor < 2)
        {

        }
        else if (temp == root)
        {
            if (parentBalanceFactor == 2 && leftChildBalanceFactor == 1)
            {
                root = RotateRight(root);
            }
            else if (parentBalanceFactor == 2 && leftChildBalanceFactor == -1)
            {
                root = RotateLeftRight(root);
            }
            else if (parentBalanceFactor == -2 && rightChildBalanceFactor == -1)
            {
                root = RotateLeft(root);
            }
            else if (parentBalanceFactor == -2 && rightChildBalanceFactor == 1)
            {
                root = RotateRightLeft(root);
            }
        }
        else
        {
            TreeNode* unbalancedNode = st[i];
            bool check = true;
            TreeNode* temp = st[i - 1];
            if (temp->left->price == unbalancedNode->price)
            {
                if (parentBalanceFactor == 2 && leftChildBalanceFactor == 1)
                {
                    temp->left = RotateRight(temp->left);
                }
                else if (parentBalanceFactor == 2 && leftChildBalanceFactor == -1)
                {
                    temp->left = RotateLeftRight(temp->left);
                }
                else if (parentBalanceFactor == -2 && rightChildBalanceFactor == -1)
                {
                    temp->left = RotateLeft(temp->left);
                }
                else if (parentBalanceFactor == -2 && rightChildBalanceFactor == 1)
                {
                    temp->left = RotateRightLeft(temp->left);
                }
            }
            else
            {
                if (parentBalanceFactor == 2 && leftChildBalanceFactor == 1)
                {
                    temp->right = RotateRight(temp->right);
                }
                else if (parentBalanceFactor == 2 && leftChildBalanceFactor == -1)
                {
                    temp->right = RotateLeftRight(temp->right);
                }
                else if (parentBalanceFactor == -2 && rightChildBalanceFactor == -1)
                {
                    temp->right = RotateLeft(temp->right);
                }
                else if (parentBalanceFactor == -2 && rightChildBalanceFactor == 1)
                {
                    temp->right = RotateRightLeft(temp->right);
                }
            }
        }
    }
    return root;
}


TreeNode* AVLTree::Insert(TreeNode* root, float pricePoint, vector<TreeNode*>& st)
{
    TreeNode* temp = root;
    if (temp)
    {
        st.push_back(temp);
    }
    if (!temp)
    {
        TreeNode* keyNode = new TreeNode(pricePoint, 1, nullptr, nullptr);
        st.push_back(keyNode);
        return keyNode;
    }

    if (pricePoint < temp->price && !temp->left)
    {
        TreeNode* keyNode = new TreeNode(pricePoint, 1, nullptr, nullptr);
        st.push_back(keyNode);
        temp->left = keyNode;
    }

    else if (pricePoint < temp->price && temp->left)
    {
        temp = Insert(temp->left, pricePoint, st);
    }

    else if (pricePoint > temp->price && !temp->right)
    {
        TreeNode* keyNode = new TreeNode(pricePoint, 1, nullptr, nullptr);
        st.push_back(keyNode);
        temp->right = keyNode;
    }

    else if (pricePoint > temp->price && temp->right)
    {
        temp = Insert(temp->right, pricePoint, st);
    }

    int l, r, m;

    l = height(temp->left);
    r = height(temp->right);
    m = l;
    if (r > m)
    {
        m = r;
    }
    temp->height = m + 1;

    return root;
}


bool AVLTree::Search(TreeNode* node, float pricePoint)
{
    TreeNode* temp = node;
    while (temp)
    {
        if (pricePoint < temp->price)
        {
            temp = temp->left;
        }
        else if (pricePoint > temp->price)
        {
            temp = temp->right;
        }
        else
        {
            temp->qty++;
            return true;
        }
    }
    return false;
}


void AVLTree::TraverseInorder(TreeNode* node, vector<TreeNode*>& v)
{
    if (node)
    {
        TraverseInorder(node->left, v);
        v.push_back(node);
        TraverseInorder(node->right, v);
    }
}




void AVLTree::LoadDataSet(float pricePoint)
{
    bool check = Search(root, pricePoint);
    if (!check)
    {
        vector<TreeNode*> st;
        root = Insert(root,  pricePoint, st);
        root = BalanceTheTree(root, st);
    }
}


int AVLTree::FindQuantityDemanded(float pricePoint)
{
    vector<TreeNode*> v;
    TraverseInorder(root, v);
    int qtyDemanded = 0;
    for (int i = 0; i < v.size();i++)
    {
        TreeNode* t = v[i];
        if (t->price >= pricePoint)
        {
            qtyDemanded = qtyDemanded + t->qty;
        }
    }

    return qtyDemanded;
}


int AVLTree::PrintMarketStatus(float m, float c, float pricePoint)
{
    int qtyDemanded = FindQuantityDemanded(pricePoint);
    int qtySupplied = floor((pricePoint - c)/m);
    int status = qtySupplied - qtyDemanded;
    return status;
}


void AVLTree::FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity)
{
    vector<TreeNode*> v;
    TraverseInorder(root, v);
    equilibriumPrice = 0;
    int qd = 0;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        TreeNode* t = v[i];
        qd = qd + t->qty;
        int qs = floor((t->price - c) / m);
        if (qd >= qs)
        {
            equilibriumPrice = t->price;
            break;
        }
        
    }
    equilibriumQuantity = floor((equilibriumPrice - c) / m);
}