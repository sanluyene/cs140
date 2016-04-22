#include <iostream>
#include <vector>
using namespace std;

class AVLTNode {
  public:
    AVLTNode *left;
    AVLTNode *right;
    AVLTNode *parent;
    int height;
    string key;
    void *val;
};

class AVLTree {
  public:
    AVLTree();
    ~AVLTree();
    int Insert(string key, void *val);
    void *Find(string key);
    int Delete(string key);
    void Print();
    int Size();
    int Empty();
    vector <void *> Sorted_Vector();
  protected:
    AVLTNode *sentinel;
    int size;
    vector <void *> array;

    void Check_Balance(AVLTNode *n);
    AVLTNode *Rebalance(AVLTNode *n);
    void Rotate(AVLTNode *n);
   
    void recursive_inorder_print(int level, AVLTNode *n);
    void recursive_make_vector(AVLTNode *n);
    void recursive_destroy(AVLTNode *n);

};
