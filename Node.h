#pragma once
struct Node
{
	float price;
	int qty;
	Node* left;
	Node* right;
	Node(float p, int q, Node* l, Node* r);
};

