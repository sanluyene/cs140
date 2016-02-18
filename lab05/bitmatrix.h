#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Bitmatrix {
  public:
    Bitmatrix(int rows, int cols);   // Create an empty bitmatrix
    Bitmatrix(string fn);            // Read from a file
    void Write(string fn);           // Write t to a file either as hex or zeros & ones
    void Print(int w);               // Print on standard ouptput with spaces & blank lines 
    void PGM(string fn, int pixels, int border);  // Write it to a pgm file 
    int Rows();                           // Return the number of rows
    int Cols();                           // Return the number of columns
    void Set(int row, int col, char val); // Set the specified element to val
    char Val(int row, int col);           // Return the specified element
    void Swap_Rows(int r1, int r2);       
    void R1_Plus_Equals_R2(int r1, int r2);
    Bitmatrix *Copy();
  protected:
    vector <string> M; // The matrix.  Elements are '0' or '1'.
};

Bitmatrix *Sum(Bitmatrix *a1, Bitmatrix *a2);
Bitmatrix *Product(Bitmatrix *a1, Bitmatrix *a2);
Bitmatrix *Sub_Matrix(Bitmatrix *a1, vector <int> &rows);
Bitmatrix *Inverse(Bitmatrix *m);

class HTE {
  public:
    string key;
    Bitmatrix *bm;
};

typedef vector <HTE *> HTVec;

class BM_Hash {
  public:
    BM_Hash(int size);
    void Store(string &key, Bitmatrix *bm);
    Bitmatrix *Recall(string &key);
    HTVec All();
  protected:
    vector <HTVec> table;
};
