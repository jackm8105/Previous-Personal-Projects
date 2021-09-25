#include <iostream>
#include "BST.hpp"
using namespace std;
#define COUNT 10
#define DEBUG_PRINT_TREE_HELPER true // true: printTreeHelper() will show parent/child relationships

/*
PUBLIC METHODS:
*/

// Constructor definitions:
// Default:
BST::BST(){
    root = nullptr;
}

// Parameterized constructor. Create the root and initialize key with data value.
BST::BST(int data){
    root = createNode(data);
    cout<< "New tree created with "<<data << "as root node" <<endl;
}

// Destructor
BST::~BST(){
    destroySubTree(root);
}

void BST::insert(int data){
    root = insertHelper(root, data);
    cout<<data<<" has been added"<<endl;
}

// This function will return whether a key is in the tree
bool BST::searchKey(int key){
    Node* tree = searchKeyHelper(root, key);
    if(tree != nullptr) {
        return true;
    }
    cout<<"Key not present in the tree"<<endl;
    return false;
}



void BST::printTree(){
    if(root){
        cout << "ROOT node: "<< root->key << endl;

    }
    printTreeHelper(root);
    cout<<endl;
}



void BST::print2DUtil(int space)
{
    print2DUtilHelper(root, space);
}

bool BST::isValidBST(){
    return isBST(root);
}

vector<int> BST::inorderTree(){
    vector<int> inorder;
    inorderHelper(root,inorder );
    return inorder;
}

//TO DO:



void delOddLeafHelper(Node* root)
{
    Node* current = root;
    if(current->left != nullptr)
    {
        delOddLeafHelper(current->left);
        if(current->key % 2 != 0) //deleting leftmost odd leafNode
        {
            Node* temp = current;
            current->parent = nullptr;
            current = root;
            cout << current->key << "(deleting)" << endl;
            delete temp;

            delOddLeafHelper(current->right);
            if(current->key % 2 != 0) //deleting leftmost odd leafNode
            {
                Node* temp = current;
                current->parent = nullptr;
                current = root;
                cout << current->key << "(deleting)" << endl;
                delete temp;
                return;
            }
        }
        else
        {
            current = root;
            delOddLeafHelper(current->right);
            if(current->key % 2 != 0) //deleting leftmost odd leafNode
            {
                Node* temp = current;
                current->parent = nullptr;
                current = root;
                cout << current->key << "(deleting)" << endl;
                delete temp;
                return;
            }
        }
    }
    return;
}


void BST:: delOddLeaf()
{
    if(root == nullptr) //tree doesn't exist
    {
        return;
    }
    else //tree exists
    {
        delOddLeafHelper(root); //call helper function to delete
    }
}
/*
PRIVATE METHODS:
*/


//   This function will add the data in the tree rooted at currNode.
//   Call this function from insert().


Node* BST:: insertHelper(Node* currNode, int data){
    if(currNode == nullptr){
       return createNode(data);
    }
    else if(currNode->key < data){
        currNode->right = insertHelper(currNode->right,data);
        currNode->right->parent = currNode;
    }
    else if(currNode->key > data){
        currNode->left = insertHelper(currNode->left,data);
        currNode->left->parent = currNode;
    }
    return currNode;
}

// This function will search the data in a tree.
// Call this function from searchKey().

Node* BST::searchKeyHelper(Node* currNode, int data){
    if(currNode == nullptr)
        return nullptr;

    if(currNode->key == data)
        return currNode;

    if(currNode->key > data)
        return searchKeyHelper(currNode->left, data);

    return searchKeyHelper (currNode->right, data);
}

// This function will destroy the subtree rooted at currNode.


void BST:: destroySubTree(Node *currNode){
    if(currNode!=nullptr)
    {
        destroySubTree(currNode->right);
        destroySubTree(currNode->left);

        delete currNode;
        currNode = nullptr;
    }
}

// This function will traverse the tree in-order and print out the node elements.
// printTree() function will call this function.

void BST:: printTreeHelper(Node* currNode){
    if(currNode)
    {
        printTreeHelper( currNode->left);
#if DEBUG_PRINT_TREE_HELPER
        cout << "Node "<< currNode->key << ":\n   left child: ";
        if(currNode->left)
            cout << currNode->left->key;
        else
            cout << "null ";
        cout << "\n   right child: ";
        if(currNode->right)
            cout << currNode->right->key;
        else
            cout << "null ";
        cout << "\n   parent: ";
        if(currNode->parent)
            cout << currNode->parent->key << endl;
        else
            cout << "null " << endl;
#else
        cout << " "<< currNode->key;
#endif

        printTreeHelper(currNode->right);
    }
}

bool BST::isBST(Node *root){
    if(root == nullptr) {
        return true;
    }
    if(root->left != nullptr && root->key < root->left->key)
        return false;

    if(root->right != nullptr && root->key >= root->right->key)
        return false;

    if(!isBST(root->right) || !isBST(root->left))
        return false;

    return true;
}

// Create a new node, setting key value to  input data
// and all pointers to null.
Node* BST:: createNode(int data){
    Node* newNode = new Node;
    newNode->key = data;
    newNode->parent = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* BST::getRoot(){
    return root;
}



/*
   Prints a binary tree in a 2D fashion.
Note: The image of the tree is left rotated by 90 degrees.
*/
void BST::print2DUtilHelper(Node *currNode, int space){
    // Base case
    if (currNode == nullptr)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtilHelper(currNode->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", currNode->key);

    // Process left child
    print2DUtilHelper(currNode->left, space);
}

void BST::inorderHelper(Node *currNode,vector<int>&  inorder)
{
    if (currNode == nullptr)
        return;
    inorderHelper(currNode->left, inorder);
    inorder.push_back(currNode->key);
    inorderHelper(currNode->right, inorder);
}
