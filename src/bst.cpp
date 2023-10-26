#include "bst.h"

BST::BST() : node(NULL) {};

BSTnode *bst_new(int key, void *content)
{
	BSTnode *node = new BSTnode;
	node->content = content;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
}

void BST::insert(int key, void *content)
{
	if (!node)
	{
		node = bst_new(key, content);
		return ;
	}
	BSTnode *temp = node;
	while (temp->left && temp->right)
}

BSTnode BST::search(int key)
{

}
