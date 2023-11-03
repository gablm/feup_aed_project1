#include "headers/bst.h"

/**
 * Creates a Binary Search Tree (BST)
*/
BST::BST() : node(NULL) {}

/**
 * Create a Binary Search Tree (BST) node, composed of a key and a pointer to its content
 * The left and right nodes are initiated to 0/NULL
 * @note Complexity: O(1)
 * @param key Key of the node
 * @param content Pointer to the content
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
 * Following the concept of a Binary Search Tree, it looks for a place where the next node does not exist and the key is less than the key before it.
 * @note Complexity: O(n)
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

static void *recursive_search(BSTnode *node, int key) {
	if (!node)
		return NULL;
	if (node->key == key)
		return node->content;
	
	if (node->key > key)
		return recursive_search(node->left, key);
	
	return recursive_search(node->right, key);
}

/**
 * Searches the Binary Search Tree (BST) for the content related to the key
 * @note Complexity: O(n) 
 * @param key Key to look for
 * @return The content associated to the key
*/
void *BST::search(int key) {
	return recursive_search(node, key);
}

static void bst_del(BSTnode *node, void (*del)(void *)) {
	if (!node)
		return;
	bst_del(node->left, del);
	bst_del(node->right, del);
	del(node->content);
	node->left = node->right = NULL;
	delete node;
	node = NULL;
}

/**
 * Deletes the entire Binary Search Tree (BST).
 * As the BST stores void pointers, there is a need to ask for an appropriate function to delete the data.
 * @note Complexity: O(n)
 * @param del Function to delete the content
*/
void BST::clear(void (*del)(void *)) {
	bst_del(node, del);
}

/**
 * Returns a pointer to the root node of the Binary Search Tree (BST).
 * @note Complexity: O(1)
 * @return Node
*/
BSTnode *BST::getNode() const {
	return node;
}
