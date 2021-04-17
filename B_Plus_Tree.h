#pragma once
#include <vector>
#include<algorithm>
#include <unordered_map>
#include <iostream>


using namespace std;

struct Node {

    bool leaf = true;
    vector<Node*> children{ nullptr, nullptr, nullptr, nullptr };
    vector<pair<float, int>> prices;
    Node* next;
    int numChildren = 0;
};
class B_Plus_Tree {

    const int maxChildren = 4;
    int maxKeys = maxChildren - 1;
    unordered_map<float, int> quantities;

    Node* root;

    void insert(float price);
    vector<Node*> findInsertion(Node* node, Node* prev, float price);
    Node* insertNonFull(Node* node, float price);
    Node* insertFull(Node* node, Node* prev, float price);
    Node* findParent(Node* node, Node* target, float price);
    void recursiveInsert(Node* node, Node* prev, float price);
    Node* findNode(Node* node,float price);
    Node* GetTail();
public:
    B_Plus_Tree();
    B_Plus_Tree(float price);
    void LoadDataSet(float pricePoint);
    int FindQuantityDemanded(float pricePoint);
    int PrintMarketStatus(float m, float c, float pricePoint);
    void FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity);

};

