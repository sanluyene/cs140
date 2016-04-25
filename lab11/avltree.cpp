// CS140 Spring 2016
// Lab 11: AVL Tree Playtime
// Author: Ashley Sattler
// Date: 04/22/2016

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "avltree.h"

using namespace std;

// Constructor for our new AVL Tree
AVLTree::AVLTree() {
	sentinel = new AVLTNode;
	sentinel->parent = NULL;
	sentinel->left = NULL;
	sentinel->right = sentinel;
	sentinel->height = -1;
	size = 0;
}

// Deconstructor for our AVL Tree
AVLTree::~AVLTree() {
	recursive_destroy(sentinel->right);
	delete sentinel;
}

// This method will find the appropriate parent node for our new key
// and insert it into our AVL Tree
int AVLTree::Insert(string key, void *val) {
	AVLTNode *parent;
	AVLTNode *n;

	parent = sentinel;
	n = sentinel->right;

	while (n != sentinel) {
		if (n->key == key) return 0;
		parent = n;
		if (key < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}

	n = new AVLTNode;
	n->key = key;
	n->val = val;
	n->parent = parent;
	n->left = sentinel;
	n->right = sentinel;
	if (parent == sentinel) {
		sentinel->right = n;
	} else if (key < parent->key) {
		parent->left = n;
	} else {
		parent->right = n;
	}
	size++;
	n->height = 0;

	if (n->parent != sentinel) Check_Balance(n->parent);

	return 1;
}

// This method will find the specified key in the AVL Tree if it exists
void *AVLTree::Find(string key) {
	AVLTNode *n;

	n = sentinel->right;
	while (1) {
		if (n == sentinel) return NULL;
		if (key == n->key) return n->val;
		if (key < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}
}

// This method will delete the specified key in the AVL Tree if it exists
// and rebalance our tree if necessary
int AVLTree::Delete(string key) {
	AVLTNode *n, *parent, *mlc;
	string tmpkey;
	void *tmpval;

	n = sentinel->right;
	while (n != sentinel && key != n->key) {
		if (key < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}
	if (n == sentinel) return 0;

	parent = n->parent;
	if (n->left == sentinel) {
		if (n == parent->left) {
			parent->left = n->right;
		} else {
			parent->right = n->right;
		}
		if (n->right != sentinel) {
			n->right->parent = parent;
			n->right->height--;
		}
		delete n;
		size--;
	} else if (n->right == sentinel) {
		if (n == parent->left) {
			parent->left = n->left;
		} else {
			parent->right = n->left;
		}
		n->left->parent = parent;
		n->left->height--;
		delete n;
		size--;
	} else {
		for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
		tmpkey = mlc->key;
		tmpval = mlc->val;
		Delete(tmpkey);
		n->key = tmpkey;
		n->val = tmpval;
		n->height--;
	}

	Check_Balance(parent);

	return 1;
}

// This method prints our AVL Tree In Order
void AVLTree::Print() {
	recursive_inorder_print(0, sentinel->right);
}

// This method returns the size of our AVL Tree
int AVLTree::Size() {
	return size;
}

// This method identifies if our AVL Tree is empty or not
int AVLTree::Empty() {
	return (size == 0);
}

// This method will sort our AVL Tree in alphabetical order
vector <void *> AVLTree::Sorted_Vector() {
	array.clear();
	recursive_make_vector(sentinel->right);
	return array;
}

void AVLTree::Check_Balance(AVLTNode *n) {
	int curheight = 0, newheight = 0;

	curheight = n->height;
	if (n->left != sentinel && n->right !=sentinel) {
		newheight = (n->left->height > n->right->height) ? (n->left->height + 1) : (n->right->height + 1);
	}
	else if (n->left != sentinel) newheight = n->left->height + 1;
	else newheight = n->right->height + 1;

	if (curheight != newheight) n = Rebalance(n);

	return;
}

// This method rebalances the tree if necessary to maintain AVL
// Tree constraints
AVLTNode *AVLTree::Rebalance(AVLTNode *n) {
	AVLTNode *lsub, *rsub, *llsub, *rrsub;
	int lheight = 0, rheight = 0, lsheight = 0, rsheight = 0;

	if (abs(n->left->height - n->right->height) < 1) return n;

	// Check which rebalance case we have
	lsub = n->left;
	rsub = n->right;

	// Left Subtree Heavy
	if (lheight > rheight) {
		llsub = lsub->left;
		rrsub = lsub->right;
		lsheight = llsub->height;
		rsheight = rrsub->height;

		// Zig Zig
		if (lsheight > rsheight) {
			Rotate(lsub);
			Check_Balance(lsub->parent);
			return lsub;
		}
		// Zig Zag
		else {
			Rotate(rrsub);
			Rotate(rrsub);
			Check_Balance(rrsub->parent);
			return rrsub;
		}
	}
	// Right Subtree Heavy
	else {
		llsub = rsub->left;
		rrsub = rsub->right;
		lsheight = llsub->height;
		rsheight = rrsub->height;

		// Zig Zag
		if (lsheight > rsheight) {
			Rotate(llsub);
			Rotate(llsub);
			Check_Balance(llsub->parent);
			return llsub;
		}
		// Zig Zig
		else {
			Rotate(rsub);
			Check_Balance(rsub->parent);
			return rsub;
		}
	}

	return n;
}

// This method will rotate the AVL Tree about the specified node
void AVLTree::Rotate(AVLTNode *n) {
	AVLTNode *parent, *child, *oldparent;

	if (Empty()) return;

	// Step 1: identify the parent
	parent = n->parent;
	oldparent = parent->parent;
	if (oldparent->left == parent) oldparent->left = n;
	else oldparent->right = n;

	// Step 2: identify direction to rotate
	// Step 3: identify the subtree that is moving
	// Step 4: form new relationships
	if (parent->left == n) {
		// right rotation
		child = n->right;
		parent->left = child;
		n->right = parent;
	}
	else {
		// left rotation
		child = n->left;
		parent->right = child;
		n->left = parent;
	}

	// Adjust parent pointers
	n->parent = oldparent;
	parent->parent = n;
	if (child != sentinel) child->parent = parent;

	// Adjust heights
	n->height--;
	parent->height++;

	return;
}

// This method will recursively call every node in our tree In Order
void AVLTree::recursive_inorder_print(int level, AVLTNode *n) {
	if (n == sentinel) return;
	recursive_inorder_print(level+2, n->right);
	printf("%*s%s %s\n", level, "", n->height, n->key.c_str());
	recursive_inorder_print(level+2, n->left);
}

// This method will recursively call every node in our tree to create
// a sorted vector
void AVLTree::recursive_make_vector(AVLTNode *n) {
	if (n == sentinel) return;
	recursive_make_vector(n->left);
	array.push_back(n->val);
	recursive_make_vector(n->right);
}

// This method will recursively call and destroy every node in our AVL Tree
void AVLTree::recursive_destroy(AVLTNode *n) {
	if (n == sentinel) return;
	recursive_destroy(n->left);
	recursive_destroy(n->right);
	delete n;
}