#include "bst.h"

BST::BST() : node(NULL) {}

BSTnode *bst_new(int key, void *content)
{
	BSTnode *node = new BSTnode;
	node->content = content;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void BST::insert(int key, void *content)
{
	BSTnode *new_node = bst_new(key, content);
	if (!node)
	{
		node = new_node;
		return ;
	}
	BSTnode *temp = node;
	BSTnode *last = NULL;
	while (temp)
	{
		last = temp;
		if (temp->key > key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	if (last->key > key)
		last->left = new_node;
	else
		last->right = new_node;
}

BSTnode BST::search(int key)
{
	BSTnode *temp = node;
	while (temp->key != key)
		temp = (temp->right->key > key) ? temp->left : temp->right;
	return *temp;
}
