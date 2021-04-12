#include "AVLTree.h"
int AVLTree::CalculateTreeHeight(Node* node)
{
    if (!node)
    {
        return 0;
    }
    int leftHeight = CalculateTreeHeight(node->left);
    int rightHeight = CalculateTreeHeight(node->right);

    if (leftHeight > rightHeight)
    {
        return(leftHeight + 1);
    }
    else
    {
        return(rightHeight + 1);
    }
}


int AVLTree::height(Node* n)
{
    if (n == nullptr)
    {
        return  0;
    }
    return n->height;
}


Node* AVLTree::RotateLeft(Node* node)
{
    Node* grandchild = node->right->left;
    Node* newParent = node->right;
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


Node* AVLTree::RotateRight(Node* node)
{
    Node* grandchild = node->left->right;
    Node* newParent = node->left;
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


Node* AVLTree::RotateLeftRight(Node* node)
{
    node->left = RotateLeft(node->left);
    node = RotateRight(node);
    return node;
}


Node* AVLTree::RotateRightLeft(Node* node)
{
    node->right = RotateRight(node->right);
    node = RotateLeft(node);
    return node;
}


Node* AVLTree::BalanceTheTree(Node* root, vector<Node*>& st)
{
    for (int i = st.size() - 1; i >= 0; i--)
    {

        Node* temp = st[i];
        Node* lchild = temp->left;
        Node* rchild = temp->right;
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
            Node* lchild = temp->left->left;
            Node* rchild = temp->left->right;
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
            Node* lchild = temp->right->left;
            Node* rchild = temp->right->right;
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
            Node* unbalancedNode = st[i];
            bool check = true;
            Node* temp = st[i - 1];
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


Node* AVLTree::Insert(Node* root, float pricePoint, vector<Node*>& st)
{
    Node* temp = root;
    if (temp)
    {
        st.push_back(temp);
    }
    if (!temp)
    {
        Node* keyNode = new Node(pricePoint, 1, nullptr, nullptr);
        st.push_back(keyNode);
        return keyNode;
    }

    if (pricePoint < temp->price && !temp->left)
    {
        Node* keyNode = new Node(pricePoint, 1, nullptr, nullptr);
        st.push_back(keyNode);
        temp->left = keyNode;
    }

    else if (pricePoint < temp->price && temp->left)
    {
        temp = Insert(temp->left, pricePoint, st);
    }

    else if (pricePoint > temp->price && !temp->right)
    {
        Node* keyNode = new Node(pricePoint, 1, nullptr, nullptr);
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


bool AVLTree::Search(Node* node, float pricePoint)
{
    Node* temp = node;
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


void AVLTree::TraverseInorder(Node* node, vector<Node*>& v)
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
        vector<Node*> st;
        root = Insert(root,  pricePoint, st);
        root = BalanceTheTree(root, st);
    }
}


int AVLTree::FindQuantityDemanded(float pricePoint)
{
    vector<Node*> v;
    TraverseInorder(root, v);
    int qtyDemanded = 0;
    for (int i = 0; i < v.size();i++)
    {
        Node* t = v[i];
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
    vector<Node*> v;
    TraverseInorder(root, v);
    equilibriumPrice = 0;
    int qd = 0;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        Node* t = v[i];
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