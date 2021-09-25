#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>
#include <cmath>
#include <queue>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST
MovieNode* getMovieNode(int rank, string t, int y, float r)
{
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank; 
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() 
{
  root->year = 0;
  root->title = "";
  root->rating = 0;
  root->left = NULL;
  root->right = NULL;
}

MovieTree::~MovieTree() 
{
  if (root == NULL) 
    {
      return;
    }

    delete root->left;
    delete root->right;
    cout<<"\n Deleting node:"<< root->title;
    delete root;  
}

void helpToPrint(MovieNode* node)
{
  if(node == NULL)
  {
    return;
  }

  helpToPrint(node->left);
  cout << "Movie: " << node->title << " " << node->rating << endl;
  helpToPrint(node->right);
}


void MovieTree::printMovieInventory() 
{
  if(root != NULL)
  {
    helpToPrint(root);
  }
  else
  {
    cout << "Tree is empty. Cannot print" << endl;
    return;
  }
}

MovieNode* addMovieHelper(MovieNode* node, MovieNode* current)
{
  if(current == NULL)
  {
    return node;
  }

  if(node->title.compare(current->title) < 0)
  {
    current->left = addMovieHelper(node, current->left);
    return current;
  }
  else
  {
    current->right = addMovieHelper(node, current->right);
    return current;
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) 
{
  MovieNode* node = new MovieNode;
  node->ranking = ranking;
  node->title = title;
  node->year = year;
  node->rating = rating;
  root = addMovieHelper(node, root);
}

void helpFindMovie(MovieNode* node, string title)
{
  if(node == NULL)
  {
    cout << "Movie not found." << endl;
    return;
  }

  if(node->title.compare(title) == 0)
  {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << node->ranking << endl;
    cout << "Title  :" << node->title << endl;
    cout << "Year   :" << node->year << endl;
    cout << "rating :" << node->rating << endl;
  }
  else if(node->title.compare(title) > 0)
  {
    helpFindMovie(node->left, title);
  }
  else
  {
    helpFindMovie(node->right, title);
  }
}

void MovieTree::findMovie(string title) 
{
  helpFindMovie(root, title);
}

void helpQuery(MovieNode* node, int year, float rating)
{
  if(node == NULL)
  {
    return;
  }
  
  if(node->year >= year && node->rating >= rating)
  {
    cout << node->title << "(" << node->year << ") " << node->rating << endl;
  }

  helpQuery(node->left, year, rating);
  helpQuery(node->right, year, rating);
}

void MovieTree::queryMovies(float rating, int year)
{
  if(root != NULL)
  {
    cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
    helpQuery(root, year, rating);
  }
  else
  {
    cout << "Tree is empty. Cannot query movies" << endl;
    return;
  }  
}

float RTotal(MovieNode* node)
{
  float totalRate = 0;
  if(node == NULL)
  {
    return 0;
  }
  else
  {
    totalRate = node->rating + RTotal(node->left) + RTotal(node->right);
    return totalRate;
  }
}


int totalNode(MovieNode* node)
{
  int Ntotal = 0;
  if(node == NULL)
  {
    return 0;
  }
  else
  {
    Ntotal = totalNode(node->left) + totalNode(node->right) + 1;
    return Ntotal;
  }
}

void MovieTree::averageRating()
{
  if(root == NULL)
  {
    cout << "Average rating:0.0" << endl;
  }
  else
  {
    cout << "Average rating:" << RTotal(root) / totalNode(root) << endl;
  }
}

void helpPrintNodes(MovieNode* node, int level)
{
  if(node != NULL)
  {
    helpPrintNodes(node->left, level - 1);
    if(level == 0)
    {
      cout << "Movie: " << node->title << " " << node->rating << endl;
    }
    helpPrintNodes(node->right, level - 1);
  }
}

void MovieTree::printLevelNodes(int k)
{
  MovieNode* current = root;
  if(root == NULL)
  {
    return;
  }
  else if(k >= 0)
  {
    helpPrintNodes(current, k);
  }
}
