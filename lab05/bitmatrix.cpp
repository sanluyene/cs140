// CS140 Spring 2016
// Lab 05: Playing with bit matricies
// Author: Ashley Sattler
// Date: 02/19/2016

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.h"

using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols)
{
	if (rows <= 0 || cols <= 0) {
		fprintf(stderr, "Bad matrix file\n");
		M.resize(1); M[0].resize(1), M[0][0] = '0';
	}
	else {
		M.resize(rows);
		for (int i = 0; i < rows; i++) {
			M[i].resize(cols, '0');
		}
	}
}

int Bitmatrix::Rows()
{
	return M.size();
}

int Bitmatrix::Cols()
{
	return M[0].size();
}

void Bitmatrix::Set(int row, int col, char val)
{
	if (row < 0 || col < 0) return;
	M[row][col] = val;
}

char Bitmatrix::Val(int row, int col)
{
	if (row < 0 || col < 0) return -1;
	return (M[row][col] - 48);
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
	ofstream fout;
	fout.open(fn.c_str());

	for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[i].size(); j++) {
			fout << (M[i][j] - 48);
		}
		fout << "\n";
	}
	fout.close();
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
