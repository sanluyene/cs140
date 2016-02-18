#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.h"

Bitmatrix::Bitmatrix(int rows, int cols)
{
}

int Bitmatrix::Rows()
{
  return 0;
}

int Bitmatrix::Cols()
{
  return 0;
}

void Bitmatrix::Set(int row, int col, char val)
{
}
  
char Bitmatrix::Val(int row, int col)
{
  return -1;
}
  
void Bitmatrix::Print(int w) 
{
  int i, j;

  for (i = 0; i < M.size(); i++) {
    if (w > 0 && i != 0 && i%w == 0) printf("\n");
    if (w <= 0) {
      cout << M[i] << endl;
    } else {
      for (j = 0; j < M[i].size(); j++) {
        if (j % w == 0 && j != 0) printf(" ");
        printf("%c", M[i][j]);
      }
      cout << endl;
    }
  }
}

void Bitmatrix::Write(string fn) 
{
}

void Bitmatrix::Swap_Rows(int r1, int r2)
{
}

void Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
}

Bitmatrix::Bitmatrix(string fn) 
{
  ifstream f;
  int i, j;
  string s, row;

  f.open(fn.c_str());
  if (f.fail()) { perror(fn.c_str()); M.resize(1); M[0].resize(1), M[0][0] = '0'; return; }

  while (getline(f, s)) {
    row.clear();
    for (i = 0; i < s.size(); i++) {
      if (s[i] == '0' || s[i] == '1') {
        row.push_back(s[i]);
      } else if (s[i] != ' ') {
        fprintf(stderr, "Bad matrix file %s\n", fn.c_str());
        M.resize(1); M[0].resize(1), M[0][0] = '0'; 
        f.close();
        return;
      }
    }
    if (s.size() > 0 && M.size() > 0 && row.size() != M[0].size()) {
      fprintf(stderr, "Bad matrix file %s\n", fn.c_str());
      M.resize(1); M[0].resize(1), M[0][0] = '0'; 
      f.close();
      return;
    }
    if (s.size() > 0) M.push_back(row);   
  }
  f.close();
}

void Bitmatrix::PGM(string fn, int pixels, int border)
{
}

Bitmatrix *Bitmatrix::Copy()
{
  return NULL;
}


BM_Hash::BM_Hash(int size)
{
}

void BM_Hash::Store(string &key, Bitmatrix *bm)
{
}
  
Bitmatrix *BM_Hash::Recall(string &key)
{
  return NULL;
}
  
HTVec BM_Hash::All()
{
  HTVec rv;
  return rv;
}


Bitmatrix *Sum(Bitmatrix *m1, Bitmatrix *m2)
{
  return NULL;
}

Bitmatrix *Product(Bitmatrix *m1, Bitmatrix *m2)
{
  return NULL;
}

Bitmatrix *Sub_Matrix(Bitmatrix *m, vector <int> &rows)
{
  return NULL;
}

Bitmatrix *Inverse(Bitmatrix *m)
{
  return NULL;
}
