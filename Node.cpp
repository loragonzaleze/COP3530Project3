#include "Node.h"
Node::Node(float p, int q, Node* l, Node* r)
{
	price = p;
	qty = q;
	left = l;
	right = r;
}