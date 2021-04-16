#pragma once
#include <vector>
#include <unordered_map>
#include <cmath>


/**TODO: add quantities to each node. Instead of searching each time you add a node, instead search for the node, if the node is found along the way, simply add 1
 * to its quantity.**/

using namespace std;
struct Node{

    bool leaf = true;
    int size;
    Node* parent;
    vector<Node*> children{nullptr, nullptr, nullptr, nullptr};
    vector<float> prices;
    Node* next;
    int numChildren = 0;
};
class B_Plus_Tree {

    const int maxChildren = 4;
    int maxKeys = maxChildren - 1;
    unordered_map<float, int> quantities;

public:
    Node* root;
    int unique;
    int dup = 0;

    void insert(float price);
    B_Plus_Tree(float price);
    vector<Node*> findInsertion(Node* node, Node* prev, float price);
    Node* insertNonFull(Node* node, Node* prev, float price);
    Node* insertFull(Node* node, Node* prev, float price);
    Node* findParent(Node* node, Node* target, float price);
    void recursiveInsert(Node* node, Node* prev, float price);
    void printLeaves(Node* node, Node* prev, float price);
    Node* findNode(Node* node, Node* prev, float price);
    Node* determineConnection(Node* node, Node* prev, float price);

};

B_Plus_Tree::B_Plus_Tree(float price) {
    Node* newRoot = new Node();
    unique = 0;
    newRoot->prices.push_back(price);
    newRoot->leaf = true;
    root = newRoot;
}

void B_Plus_Tree::insert(float price) {
    if(root == nullptr){
        Node* newRoot = new Node();
        newRoot->leaf = true;
        newRoot->prices.push_back(price);
        newRoot->numChildren++;
        root = newRoot;
        return;
    }
    /*if(quantities.find(price) != quantities.end()){
        dup++;
        return;
    }*/



    Node* currNode = root;
    Node* prev = new Node();

    vector<Node*> returned = findInsertion(currNode, prev, price);
    currNode = returned[0];
    prev = returned[1];
    if(currNode == nullptr){
        dup++;
        return;
    }
    unique++;


    if(currNode->prices.size() < maxKeys){
        insertNonFull(currNode, prev, price); // doone
    }
    else if(currNode->prices.size() == maxKeys){
        insertFull(currNode, prev, price);
    }
}

Node *B_Plus_Tree::findParent(Node* node, Node* target, float price) {
    Node* parent;
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
} //remember to cite this

//TODO: write code that connects nodes from 2 diffretent branches

Node *B_Plus_Tree::insertFull(Node *node, Node *prev, float price) {
    Node* newChild = new Node();
    int mid = (node->prices.size() + 1) / 2; //splits nodes
    vector<float> unsplitNode;

    unsplitNode = node->prices;
    unsplitNode.push_back(price);
    sort(unsplitNode.begin(), unsplitNode.end());

    node->prices.clear();
    copy(unsplitNode.begin(), unsplitNode.begin() + mid, back_inserter(node->prices));
    copy(unsplitNode.begin() + mid, unsplitNode.end(), back_inserter(newChild->prices));
    newChild->next = node;

    int pos = 0;
    //find where to place node inside node parent node
    while(pos < prev->prices.size() && price > prev->prices[pos])
        pos++;


    //where to write code to connect two nodes from 2 different branches:
    Node* find;
    if(pos == 3){
        for(int k = 0; k < 1000; k++){
            float add = k / 100;
            find = findNode(root, prev, newChild->prices.back() + add);
            if(find != nullptr){
                find->next = newChild;
                break;
            }
        }
    }



    if(node == root){
        Node* newRoot = new Node();
        newRoot->prices.push_back(unsplitNode[mid]);
        newRoot->numChildren = 2;
        newRoot->leaf = false;
        newRoot->children[0] = node;
        newRoot->children[1] = newChild;
        root = newRoot;
    }
    else{
        recursiveInsert(newChild, prev, newChild->prices[0]);
    }

    return node;

}

Node* B_Plus_Tree::determineConnection(Node *node, Node *prev, float price) {
    Node* grandFather = findParent(root, prev, price);
    if(grandFather != nullptr){
        int k = 0;
        for(; k < grandFather->numChildren; k++)
            if(grandFather->children[k] == prev)
                break;

        if(k == grandFather->numChildren - 1){
            determineConnection(nullptr, grandFather, price);
        }
        else{
            return grandFather;
        }
    }
    return nullptr;
}


void B_Plus_Tree::recursiveInsert(Node *node, Node *prev, float price) {
    if(prev->prices.size() < maxKeys){ //if parent is not full
        int pos = 0;
        //find where to place node inside node parent node
        while(pos < prev->prices.size() && price > prev->prices[pos])
            pos++;
        prev->prices.push_back(price);
        sort(prev->prices.begin(), prev->prices.end());
        prev->children.insert(prev->children.begin() + pos + 1, node);
        prev->children.pop_back();
        prev->numChildren++;
        prev->leaf = false;

        if(pos + 1 == 1 && prev->children[pos + 2] != nullptr){
            prev->children[pos + 2]->next = prev->children[pos + 1];
        }
        else if(pos + 1 == 2 && prev->children[pos + 2] != nullptr){
            prev->children[pos + 2]->next = prev->children[pos + 1];
        }
        else if((pos + 1 == 1 || pos + 1 == 2) && prev->children[pos + 2] == nullptr){
        }
    }
    else{

        Node* newNode = new Node();
        vector<float> unsplitNode;
        unsplitNode = prev->prices;
        unsplitNode.push_back(price);
        sort(unsplitNode.begin(), unsplitNode.end());
        int mid = (unsplitNode.size()) / 2; //splits nodes
        float val = unsplitNode[mid];

        int pos = 0;
        //find where to place node inside node parent node
        while(pos < prev->prices.size() && price > prev->prices[pos])
            pos++;


        vector<Node*> children;
        children = prev->children;
        children.insert(children.begin() + pos + 1, node); //inserts nodes in correct spot

        //determine where to point:

        prev->children = {nullptr, nullptr, nullptr, nullptr};
        for(int k = 0; k < 3; k++){
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

        if(price < unsplitNode[mid])
            newNode->prices.push_back(unsplitNode[unsplitNode.size() - 1]); //if child is to the left of mid

        else if(price == unsplitNode[mid])
            newNode->prices.push_back(unsplitNode[mid + 1]); //if child is mid
        else
            newNode->prices.push_back(price); //if child is to the right of mid

        newNode->numChildren = 2;
        newNode->children[0] = children[children.size() - 2];
        newNode->children[1] = children[children.size() - 1];
        newNode->leaf = false;

        newNode->children[1]->next = newNode->children[0];
     //   newNode->children[0]->next = node;

        if(pos + 1 == 1 && prev->children[pos + 2] != nullptr){
            prev->children[pos + 2]->next = prev->children[pos + 1];
        }
        else if(pos + 1 == 2 && prev->children[pos + 2] != nullptr){
            prev->children[pos + 2]->next = prev->children[pos + 1];
        }
        else if((pos + 1 == 1 || pos + 1 == 2) && prev->children[pos + 2] == nullptr){
            newNode->children[0]->next = node;
        }


        if(prev == root){
            Node* newRoot = new Node();
            newRoot->prices.push_back(unsplitNode[mid]);
            newRoot->numChildren = 2;
            newRoot->leaf = false;
            newRoot->children[0] = prev;
            newRoot->children[1] = newNode;
            root = newRoot;
        }
        else{
            recursiveInsert(newNode, findParent(root, prev, val), val);
        }
    }

}

Node *B_Plus_Tree::insertNonFull(Node *node, Node *prev, float price) {
    node->prices.push_back(price);
    quantities[price] = 1;
    sort(node->prices.begin(), node->prices.end());
    return node;
}

bool compare_float(float x, float y, float epsilon = 0.01f){ //remember to cite this
    if(fabs(x - y) < epsilon)
        return true; //they are same
    return false; //they are not same
}

vector<Node*>B_Plus_Tree::findInsertion(Node *node, Node *prev, float price) {
    Node* currNode = node;
    bool changed = false;

    int x;

    while(!currNode->leaf){ //finds place to insert node at
        for(x = 0; x < currNode->prices.size(); x++){
            if(price < currNode->prices[x]){
                if(x == 0 || x == 1 || x == 2){
                    prev = currNode;
                    currNode = currNode->children[x];
                    changed = true;
                    break;
                }
            }
        }
        if(!changed){
            prev = currNode;
            currNode = currNode->children[currNode->numChildren - 1];
        }
        changed = false;
    }

    int priceAsInt = (int)(100 * price + 0.5);

    for(int k = 0; k < currNode->prices.size(); k++){
        int currPrice = (int)(100 * currNode->prices[k] + 0.5);
        if(priceAsInt == currPrice){
            return{nullptr, nullptr};
        }
    }

    return {currNode, prev};
}

void B_Plus_Tree::printLeaves(Node *node, Node *prev, float price) {
    Node* currNode = node;

    int x;

    while(!currNode->leaf){ //finds place to insert node at
        for(x = 0; x < currNode->prices.size(); x++){
            if(price > currNode->prices[x]){
                currNode = currNode->children[x];
        }
    }
    Node* itr = currNode;
    }
}

Node *B_Plus_Tree::findNode(Node *node, Node *prev, float price) {
    Node* currNode = node;
    bool changed = false;

    int x;
    while(!currNode->leaf){ //finds place to insert node at
        for(x = 0; x < currNode->prices.size(); x++){
            if(currNode->prices[x] == price && currNode->leaf){
                return currNode;
            }
            if(price < currNode->prices[x]){
                if(x == 0 || x == 1 || x == 2){
                    currNode = currNode->children[x];
                    changed = true;
                    break;
                }
            }
        }
        if(!changed){
            currNode = currNode->children[currNode->numChildren - 1];
        }
        changed = false;
    }
    if(currNode->prices[currNode->prices.size() - 1] < price)
        return nullptr;

    int priceAsInt = (int)(100 * price + 0.5);

    for(int k = 0; k < currNode->prices.size(); k++){
        int currPrice = (int)(100 * currNode->prices[k] + 0.5);
        if(priceAsInt == currPrice){
            return currNode;
        }
    }
    return currNode;
}












