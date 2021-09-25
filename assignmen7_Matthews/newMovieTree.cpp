#include <iostream>
#include <fstream>
#include "newMovieTree.hpp"

using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}
/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}
/* ------------------------------------------------------ */


void deleteSubTree(TreeNode* curr)
{
  if(curr == NULL)
  {
    return;
  }
  deleteSubTree(curr->leftChild);
  deleteSubTree(curr->rightChild);
  LLMovieNode* currMovie = curr->head;
  while(currMovie != NULL)
  {
    LLMovieNode* tempMovie = currMovie->next;
    delete currMovie;
    currMovie = tempMovie;
  }
  delete curr;
}

MovieTree::~MovieTree()
{
  deleteSubTree(root);
}


void helpShowMovies(TreeNode* node)
{
  if(node == NULL)
  {
    return;
  }

  LLMovieNode *curr;
  curr = node->head;
  helpShowMovies(node->leftChild);
  cout << "Movies starting with letter: " << node->titleChar << endl;
  while(curr != NULL)
  {
    cout << " >> " << curr->title << " " << curr->rating << endl;
    curr = curr->next;
  }
  helpShowMovies(node->rightChild);
}


void MovieTree::showMovieCollection() 
{
  if(root != NULL)
  {
    helpShowMovies(root);
  }
  else
  {
    return;
  }
}


void helpInsertMovie(LLMovieNode* movieNode, TreeNode* treeNode)
{
  if(movieNode == NULL)
  {
    return;
  }

  if(movieNode->title[0] < treeNode->titleChar)
  {
    if(treeNode->leftChild == NULL)
    {
      treeNode->leftChild = new TreeNode;
      treeNode->leftChild->parent = treeNode;
      treeNode->leftChild->titleChar = movieNode->title[0];
      treeNode->leftChild->head = movieNode;
    }
    else
    {
      helpInsertMovie(movieNode, treeNode->leftChild);
    }    
    return;
  }
  else if(movieNode->title[0] > treeNode->titleChar)
  {
    if(treeNode->rightChild == NULL)
    {
      treeNode->rightChild = new TreeNode;
      treeNode->rightChild->parent = treeNode;
      treeNode->rightChild->titleChar = movieNode->title[0];
      treeNode->rightChild->head = movieNode;
    }
    else
    {
      helpInsertMovie(movieNode, treeNode->rightChild);
    }
    return;
  }
  else
  {
    if(treeNode->head == NULL)
    {
      treeNode->head = movieNode;
    }
    else if(treeNode->head->title.compare(movieNode->title) > 0)
    {
      LLMovieNode* newNode;
      newNode = treeNode->head;
      treeNode->head = movieNode;
      movieNode->next = newNode;
    }
    else
    {
      LLMovieNode* current = treeNode->head;
      while(current->next && current->next->title.compare(movieNode->title) < 0)
      {
        current = current->next;
      }
      LLMovieNode* newNode;
      newNode = current->next;
      current->next = movieNode;
      movieNode->next = newNode;
    }
  }
}

void MovieTree::insertMovie(int ranking, string title, int year, float rating) 
{
  if(root == NULL)
  {
    root = new TreeNode;
    root->titleChar = title[0];
  }
  LLMovieNode* node = new LLMovieNode;
  node->ranking = ranking;
  node->title = title;
  node->year = year;
  node->rating = rating;
  helpInsertMovie(node, root);
}


void helpingHelpRemove(TreeNode* current, TreeNode* &root)
{
  TreeNode* tempTree;
  if(current->rightChild != NULL)
  {
    TreeNode* leftMostDescendant = current->rightChild;
    while(leftMostDescendant->leftChild != NULL)
    {
      leftMostDescendant = leftMostDescendant->leftChild;
    }
    //special case in which parent only has one right child with no left grandchildren and we're deleting parent
    if(leftMostDescendant == current->rightChild)
    {
      if(current->leftChild != NULL)
      {
        leftMostDescendant->leftChild = current->leftChild;
        current->leftChild->parent = leftMostDescendant;
      }

      if(current->parent != NULL)
      {
        TreeNode* parent = current->parent;
        bool currentWasLeftChild = current == parent->leftChild; 
        if(currentWasLeftChild) // checks if current is a left or right child and updates parent for new value
        {
          parent->leftChild = leftMostDescendant;
        }
        else
        {
          parent->rightChild = leftMostDescendant;
        }
        leftMostDescendant->parent = parent;
      }
      else
      {
        root = leftMostDescendant;
        leftMostDescendant->parent = NULL;
      }
      delete current->head;
      delete current;
      return;
    }

    //removing lefmost child in right subtree, and connecting its' parents and children to each other
    if(leftMostDescendant->rightChild != NULL)
    {
      TreeNode* newLeftMostChild = leftMostDescendant->rightChild;
      TreeNode* parentOfOldLeftMost = leftMostDescendant->parent;
      newLeftMostChild->parent = parentOfOldLeftMost;
      parentOfOldLeftMost->leftChild = newLeftMostChild;
    }
    else
    {
      TreeNode* parentOfOldLeftMost = leftMostDescendant->parent;
      parentOfOldLeftMost->leftChild = NULL;
    }
    

    // connects leftmost descendant to children of node we are trying to delete
    if(current->leftChild != NULL)
    {
      leftMostDescendant->leftChild = current->leftChild;
      leftMostDescendant->leftChild->parent = leftMostDescendant;
    }
    leftMostDescendant->rightChild = current->rightChild;
    leftMostDescendant->rightChild->parent = leftMostDescendant;

    // connects parents of current to leftmost descendant 
    if(current->parent != NULL)
    {
      TreeNode* parent = current->parent;
      bool currentWasLeftChild = current == parent->leftChild; 
      if(currentWasLeftChild) // checks if current is a left or right child and updates parent for new value
      {
        parent->leftChild = leftMostDescendant;
      }
      else
      {
        parent->rightChild = leftMostDescendant;
      }
      leftMostDescendant->parent = parent;
    }
    else // current is the root of tree
    {
      leftMostDescendant->parent = NULL;
      root = leftMostDescendant;
    }
    delete current->head;
    delete current;
    return;
  }
  else
  {
    if(current->parent != NULL)
    {
      TreeNode* parent = current->parent;
      bool currentWasLeftChild = current == parent->leftChild;
      if(currentWasLeftChild) // checks if current is a left or right child and updates parent for new value
      {
        parent->leftChild = current->leftChild;
      }
      else
      {
        parent->rightChild = current->leftChild;
      }
      if(current->leftChild != NULL)
      {
        current->leftChild->parent = parent;
      }
    }
    else // current is the root of tree
    {
      if(current->leftChild != NULL)
      {
        current->leftChild->parent = NULL;
        root = current->leftChild;
      }
      else
      {
        root = NULL;
      }
    }
    delete current->head;
    delete current;
    return;
  }
}


void helpRemove(string name, TreeNode* treeNode, TreeNode* &root)
{
  if(treeNode == NULL)
  {
    cout << "Movie not found." << endl;
    return;
  }
  TreeNode* current = treeNode;
  if(name[0] < treeNode->titleChar)
  {
    helpRemove(name, treeNode->leftChild, root);
  }
  else if(name[0] > treeNode->titleChar)
  {
    helpRemove(name, treeNode->rightChild, root);
  }
  else if(name[0] == treeNode->titleChar)
  {
    if(treeNode->head == NULL)
    {
      cout << "Movie not found." << endl;
      return;
    }
    if(treeNode->head->title == name && treeNode->head->next == NULL)
    {
      helpingHelpRemove(current, root);
    }
    else if(treeNode->head->title == name)
    {
      LLMovieNode* temp = treeNode->head;
      treeNode->head = temp->next;
      delete temp;
    }
    else
    {
      LLMovieNode* currNode = treeNode->head;
      LLMovieNode* temp = NULL;
      while(currNode->next != NULL && currNode->next->title != name)
      {
        currNode = currNode->next;
      }
      if(currNode->next != NULL && currNode->next->title == name)
      {
        temp = currNode->next;
        currNode->next = temp->next;
        delete temp;
      }
      else
      {
        cout << "Movie not found." << endl;
        return;
      }
    }
  }
  return;
}

void MovieTree::removeMovieRecord(string title)
{
  if(root == NULL)
  {
    cout << "Movie not found." << endl;
    return;
  }
  else if(title == "")
  {
    cout << "Movie not found." << endl;
    return;
  }
  else
  {
    helpRemove(title, root, root);
  }
}


void MovieTree::leftRotation(TreeNode* x)
{
  TreeNode* y = x->rightChild;
  TreeNode* xp = x->parent;
  if(y != NULL)
  {
    TreeNode* yl = y->leftChild;

    //make x the leftChild of y
    y->leftChild = x;
    x->parent = y;

    x->rightChild = yl;
    if(yl != NULL)
    {
      yl->parent = x;
    }

    if(xp != NULL)
    {
      bool xWasLeftChild = x == xp->leftChild;
      //make xp, the parent of y
      if(xWasLeftChild) // checks if current is a left or right child and updates parent for new value
      {
        xp->leftChild = y;
      }
      else
      {
        xp->rightChild = y;
      }
      y->parent = xp;
    }
    else // x is the root
    {
      root = y;
      y->parent = NULL;
    }
  }
  else // x had no right child D:
  {
    //NO OP
  }
}

void _grader_inorderTraversal(TreeNode * root) {
		if (root == NULL) {
			return;
		}

		_grader_inorderTraversal(root->leftChild);
		cout << root->titleChar << " ";
		_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}



TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}
