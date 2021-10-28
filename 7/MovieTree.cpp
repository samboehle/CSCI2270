#include <iostream>
#include <fstream>
#include <string>
#include "MovieTree.hpp"

using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode;
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next = NULL;
	return lmn;
}
/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}
/* ------------------------------------------------------ */

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

void printHelper(TreeNode *node)
{
	if(node == nullptr)
	{
		return;
	}

	printHelper(node->leftChild);
	cout << "Movies starting with letter: " << node->titleChar << endl;
	LLMovieNode *ptr = node->head;
	while(ptr != NULL)
	{
		cout << " >> " << ptr->title << " " << ptr->rating << endl;
		ptr = ptr->next;
	}
	printHelper(node->rightChild);
}

void MovieTree::showMovieCollection()
{
	printHelper(root);
}

TreeNode *getTreeNode(TreeNode *prev, char title, LLMovieNode *llmn)
{
	TreeNode *nn = new TreeNode();

	nn->parent = prev;
	nn->titleChar = title;
	nn->head = llmn;
	return nn;
}

TreeNode *insertHelper(TreeNode *node, TreeNode *parent, char title, LLMovieNode *llmn)
{
 	if(node == NULL)
	{
		return getTreeNode(parent, title, llmn);
	}
	else if (node->titleChar <= title)
	{
		node->rightChild = insertHelper(node->rightChild, node, title, llmn);
	}
	else if(node->titleChar > title)
	{
		node->leftChild = insertHelper(node->leftChild, node, title, llmn);
	}
	return node;
}

void MovieTree::insertMovie(int ranking, std::string title, int year, float rating)
{
	LLMovieNode *node = getLLMovieNode(ranking, title, year, rating);

	TreeNode *ptr = searchCharNode(title[0]);

	if(ptr == NULL && root == NULL)
	{
		root = getTreeNode(NULL, title[0], node);
	}
	else if(ptr == NULL)
	{
		root = insertHelper(root, NULL, title[0], node);
	}
	else
	{
		if(ptr->head->title > title || ptr->head == NULL)
		{
			node->next = ptr->head;
			ptr->head = node;
		}
		else
		{
			LLMovieNode *current = ptr->head;
			while(current->next != NULL && current->next->title < node->title)
			{
				current = current->next;
			}
			node->next = current->next;
			current->next = node;
		}
		
	}
	

}


TreeNode *getMinValueNode(TreeNode* currNode){

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

TreeNode *deleteNode(TreeNode *currNode, char value)
{

  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->titleChar)
  {
    currNode->leftChild = deleteNode(currNode->leftChild, value);
  }
  else if(value > currNode->titleChar)
  {
    currNode->rightChild = deleteNode(currNode->rightChild, value);
  }
  // We found the node with the value
  else
  {
    //TODO Case : No child
    if(currNode->leftChild == NULL && currNode->rightChild == NULL)
    {
        delete currNode;
        return nullptr;
    }
    //TODO Case : Only right child
    else if(currNode->leftChild == NULL)
    {
        TreeNode *p_right = currNode->rightChild;

		p_right->parent = currNode->parent;
        delete currNode;
        return p_right;
    }
    //TODO Case : Only left child
    else if(currNode->rightChild == NULL)
    {
        TreeNode *p_left = currNode->leftChild;

		p_left->parent = currNode->parent;
        delete currNode;
        return p_left;
    }
    //TODO Case: Both left and right child
    else
    {
        //Replace with Minimum from right subtree
        TreeNode *min = getMinValueNode(currNode->rightChild);

        currNode->titleChar = min->titleChar;
		currNode->head = min->head;
        currNode->rightChild = deleteNode(currNode->rightChild, min->titleChar);
    }

  }
	return currNode;
}



void MovieTree::removeMovieRecord(string title)
{
	TreeNode *ptr = searchCharNode(title[0]);

	if(ptr == NULL)
	{
		cout << "Movie not found."<< endl;
		return;
	}

	if(ptr->head->title == title)
    {
        LLMovieNode *temp = ptr->head;

        ptr->head = ptr->head->next;

        delete temp;
    }
    else
    {
       LLMovieNode *current = ptr->head;

       while(current->next != NULL)
       {
           if(current->title == title)
           {
               break;
           }
           current = current->next;
       }
       if(current->title != title)
       {
           cout << "Movie not found."<< endl;
           return;
       }

       LLMovieNode *crawler = ptr->head;

       while(crawler->next != current)
       {
           crawler = crawler->next;
       }

       crawler->next = current->next;
       delete current;


    }

	if(ptr->head == NULL)
	{
		root = deleteNode(root, ptr->titleChar);
	}

}


void MovieTree::leftRotation(TreeNode *current)
{
	if(current == root)
	{
		TreeNode *x = current;
		TreeNode *y = current->rightChild;
		y->parent = NULL;
		x->parent = y;
		x->rightChild = y->leftChild;
		y->leftChild = x;
		root = y;

	}
	else if(current->rightChild == NULL)
	{

	}
	else
	{
		TreeNode *xp = current->parent;
		TreeNode *x = current;
		TreeNode *y = current->rightChild;
		y->parent = x->parent;
		x->parent = y;

		x->rightChild = y->leftChild;
		y->leftChild = x;

		if(xp->titleChar > x->titleChar)
		{
			xp->leftChild = y;
		}
		else
		{
			xp->rightChild = y;
		}
	}
	
}

void destroyTree(TreeNode* curr)
{
   if (curr != NULL)
   {
       destroyTree(curr->leftChild);
       destroyTree(curr->rightChild);
       delete curr;
       if (curr -> leftChild != nullptr)
       {
           curr -> leftChild = nullptr;
       }
       if (curr -> rightChild != nullptr)
       {
           curr -> rightChild = nullptr;
       }
       curr = NULL;
   }
}

void deleteList(LLMovieNode *head)  
{  
	LLMovieNode* current = head;  
	LLMovieNode* next;  
	
	while (current != NULL)  
	{  
		next = current->next;  
		delete current;  
		current = next;  
	}  
	head = NULL;  
}  

void deleteHelper(TreeNode *curr)
{
	if(curr == NULL)
	{
		return;
	}
	deleteHelper(curr->rightChild);
	deleteHelper(curr->leftChild);
	deleteList(curr->head);
	delete curr;

}

MovieTree::~MovieTree()
{
	deleteHelper(root);
}