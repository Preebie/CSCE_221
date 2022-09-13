// C++ program to insert element in Binary Tree
#include <iostream>
#include <queue>
using namespace std;

/* A binary tree node has data, pointer to left child
and a pointer to right child */

struct Node {
    int data;
    Node* left;
    Node* right;
};

/* Function to create a new node */

Node* CreateNode(int data)
{
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/* Function to insert element in binary tree */

Node* InsertNode(Node* root, int data)
{
    // If the tree is empty, assign new node address to root
    if (root == NULL) {
        root = CreateNode(data);
        return root;
    }

    // Else, do level order traversal until we find an empty
    // place, i.e. either left child or right child of some
    // node is pointing to NULL.
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);
        else {
            temp->left = CreateNode(data);
            return root;
        }

        if (temp->right != NULL)
            q.push(temp->right);
        else {
            temp->right = CreateNode(data);
            return root;
        }
    }
}

/* Inorder traversal of a binary tree */

void inorder(Node* temp)
{
    if (temp == NULL)
        return;

    inorder(temp->left);
    cout << endl;
    cout << temp->data << ' ';
    inorder(temp->right);
}

// Driver code
int main()
{
    Node* root = CreateNode(22);
   
    root = InsertNode(root, 12);
    root = InsertNode(root, 11);
    root = InsertNode(root, 8);
    root = InsertNode(root, 9);
    root = InsertNode(root, 3);
    root = InsertNode(root, 4);
    root = InsertNode(root, 33);
    root = InsertNode(root, 17);

    cout << "Inorder traversal after insertion: ";
    inorder(root);
    cout << endl;

    return 0;
}