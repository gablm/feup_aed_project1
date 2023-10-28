#ifndef BST_H
#define BST_H

#include <iostream>

typedef struct node {
    int key;
	void *content;
    struct node *left, *right;
} BSTnode;

class BST {
	private:
		BSTnode *node;
	public:
		BST();
		void insert(int key, void *content);
		void *search(int key);
		BSTnode *getNode() const;
		void clear();
};

#endif