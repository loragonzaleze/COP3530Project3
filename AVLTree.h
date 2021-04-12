#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Node.h"

using namespace std;

class AVLTree
{
private:
	Node* root = nullptr;
	int CalculateTreeHeight(Node* node);
	int height(Node* n);
	Node* RotateLeft(Node* node);
	Node* RotateRight(Node* node);
	Node* RotateLeftRight(Node* node);
	Node* RotateRightLeft(Node* node);
	Node* BalanceTheTree(Node* root, vector<Node*>& st);
	Node* Insert(Node* root, float pricePoint, vector<Node*>& st);
	bool Search(Node* node, float pricePoint);
	void TraverseInorder(Node* node, vector<Node*>& v);
public:
	void LoadDataSet(float pricePoint);
	int FindQuantityDemanded(float pricePoint);
	int PrintMarketStatus(float m, float c, float pricePoint);
	void FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity);
};

