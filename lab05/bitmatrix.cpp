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

// This constructor builds an empty bitmatrix for us to start from
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

// This returns the number of rows in our bitmatrix
int Bitmatrix::Rows()
{
	return M.size();
}

// This returns the number of columnss in our bitmatrix
int Bitmatrix::Cols()
{
	return M[0].size();
}

// This method sets a specific bitmatrix entry to the desired value
void Bitmatrix::Set(int row, int col, char val)
{
	if (row < 0 || col < 0) return;
	M[row][col] = val;
}

// This method retrieves a value from the bitmatrix
char Bitmatrix::Val(int row, int col)
{
	if (row < 0 || col < 0) return -1;
	return (M[row][col] - 48);
}

// This method was given to us, and prints the entire bitmatrix
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

// This method writes the entire bitmatrix to a file
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

// This method swaps the given rows' entries 1 for 1
void Bitmatrix::Swap_Rows(int r1, int r2)
{
	if (r1 < 0 || r2 < 0) return;
	int tmp;
	for (int i = 0; i < M[0].size(); i++) {
		tmp = M[r1][i];
		M[r1][i] = M[r2][i];
		M[r2][i] = tmp;
	}
}

// This method effectively XOR's the two given rows, and sets
// the results to the first given row
void Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
	int tmp;
	if (r1 < 0 || r2 < 0) return;
	for (int i = 0; i < M[r1].size(); i++) {
		if((M[r1][i] == '0' && M[r2][i] == '0') || (M[r1][i] == '1' && M[r2][i] == '1'))
			M[r1][i] = '0';
		else M[r1][i] = '1';
	}
}

// This was given to us, and reads a given file to create a bitmatrix
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

// This method prints a PGM of the bitmatrix, and makes it all pretty-like
void Bitmatrix::PGM(string fn, int pixels, int border)
{
}

Bitmatrix *Bitmatrix::Copy()
{
	return NULL;
}


BM_Hash::BM_Hash(int size)
{
	table.resize(size);
}

// This stores a bitmatrix in a hash table with the given key,
// or updates a hash entry if the key already exists
void BM_Hash::Store(string &key, Bitmatrix *bm)
{
	bool update = false;
	vector<HTE *> temp;
	HTE hash;
	hash.key = key;
	hash.bm = bm;

	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			if (table[i][j]->key == key) {
				table[i][j]->bm = bm;
				update = true;
			}
		}
	}
	if (update == false) {
		table.push_back(temp);
	}
}

// This retrieves a bitmatrix from the hashtable, if the key exists
Bitmatrix *BM_Hash::Recall(string &key)
{
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			if (table[i][j]->key == key) return table[i][j]->bm;
		}
	}
	return NULL;
}

// This prints all of the hashtable bitmatrixes that are currently stored
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
