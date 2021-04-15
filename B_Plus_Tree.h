#pragma once
#include <vector>
#include <unordered_map>


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

    void insert(float price);
    B_Plus_Tree(float price);
    vector<Node*> findInsertion(Node* node, Node* prev, float price);
    Node* insertNonFull(Node* node, Node* prev, float price);
    Node* insertFull(Node* node, Node* prev, float price);
    Node* findParent(Node* node, Node* target, float price);
    void recursiveInsert(Node* node, Node* prev, float price);
    void printLeaves(Node* node, Node* prev, float price);
    Node* findNode(Node* node, Node* prev, float price);

};


B_Plus_Tree::B_Plus_Tree(float price) {
    Node* newRoot = new Node();

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
    if(quantities.find(price) != quantities.end()){
        quantities[price]++;
        return;
    }
    Node* currNode = root;
    Node* prev = new Node();

    vector<Node*> returned = findInsertion(currNode, prev, price);
    currNode = returned[0];
    prev = returned[1];

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

void B_Plus_Tree::recursiveInsert(Node *node, Node *prev, float price) {
    if(prev->prices.size() < maxKeys){ //if parent is not full
        int pos = 0;
        //find where to place node inside node parent node
        while(price > prev->prices[pos] && pos < prev->prices.size())
            pos++;
        prev->prices.push_back(price);
        sort(prev->prices.begin(), prev->prices.end());
        prev->children.insert(prev->children.begin() + pos + 1, node);
        prev->children.pop_back();
        prev->numChildren++;
        prev->leaf = false;
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
        while(price > prev->prices[pos] && pos < prev->prices.size())
            pos++;

        vector<Node*> children;
        children = prev->children;
        children.insert(children.begin() + pos + 1, node); //inserts nodes in correct spot

        prev->children = {nullptr, nullptr, nullptr, nullptr};
        for(int k = 0; k < 3; k++){
            prev->children[k] = children[k];
        }
        prev->numChildren = 3;
        prev->prices.clear();

        prev->prices.push_back(unsplitNode[0]);
        prev->prices.push_back(unsplitNode[1]);
        prev->leaf = false;

        newNode->prices.push_back(price);
        newNode->numChildren = 2;
        newNode->children[0] = children[children.size() - 2];
        newNode->children[1] = children[children.size() - 1];
        newNode->leaf = false;

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

vector<Node*>B_Plus_Tree::findInsertion(Node *node, Node *prev, float price) { //remember to cite this
    Node* currNode = node;
    bool changed = false;

    int x;

    while(!currNode->leaf){ //finds place to insert node at
        for(x = 0; x < currNode->prices.size(); x++){
            if(currNode->prices[x] == price && currNode->leaf){
                return {currNode, prev};
            }
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



    cout << endl;
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
    if(currNode->prices[currNode->prices.size() - 1] < price)
        return nullptr;
    return currNode;
}






#include <iostream>
#include "B_Plus_Tree.h"


int main() {

    B_Plus_Tree tree(1);

    for(int x = 2; x < 1001; x++)
        tree.insert(x);

    float targetPrice = 1400;
    Node* target = tree.findNode(tree.root, nullptr, targetPrice);
    if(target == nullptr)
        cout << "not found" << endl;

    Node* itr = target;
    while(itr != nullptr){
        for(int x = itr->prices.size() - 1; x > -1; x--)
            if(itr->prices[x] <= targetPrice)
                cout << itr->prices[x] << " ";
        itr = itr->next;
    }
    cout << endl;





    vector<float>& vals = tree.root->prices;
    for(float x: vals){
        cout << "ROOT: " << x << " " << tree.root->numChildren << endl;
    }
    vector<Node*> leaves = tree.root->children;

    for(int x = 0; x < tree.root->numChildren; x++){
        vector<float>& leaf = leaves[x]->prices;
        for(float x: leaf){
            cout << "2nd Level node " << x <<  endl;
        }
        cout << "new 2nd level node" << endl;
        vector<Node*>& children = leaves.at(x)->children;
        for(int y = 0; y < leaves.at(x)->numChildren; y++){
            vector<float>& insideLeaf = children.at(y)->prices;
            for(float j: insideLeaf)
                cout << "  " << j << endl;
            cout << " New Leaf " << endl;
          }

    }



    return 0;
}





