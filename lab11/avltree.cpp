// CS140 Spring 2016
// Lab 11: AVL Tree Playtime
// Author: Ashley Sattler
// Date: 04/22/2016

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "avltree.h"

using namespace std;

AVLTree::AVLTree() {
    sentinel = new AVLTNode;
    sentinel->parent = NULL;
    sentinel->left = NULL;
    sentinel->right = sentinel;
    size = 0;
}

AVLTree::~AVLTree() {
    recursive_destroy(sentinel->right);
    delete sentinel;
}

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
    return 1;
}

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

void AVLTree::Print() {
    recursive_inorder_print(0, sentinel->right);
}

int AVLTree::Size() {
    return size;
}

int AVLTree::Empty() {
    return (size == 0);
}

vector <void *> AVLTree::Sorted_Vector() {
    array.clear();
    recursive_make_vector(sentinel->right);
    return array;
}

void AVLTree::Check_Balance(AVLTNode *n) {
//    if (Empty()) return;

    return;
}

AVLTNode *AVLTree::Rebalance(AVLTNode *n) {
    AVLTNode *a;
    a = new AVLTNode;
    return a;
}

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

    return;
}

void AVLTree::recursive_inorder_print(int level, AVLTNode *n) {
    if (n == sentinel) return;
    recursive_inorder_print(level+2, n->right);
    printf("%*s%s\n", level, "", n->key.c_str());
    recursive_inorder_print(level+2, n->left);
}

void AVLTree::recursive_make_vector(AVLTNode *n) {
    if (n == sentinel) return;
    recursive_make_vector(n->left);
    array.push_back(n->val);
    recursive_make_vector(n->right);
}

void AVLTree::recursive_destroy(AVLTNode *n) {
    if (n == sentinel) return;
    recursive_destroy(n->left);
    recursive_destroy(n->right);
    delete n;
}
