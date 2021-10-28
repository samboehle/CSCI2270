#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree()
{
	root = nullptr;
}

void deleteTree(MovieNode *node)
{
	if (node == NULL) return;

	deleteTree(node->left);
	deleteTree(node->right);

	node = NULL;
}

MovieTree::~MovieTree() 
{
	deleteTree(root);
}

void printHelper(MovieNode *node)
{
	if(node == nullptr)
	{
		return;
	}

	printHelper(node->left);
	cout << "Movie: " << node->title << " " << node->rating << endl;
	printHelper(node->right);
}

void MovieTree::printMovieInventory() 
{
	if(root == nullptr)
	{
		cout << "Tree is Empty. Cannot print" << endl;
	}
	else
	{
		printHelper(root);
	}
}

MovieNode *insertHelper(MovieNode *node, int ranking, string title, int year, float rating)
{
	if(node == nullptr)
	{
		return getMovieNode(ranking, title, year, rating);
	}
	else if(node->title <= title)
	{
		node->right = insertHelper(node->right, ranking, title, year, rating);
	}
	else if(node->title > title)
	{
		node->left = insertHelper(node->left, ranking, title, year, rating);
	}
	return node;
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) 
{
	root = insertHelper(root, ranking, title, year, rating);
}

MovieNode *searchHelp(MovieNode *node, string title)
{
	if(node == nullptr || node->title == title)
	{
		return node;
	}
	if(node->title < title)
	{
		return searchHelp(node->right, title);
	}
	return searchHelp(node->left, title);
}

void MovieTree::findMovie(string title)
{
	MovieNode * node = searchHelp(root, title);
	if(node == nullptr)
	{
		cout << "Movie not found." << endl;
		return;
	}
	cout << "Movie Info:" << endl;
	cout << "==================" << endl;
	cout << "Ranking:" << node->ranking << endl;
	cout << "Title  :" << node->title << endl;
	cout << "Year   :" << node->year << endl;
	cout << "rating :" << node->rating << endl;
}

void queryHelp(MovieNode *node, float rating, int year)
{

	if(node != NULL)
	{
		if(node->rating >= rating && node->year > year)
		{
			cout << node->title << "(" << node->year << ") " << node->rating << endl;
		}
		queryHelp(node->left, rating, year);
		queryHelp(node->right, rating, year);
	}
}

void MovieTree::queryMovies(float rating, int year)
{
	if(root == nullptr)
	{
		cout << "Tree is Empty. Cannot query Movies" << endl;
		return;
	}
	cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
	queryHelp(root, rating, year);
}

float sum(MovieNode * node)
{
	if(node == nullptr)
	{
		return 0;
	}
	return node->rating + sum(node->right) + sum(node->left);
}

int count(MovieNode * node)
{
	if(node == nullptr)
	{
		return 0;
	}
	return 1 + count(node->right) + count (node->left);
}

void MovieTree::averageRating()
{
	if(root == nullptr)
	{
		cout << "Average rating:0.0" << endl;
		return;
	}
	cout << "Average rating:" << sum(root) / count(root) << endl;
}

void printHelp(MovieNode *node, int l)
{
	if(node == nullptr)
	{
		return;
	}

	if(l == 0)
	{
		cout << "Movie: " << node->title << " " << node->rating << endl;
		return;
	}
	printHelp(node->left, l -1);
	printHelp(node->right, l -1);
}
void MovieTree::printLevelNodes(int k)
{
	printHelp(root, k);
}
