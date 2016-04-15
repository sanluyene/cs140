// CS140 Spring 2016
// Lab 10: Binary Search Tree Playtime
// Author: Ashley Sattler
// Date: 04/15/2016

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "laba.h"

using namespace std;

// These methos are the new ones we implement for this lab
void Postorder() {

}

void Preorder() {

}

int Depth(string key) {
  return 0;
}

int Height() {
  return 0;
}

int IsAVL() {
  return 0;
}

int Rotate(string key) {
  return 0;
}

void recursive_preorder(int level, BSTNode *n) {

}

void recursive_postorder(int level, BSTNode *n) {

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