#include <iostream>
#include <chrono>
using namespace std;
template <typename T>
class RedBlackTree
{
public:
    
    //colors need to exist
    enum { RED, BLACK };
    //constructor
    explicit RedBlackTree(const T& negInf)
    {
        nullNode = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;

        header = new RedBlackNode{ negInf };
        header->left = header->right = nullNode;
    }
    //node struct
    struct RedBlackNode
    {
        //variables
        T element;
        RedBlackNode* left;
        RedBlackNode* right;
        int color;

        RedBlackNode(const T& theElement = T{ },
            RedBlackNode* lt = nullptr, RedBlackNode* rt = nullptr,
            int c = BLACK)
            : element{ theElement }, left{ lt }, right{ rt }, color{ c } { }

        RedBlackNode(T&& theElement, RedBlackNode* lt = nullptr,
            RedBlackNode* rt = nullptr, int c = BLACK)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, color{ c } { }
    };
    //constructor
    RedBlackTree() { _size = 0; }
    int _size = 0;
    //size function
    int size() 
    {
        return _size;
    }
    //height function
    int height(RedBlackNode* Node) const
    {
        return Node == nullptr ? -1 : Node->height;
    }
    //rotate
    void rotateWithLeftChild(RedBlackNode*& k2)
    {
        RedBlackNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }
    void rotateWithRightChild(RedBlackNode*& k2)
    {
        RedBlackNode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->right), height(k2->left)) + 1;
        k1->height = max(height(k1->right), k2->height) + 1;
        k2 = k1;
    }
    //double rotate
    void doubleWithLeftChild(RedBlackNode*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void doubleWithRightChild(RedBlackNode*& k3)
    {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }
    //all the di
    RedBlackNode* root;

    RedBlackNode* header;
    RedBlackNode* nullNode;

    RedBlackNode* current;
    RedBlackNode* parent;
    RedBlackNode* grand;
    RedBlackNode* great;
    //rotate
    RedBlackNode* rotate(const T& item, RedBlackNode* theParent)
    {
        if (item < theParent->element)
        {
            item < theParent->left->element ?
                rotateWithLeftChild(theParent->left) : // LL
                rotateWithRightChild(theParent->left); // LR
            return theParent->left;
        }
        else
        {
            item < theParent->right->element ?
                rotateWithLeftChild(theParent->right) : // RL
                rotateWithRightChild(theParent->right); // RR
            return theParent->right;
        }
    }
    //function that returns a minimum value
    RedBlackNode* findMin(RedBlackNode* Node) {
        //let's make sure the node isn't empty
        if (Node != nullptr)
            //while it isn't, move to the left
            while (Node->left != nullptr)
                Node = Node->left;
        //we found it!
        return Node;
    }
    //same as above but we go right to find the max
    RedBlackNode* findMax(RedBlackNode* Node)
    {
        if (Node != nullptr)
            while (Node->right != nullptr)
                Node = Node->right;
        return Node;
    }
    //balancer
    void handleReorient(const T& item)
        {
            current->color = RED;
        current->left->color = BLACK;
        current->right->color = BLACK;
        
        if (parent->color == RED) {
            grand->color = RED;
            if (item < grand->element != item < parent->element)
                parent = rotate(item, grand); 
            current = rotate(item, great);
            current->color = BLACK;
        }
            header->right->color = BLACK; 
    }
    //insert function
    void insert(const T& x)
    {
        current = parent = grand = header;
        nullNode->element = x;

        while (current->element != x)
        {
            great = grand; grand = parent; parent = current;
            current = x < current->element ? current->left : current->right;

            if (current->left->color == RED && current->right->color == RED)
                handleReorient(x);
        }

        if (current != nullNode)
            return;
        current = new RedBlackNode{ x, nullNode, nullNode };
        _size++;

        if (x < parent->element)
            parent->left = current;
        else
            parent->right = current;
        handleReorient(x);
    }
};


int main() 
{
    	RedBlackTree <int> Tree;
    	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    	for (int n = 0; n < 1000000; n++) {
    		Tree.insert(n);
    	}
    	
    	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    
    	std::cout << "It took me " << time_span.count() << " seconds.";
    	std::cout << std::endl;
    
}