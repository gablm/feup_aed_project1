#include "bst.h"

/**
 * Creates a Binary Search Tree (BST)
*/
BST::BST() : node(NULL) {}

/**
 * Create a BST node, composed of a key + content
 * The left and right nodes are initiated to 0/NULL
 * @param key Key of the node
 * @param content Content on the node
*/
BSTnode *bst_new(int key, void *content)
{
	BSTnode *node = new BSTnode;
	node->content = content;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/**
 * Inserts a new node in the BST.
 * Following the concept of a Binary Search Tree, it looks for a place where the next node does not exist and the key is less than the key before it
 * @param key Key of the new node
 * @param content Content on the new node
*/
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

/**
 * Searches the BST for the content related to the key
 * @param key Key to look for
 * @return The content associated to the key
*/
void *BST::search(int key)
{
	BSTnode *temp = node;
	while (temp->key != key)
		temp = (temp->right->key > key) ? temp->left : temp->right;
	return temp->content;
}

void bst_del(BSTnode *node, void (*del)(void *)) {
	if (!node)
		return;
	bst_del(node->left, del);
	bst_del(node->right, del);
	del(node->content);
	delete node;
	node->left = node->right = NULL;
	node = NULL;
}

void BST::clear(void (*del)(void *)) {
	bst_del(node, del);
}

BSTnode *BST::getNode() const {
	return node;
}
