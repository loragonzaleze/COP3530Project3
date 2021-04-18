#include "B_Plus_Tree.h"



B_Plus_Tree::B_Plus_Tree() {

}


B_Plus_Tree::B_Plus_Tree(float price) {
    Node* newRoot = new Node();
    newRoot->prices.push_back({ price, 1});
    newRoot->leaf = true;
    root = newRoot;
}

//Determine what type of insertion needs to be done, if needed
//Verifies that a price is not already in the tree, and if it, will simply add 1 to the price.
//Will determine what type of insertion needs to be done depending on the size of the node.
void B_Plus_Tree::insert(float price) {
    if (root == nullptr) {
        Node* newRoot = new Node();
        newRoot->leaf = true;
        newRoot->prices.push_back({ price, 1 });
        root = newRoot;
        return;
    }

    Node* currNode = root;
    Node* prev = new Node();

    vector<Node*> returned = findInsertion(currNode, prev, price);
    currNode = returned[0];
    prev = returned[1];

    if (currNode == nullptr) { //If a nullptr is returned, that means price is already in tree, so no insertion is done
        return;
    }
    if (currNode->prices.size() < maxKeys) {
        insertNonFull(currNode, price);
    }
    else if (currNode->prices.size() == maxKeys) {
        insertFull(currNode, prev, price);
    }
}

//Function to find any inputted node's parent
//Used whenever doing a recursive insertion that requires balancing the tree as the program
//makes its way up the recursive stack
//Taken from geekforgeeks.com
//Citation: https://www.geeksforgeeks.org/insertion-in-a-b-tree/
Node* B_Plus_Tree::findParent(Node* node, Node* target, float price) {
    Node* parent = nullptr;
    if (node == nullptr || node->leaf) {
        return nullptr;
    }
    for (int x = 0; x < node->numChildren; x++) {
        if (node->children[x] == target) {
            parent = node;
            return parent;
        }
        else {
            parent = findParent(node->children[x], target, price);
            if (parent != nullptr)
                return parent;
        }
    }
    return parent;
}

//If the node to be inserted is at is full, this function will be called.
//It will create a new node, and edit the current node to only have half of the values. it will also assign
//new next pointers to the new child node
//If the current node is the root node, it will create a new root node, and assign as children the current node and the
//new child.
//Otherwise it will perform a recursive insert.
Node* B_Plus_Tree::insertFull(Node* node, Node* prev, float price) {
    Node* newChild = new Node();
    int mid = (node->prices.size() + 1) / 2; //splits nodes
    vector<pair<float, int>> unsplitNode;

    unsplitNode = node->prices;
    unsplitNode.push_back({ price, 1 });
    sort(unsplitNode.begin(), unsplitNode.end());

    node->prices.clear();
    copy(unsplitNode.begin(), unsplitNode.begin() + mid, back_inserter(node->prices));
    copy(unsplitNode.begin() + mid, unsplitNode.end(), back_inserter(newChild->prices));
    newChild->next = node;

    if (node == root) {
        Node* newRoot = new Node();
        newRoot->prices.push_back(unsplitNode[mid]);
        newRoot->numChildren = 2;
        newRoot->leaf = false;
        newRoot->children[0] = node;
        newRoot->children[1] = newChild;
        root = newRoot;
    }
    else {
        recursiveInsert(newChild, prev, newChild->prices[0].first);
    }

    return node;

}

//This function will recursively insert nodes, and split them as needed.
void B_Plus_Tree::recursiveInsert(Node* node, Node* prev, float price) {
    if (prev->prices.size() < maxKeys) { //if parent is not full
        int pos = 0;
        //find where to place node inside node parent node
        while (pos < prev->prices.size() && price > prev->prices[pos].first)
            pos++;
        prev->prices.push_back({ price, 1 });
        sort(prev->prices.begin(), prev->prices.end());
        prev->children.insert(prev->children.begin() + pos + 1, node);
        prev->children.pop_back();
        prev->numChildren++;
        prev->leaf = false;

        if (pos + 1 == 1 && prev->children[pos + 2] != nullptr) {
            prev->children[pos + 2]->next = prev->children[pos + 1];
        }
        else if (pos + 1 == 2 && prev->children[pos + 2] != nullptr) {
            prev->children[pos + 2]->next = prev->children[pos + 1];
        }
    }
    else {

        Node* newNode = new Node();
        vector<pair<float, int>> unsplitNode;
        unsplitNode = prev->prices;
        unsplitNode.push_back({ price, 1 });
        sort(unsplitNode.begin(), unsplitNode.end());
        int mid = (unsplitNode.size()) / 2; //splits nodes
        float val = unsplitNode[mid].first;

        int pos = 0;
        //find where to place node inside node parent node
        while (pos < prev->prices.size() && price > prev->prices[pos].first)
            pos++;


        vector<Node*> children;
        children = prev->children;
        children.insert(children.begin() + pos + 1, node); //inserts nodes in correct spot

        //pushes new assigned children into node
        prev->children = { nullptr, nullptr, nullptr, nullptr };
        for (int k = 0; k < 3; k++) {
            prev->children[k] = children[k];
        }
        prev->numChildren = 3;
        prev->prices.clear();

        //Assign next pointers to children;
        prev->children[1]->next = prev->children[0];
        prev->children[2]->next = prev->children[1];

        prev->prices.push_back(unsplitNode[0]);
        prev->prices.push_back(unsplitNode[1]);
        prev->leaf = false;

        if (price < unsplitNode[mid].first)
            newNode->prices.push_back(unsplitNode[unsplitNode.size() - 1]); //if child is to the left of mid

        else if (price == unsplitNode[mid].first)
            newNode->prices.push_back(unsplitNode[mid + 1]); //if child is mid
        else
            newNode->prices.push_back({ price, 1 }); //if child is to the right of mid

        newNode->numChildren = 2;
        newNode->children[0] = children[children.size() - 2];
        newNode->children[1] = children[children.size() - 1];
        newNode->leaf = false;

        newNode->children[1]->next = newNode->children[0];

        if (pos + 1 == 1 && prev->children[pos + 2] != nullptr) {
            prev->children[pos + 2]->next = prev->children[pos + 1];
        }
        else if (pos + 1 == 2 && prev->children[pos + 2] != nullptr) {
            prev->children[pos + 2]->next = prev->children[pos + 1];
        }
        else if ((pos + 1 == 1 || pos + 1 == 2) && prev->children[pos + 2] == nullptr) {
            newNode->children[0]->next = node;
        }

        if (prev == root) {
            Node* newRoot = new Node();
            newRoot->prices.push_back(unsplitNode[mid]);
            newRoot->numChildren = 2;
            newRoot->leaf = false;
            newRoot->children[0] = prev;
            newRoot->children[1] = newNode;
            root = newRoot;
        }
        else {
            recursiveInsert(newNode, findParent(root, prev, val), val); //will continue calling itself until it reaches
        }                                                                    // an non-full node or root node
    }

}

//Called whenever the current node is not full
Node* B_Plus_Tree::insertNonFull(Node* node, float price) {
    node->prices.push_back({ price, 1 });
    sort(node->prices.begin(), node->prices.end());
    return node;
}

//This function will find the correct place to insert a given price.
//Once found it will return the node at which to insert it at.
//The node returned will always be a root node.
vector<Node*>B_Plus_Tree::findInsertion(Node* node, Node* prev, float price) {
    Node* currNode = node;
    bool changed = false;

    int x;

    while (!currNode->leaf) { //finds place to insert node at
        for (x = 0; x < currNode->prices.size(); x++) {
            if (price < currNode->prices[x].first) {
                if (x == 0 || x == 1 || x == 2) {
                    prev = currNode;
                    currNode = currNode->children[x];
                    changed = true;
                    break;
                }
            }
        }
        if (!changed) {
            prev = currNode;
            currNode = currNode->children[currNode->numChildren - 1];
        }
        changed = false;
    }

    int priceAsInt = (int)(100 * price + 0.5);

    for (int k = 0; k < currNode->prices.size(); k++) {
        int currPrice = (int)(100 * currNode->prices[k].first + 0.5);
        if (priceAsInt == currPrice) {
            currNode->prices[k].second++;
            return{ nullptr, nullptr };
        }
    }

    return { currNode, prev };
}

//Will find the leaf node that contains the given price
Node* B_Plus_Tree::findNode(Node* node, float price) {
    Node* currNode = node;
    bool changed = false;

    int x;
    while (!currNode->leaf) {
        for (x = 0; x < currNode->prices.size(); x++) {
            if (price < currNode->prices[x].first) {
                if (x == 0 || x == 1 || x == 2) {
                    currNode = currNode->children[x];
                    changed = true;
                    break;
                }
            }
        }
        if (!changed) {
            currNode = currNode->children[currNode->numChildren - 1];
        }
        changed = false;
    }
    if (currNode->prices[currNode->prices.size() - 1].first < price)
        return nullptr;

    int priceAsInt = (int)(100 * price + 0.5);

    for (int k = 0; k < currNode->prices.size(); k++) {
        int currPrice = (int)(100 * currNode->prices[k].first + 0.5);
        if (priceAsInt == currPrice) {
            return currNode;
        }
    }
    return currNode;
}

//Function that will get the end of the list by going to the last leaf node
Node* B_Plus_Tree::GetTail()
{
    Node* node = root;
    while (!node->leaf)
    {
        int a = node->prices.size();
        node = node->children[a];
    }
    return node;
}

//Function called by the UI
void B_Plus_Tree::LoadDataSet(float pricePoint)
{
    insert(pricePoint);
}

//Sums up the quantities in all nodes that are greater than a given price point.
//Returns the total quantities.
int B_Plus_Tree::FindQuantityDemanded(float pricePoint)
{
    int priceAsInt = (int)(100 * pricePoint + 0.5);

    int p = 0;
    int quantity = 0;
    Node* itr = GetTail();
    while (itr != nullptr) {
        for (int x = itr->prices.size() - 1; x > -1; x--)
        {
            int currPrice = (int)(100 * itr->prices[x].first + 0.5);
            if (currPrice >= priceAsInt)
            {
                p++;
                quantity = quantity + itr->prices[x].second;
            }
        }

        itr = itr->next;
    }
    return quantity;
}

//Determine the amount of shortage or surplus there would be depending on the inputted m, c, and price.
int B_Plus_Tree::PrintMarketStatus(float m, float c, float pricePoint)
{
    int qtyDemanded = FindQuantityDemanded(pricePoint);
    int qtySupplied = floor((pricePoint - c) / m);
    int status = qtySupplied - qtyDemanded;
    return status;
}

//Function that returns the Equilibrium price point.
void B_Plus_Tree::FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity)
{
    int qd = 0;
    bool check = false;
    Node* itr = GetTail();
    while (itr != nullptr) {
        for (int x = itr->prices.size() - 1; x > -1; x--)
        {
            qd = qd + itr->prices[x].second;
            int qs = floor((itr->prices[x].first - c) / m);
            if (qd >= qs)
            {
                equilibriumPrice = itr->prices[x].first;
                check = true;
                break;
            }
            if (check)
            {
                break;
            }
        }
        if (check)
        {
            break;
        }
        itr = itr->next;
    }
    equilibriumQuantity = floor((equilibriumPrice - c) / m);
}
