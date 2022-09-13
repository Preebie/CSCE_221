#include <iostream>
#include <chrono>
using namespace std;
template <typename T>

class AVLTree
{
public:
	//create a new struct
	struct AvlNode
	{
		//we need a height for the rotations
		T element;
		AvlNode* left;
		AvlNode* right;
		int height;
		//recreate the nodes
		AvlNode(const T& ele, AvlNode* lt, AvlNode* rt, int h = 0)
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode(T&& ele, AvlNode* lt, AvlNode* rt, int h = 0)
			: element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h } { }
	};
	//set an allowance for the imbalance in the tree
	static const int ALLOWED_IMBALANCE = 1;
	AvlNode* root;
	int _size;

	//constructor
	AVLTree() {
		root = nullptr;
		_size = 0;
	}
	//height with a condensed if loop
	int height(AvlNode* Node) const
	{
		return Node == nullptr ? -1 : Node->height;
	}
	//size function
	int size() {
		return _size;
	}
	//insert function
	void insert(const T & x, AvlNode * &Node)
	{
		if (Node == nullptr) {
			Node = new AvlNode{ x, nullptr, nullptr };
			_size++;
		}
		else if (x < Node->element)
			insert(x, Node->left);
		else if (Node->element < x)
			insert(x, Node->right);
		//this is the only new thing, we need to rebalance so that we can still have an AVL Tree 
		balance(Node);
	}
	//check if it's there just like in the original BST
	bool contains(const T& Obj, AvlNode* Node)
	{
		if (Node == nullptr)
			Node = new AvlNode{ Obj, nullptr, nullptr };
		else if (Obj < Node->element)
			insert(Obj, Node->left);
		else if (Node->element < Obj)
			insert(Obj, Node->right);
		else
			;
	}
	//we need to rebalance
	void balance(AvlNode*& Node)
	{
		if (Node == nullptr)
			return;
		//let's check all the cases and see where we should rotate
		if (height(Node->left) - height(Node->right) > ALLOWED_IMBALANCE)
			if (height(Node->left->left) >= height(Node->left->right))
				rotateWithLeftChild(Node);
			else
				doubleWithLeftChild(Node);
		else
			if (height(Node->right) - height(Node->left) > ALLOWED_IMBALANCE)
				if (height(Node->right->right) >= height(Node->right->left))
					rotateWithRightChild(Node);
				else
					doubleWithRightChild(Node);
		//let's add one to the height
		Node->height = max(height(Node->left), height(Node->right)) + 1;
	}
	//function that rotates
	void rotateWithLeftChild(AvlNode*& Node2)
	{
		AvlNode * Node1 = Node2->left;
		Node2->left = Node1->right;
		Node1->right = Node2;
		Node2->height = max(height(Node2->left), height(Node2->right)) + 1;
		Node1->height = max(height(Node1->left), Node2->height) + 1;
		Node2 = Node1;
	}
	void rotateWithRightChild(AvlNode*& Node2)
	{
		AvlNode* Node1 = Node2->right;
		Node2->right = Node1->left;
		Node1->left = Node2;
		Node2->height = max(height(Node2->right), height(Node2->left)) + 1;
		Node1->height = max(height(Node1->right), Node2->height) + 1;
		Node2 = Node1;
	}
	//Now it double rotates, but can just call earlier functions
	void doubleWithLeftChild(AvlNode*& k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	void doubleWithRightChild(AvlNode*& k3)
	{
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}
	//function that removes a node
	void remove(const T& x, AvlNode*& Node)
	{
		if (Node == nullptr)
			return; 

		if (x < Node->element)
			remove(x, Node->left);
		else if (Node->element < x)
			remove(x, Node->right);
		else if (Node->left != nullptr && Node->right != nullptr) 
		{
			Node->element = findMin(Node->right)->element;
			remove(Node->element, Node->right);
		}
		else
		{
			AvlNode* oldNode = Node;
			Node = (Node->left != nullptr) ? Node->left : Node->right;
			delete oldNode;
			_size--;
		}

		balance(Node);
	}
	//find max just like normal
	AvlNode* findMax(AvlNode* Node)
	{
		if (Node != nullptr)
			while (Node->right != nullptr)
				Node = Node->right;
		return Node;
	}
	//Now we find min
	AvlNode* findMin(AvlNode* Node)
	{
		if (Node != nullptr)
			while (Node->left != nullptr)
				Node = Node->left;
		return Node;
	}
	//print tree
	void display(ostream& ostream = cout)
	{
		display(root, ostream);
	}
	void display(AvlNode* Node, ostream& ostream)
	{
		if (Node != nullptr)
		{
			display(Node->left, ostream);
			ostream << Node->element << endl;
			display(Node->right, ostream);
		}
	}
};
//int main() {
//	srand(time(0));
//	AVLTree<int> Tree;
//	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
//	
//	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
//	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
//
//	std::cout << "It took me " << time_span.count() << " seconds.";
//	std::cout << std::endl;
//}
//
