#include <iostream>
#include <chrono>

using namespace std;


template <typename T, typename Comparator = less<T>>
class BinarySearchTree
{
public:

	//create struct for node in tree
	struct BinaryNode
	{
		//templated element
		T element;
		//define both sides of the node
		BinaryNode* left;
		BinaryNode* right;
		//create node
		BinaryNode(T& theElement, BinaryNode* lt, BinaryNode* rt)
			: element{ theElement }, left{ lt }, right{ rt } { }

		BinaryNode(T&& theElement, BinaryNode* lt, BinaryNode* rt)
			: element{ std::move(theElement) }, left{ lt }, right{ rt } { }
	};
	//define necessary variables
	int _size;
	BinaryNode* root;
	Comparator isLessThan;
	//constructor
	BinarySearchTree()
	{
		root = nullptr;
		_size = 0;
	}
	//define size function to return size
	int size() {
		return _size;
	}
	//define contains function
	bool contains(const T& Obj, BinaryNode* Node)
	{
		//check if empty tree or if we didn't find it
		if (Node == nullptr)
			return false;
		//decide which way to go and call recursively
		else if (Obj->element < Obj)
			return contains(Obj, Node->right);
		else if (Obj < Node->element)
			return contains(Obj, Node->left);
		//we found it!
		else
			return true; 
	}
	//function that returns a minimum value
	BinaryNode* findMin(BinaryNode* Node) {
		//let's make sure the node isn't empty
		if (Node != nullptr)
			//while it isn't, move to the left
			while (Node->left != nullptr)
				Node = Node->left;
		//we found it!
		return Node;
	}
	//same as above but we go right to find the max
	BinaryNode* findMax(BinaryNode* Node)
	{
		if (Node != nullptr)
			while (Node->right != nullptr)
				Node = Node->right;
		return Node;
	}
	//the heftiest operation, insert
	void insert(T& Obj, BinaryNode*& Node)
	{
		//empty tree means we just insert, or if we find a nullptr we insert
		if (Node == nullptr) {
			Node = new BinaryNode{ Obj, nullptr, nullptr };
			_size++;
		}
		//call it recursively until we find a place where it fits
		else if (Obj < Node->element) {
			while (Node != nullptr && (Obj < Node->element)) {
				Node = Node->left;
			}
			insert(Obj, Node);
		}
		else if (Node->element < Obj) {
			while (Node != nullptr && (Node->element < Obj)) {
				Node = Node->right;
			}
			insert(Obj, Node);
		}
	}
	//destructor
	~BinarySearchTree() {
		makeEmpty(root);
	}
	//deleting time
	void remove(const T& Obj, BinaryNode*& Node)
	{
		//empty tree time
		if (Node == nullptr)
			return;
		//we gotta find the number to remove the number so lets be recursive again
		if (Obj < Node->element)
			remove(Obj, Node->left);
		else if (Node->element < Obj)
			remove(Obj, Node->right);
		else if (Node->left != nullptr && Node->right != nullptr)
		{
			Node->element = findMin(Node->right)->element;
			remove(Node->element, Node->right);
		}
		//we found it!
		else
		{
			BinaryNode* oldNode = Node;
			Node = (Node->left != nullptr) ? Node->left : Node->right;
			delete oldNode;
		}
	}
	//lets empty the tree so the destructor works
	void makeEmpty(BinaryNode*& Node)
	{
		//we can't delete what isn't there so we check
		if (Node != nullptr)
		{
			//let's go down the line and do the rest before the root so we don't lose them
			makeEmpty(Node->left);
			makeEmpty(Node->right);
			//and finally, we delete the original
			delete Node;
		}
		//The tree still needs to exist, so
		Node = nullptr;
	}
	//copy constructor
	BinarySearchTree(const BinarySearchTree& rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}
	//helper for the copy constructor
	BinaryNode* clone(BinaryNode* Node)
	{
		if (Node == nullptr)
			return nullptr;
		else
			return new BinaryNode{ Node->element, clone(Node->left), clone(Node->right) };
	}
	//need function to print
	void display(BinaryNode* Node, ostream& out)
	{
		if (Node != nullptr)
		{
			display(Node->left, out);
			out << Node->element << endl;
			display(Node->right, out);
		}
	}
};


//-------------------------------------------------------------------------------------------------------------------------------//







//int main() {
//	BinarySearchTree <int> Tree;
//	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
//	for (int n = 0; n < 1000000; n++) {
//		Tree.insert(n, Tree.root);
//	}
//	
//	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
//	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
//
//	std::cout << "It took me " << time_span.count() << " seconds.";
//	std::cout << std::endl;
//
//}