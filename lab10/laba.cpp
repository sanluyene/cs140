// CS140 Spring 2016
// Lab 10: Binary Search Tree Playtime
// Author: Ashley Sattler
// Date: 04/15/2016

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "laba.h"

using namespace std;

// These methods are the new ones we implement for this lab

// This method will print our tree in postorder
void BSTree::Postorder() {
	recursive_postorder(0, sentinel->right);
}

// This method will print our tree in preorder
void BSTree::Preorder() {
	recursive_preorder(0, sentinel->right);
}

// This method will return the depth of the specified key
int BSTree::Depth(string key) {
	BSTNode *n;
	int depth = 0; 

	if (Find(key) == NULL) return -1;

	n = sentinel->right;
	while (1) {
		if (n == sentinel) return -1;
		if (key == n->key) return depth;
		depth++;
		if (key < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}
}

// This method will return the height of our tree
int BSTree::Height() {
	int height = 0;

	if (Empty()) return -1;
	height = recursive_height(sentinel->right);
	return height;
}

// This method will return whether or not the tree is AVL balanced
int BSTree::IsAVL() {
	int rheight = 0, lheight = 0;
	BSTNode *n;

	if (Empty()) return 1;

	n = sentinel->right;

	if (n->left != sentinel) lheight = recursive_height_and_avl_check(n->left);
	if (n->right != sentinel) rheight = recursive_height_and_avl_check(n->right);

	if ((abs(lheight - rheight)) > 1) return 0;
	//	else if (lheight > rheight) return lheight;
	else return 1;
}

// This method will attempt to rotate our tree on the specified key
int BSTree::Rotate(string key) {
	BSTNode *n, *parent, *child, *oldparent;

	if (Empty()) return 0;

	n = sentinel->right;
	if (n->key == key) return 0;

	// First we need to find the node of the specified key, if it exists
	while (1) {
		if (n == sentinel || n == NULL) return 0;
		if (key == n->key) break;
		if (key < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}

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

	return 1;
}

// This method will call recursively every node in our tree in
// preorder: step 1 print yourself, step 2 print your left child,
// step 3 print your right child
void BSTree::recursive_preorder(int level, BSTNode *n) {
	if (n == sentinel) return;
	printf("%*s%s\n", level, "", n->key.c_str());
	recursive_preorder((level + 2), n->left);
	recursive_preorder((level + 2), n->right);
}

// This method will call recursively every node in our tree in
// postorder: step 1 print your left child, step 2 print your right
// child, step 3 print yourself
void BSTree::recursive_postorder(int level, BSTNode *n) {
	if (n == sentinel) return;
	recursive_postorder((level + 2), n->left);
	recursive_postorder((level + 2), n->right);
	printf("%*s%s\n", level, "", n->key.c_str());
}

// This method will call recursively every node in our tree in order
// to find the deepest depth of our tree (the height)
int BSTree::recursive_height(BSTNode *n) {
	int lheight = -1, rheight = -1;

	if (n->left != sentinel) lheight = recursive_height(n->left);
	if (n->right != sentinel) rheight = recursive_height(n->right);

	if (lheight > rheight) return lheight + 1;
	else return rheight + 1;
}

// This method will call recursively to determine the height on the
// left and right sides of our tree to check for AVL balance
// (they may only differ by 1)
int BSTree::recursive_height_and_avl_check(BSTNode *n) {
	int lheight = -1, rheight = -1;

	if (n->left != sentinel) lheight = recursive_height_and_avl_check(n->left);
	if (n->right != sentinel) rheight = recursive_height_and_avl_check(n->right);

	if (lheight > rheight) return lheight + 1;
	else return rheight + 1;
}


// These methods below were given to us by the instructor
BSTree::BSTree()
{
	sentinel = new BSTNode;
	sentinel->parent = NULL;
	sentinel->left = NULL;
	sentinel->right = sentinel;
	size = 0;
}

BSTree::~BSTree()
{
	recursive_destroy(sentinel->right);
	delete sentinel;
}

int BSTree::Insert(string s, void *val)
{
	BSTNode *parent;
	BSTNode *n;

	parent = sentinel;
	n = sentinel->right;

	while (n != sentinel) {
		if (n->key == s) return 0;
		parent = n;
		if (s < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}

	n = new BSTNode;
	n->key = s;
	n->val = val;
	n->parent = parent;
	n->left = sentinel;
	n->right = sentinel;
	if (parent == sentinel) {
		sentinel->right = n;
	} else if (s < parent->key) {
		parent->left = n;
	} else {
		parent->right = n;
	}
	size++;
	return 1;
}

void *BSTree::Find(string s)
{
	BSTNode *n;

	n = sentinel->right;
	while (1) {
		if (n == sentinel) return NULL;
		if (s == n->key) return n->val;
		if (s < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}
}

int BSTree::Delete(string s)
{
	BSTNode *n, *parent, *mlc;
	string tmpkey;
	void *tmpval;

	n = sentinel->right;
	while (n != sentinel && s != n->key) {
		if (s < n->key) {
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
		if (n->right != sentinel) n->right->parent = parent;
		delete n;
		size--;
	} else if (n->right == sentinel) {
		if (n == parent->left) {
			parent->left = n->left;
		} else {
			parent->right = n->left;
		}
		n->left->parent = parent;
		delete n;
		size--;
	} else {
		for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
		tmpkey = mlc->key;
		tmpval = mlc->val;
		Delete(tmpkey);
		n->key = tmpkey;
		n->val = tmpval;
	}
	return 1;
}

vector <void *>BSTree::Sorted_Vector()
{
	array.clear();
	recursive_make_vector(sentinel->right);
	return array;
}

void BSTree::Print()
{
	recursive_inorder_print(0, sentinel->right);
}

int BSTree::Size()
{
	return size;
}

int BSTree::Empty()
{
	return (size == 0);
}

void BSTree::recursive_inorder_print(int level, BSTNode *n)
{
	if (n == sentinel) return;
	recursive_inorder_print(level+2, n->right);
	printf("%*s%s\n", level, "", n->key.c_str());
	recursive_inorder_print(level+2, n->left);
}

void BSTree::recursive_make_vector(BSTNode *n)
{
	if (n == sentinel) return;
	recursive_make_vector(n->left);
	array.push_back(n->val);
	recursive_make_vector(n->right);
}

void BSTree::recursive_destroy(BSTNode *n)
{
	if (n == sentinel) return;
	recursive_destroy(n->left);
	recursive_destroy(n->right);
	delete n;
}
