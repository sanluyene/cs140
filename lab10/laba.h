#include <iostream>
#include <vector>
using namespace std;

class BSTNode {
  public:
    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;
    string key;
    void *val;
};

class BSTree {
  public:
    BSTree();
    ~BSTree();
    int Insert(string key, void *val);
    void *Find(string key);
    int Delete(string key);
    void Print();
    int Size();
    int Empty();
    vector <void *> Sorted_Vector();

    void Postorder();  // These are the new methods you need to implement
    void Preorder();
    int Depth(string key);
    int Height();
    int IsAVL();
    int Rotate(string key);
  protected:
    BSTNode *sentinel;
    int size;
    vector <void *> array;
   
    void recursive_preorder(int level, BSTNode *n);
    void recursive_postorder(int level, BSTNode *n);
    void recursive_inorder_print(int level, BSTNode *n);
    void recursive_make_vector(BSTNode *n);
    void recursive_destroy(BSTNode *n);
    int recursive_height(BSTNode *n);
    int recursive_height_and_avl_check(BSTNode *n);

};
