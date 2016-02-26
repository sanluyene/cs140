// CS140 Spring 2016
// Lab 05: Playing with bit matricies
// Part 1: 1-28 and 101-120 (2/24)
// Part 2: Remainder (3/2)
// Author: Ashley Sattler
// Date: 02/24/2016

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include "bitmatrix.h"

using namespace std;

// This is our hash function, our collision resolution is separate chaining
unsigned int djb_hash(string &s)
{
	int i;
	unsigned int h;

	h = 5381;

	for (i = 0; i < s.size(); i++) {
		h = (h << 5) + h + s[i];
	}
	return h;
}

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
// We are only using 0's and 1's
void Bitmatrix::Set(int row, int col, char val)
{
	if (row < 0 || col < 0) return;
	M[row][col] = val;
}

// This method retrieves a specific value from the bitmatrix
char Bitmatrix::Val(int row, int col)
{
	if (row < 0 || col < 0) return -1;
	return (M[row][col] - '0');
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
			fout << (M[i][j] - '0');
		}
		fout << "\n";
	}
	fout.close();
}

// This method will swap all entries in the two specified rows
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

// This method effectively XOR's the values from two given rows
// and sets the results to the first given row
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

// This method was given to us, and reads a given file to create a bitmatrix
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
	ofstream fout;
	FILE * pgm;
	int rows = 0, cols = 0, newrows = 0, newcols = 0;

	rows = M.size();
	cols = M[0].size();
	// We need to account for the size of the border
	newrows = (rows * pixels) + ((rows + 1) * border);
	newcols = (cols * pixels) + ((cols + 1) * border);

	pgm = fopen(fn.c_str(), "w");

	// Print the required non-pixel values for the PGM file
	fprintf(pgm, "P2\n%d %d\n255\n", newcols, newrows);

	// Print the beginning border rows
	for (int i = 0; i < border; i++) {
		for (int j = 0; j < newcols; j++) {
			fprintf(pgm, "0 ");
		}
		fprintf(pgm, "\n");
	}

	for (int i = 0; i < rows; i++) {
		for (int r = 0; r < pixels; r++) {
			for (int j = 0; j < cols; j++) {
				// The border before the pixel
				for (int b = 0; b < border; b++) {
					fprintf(pgm, "0 ");
				}
				for (int k = 0; k < pixels; k++) {
					// The actual pixel
					if (M[i][j] == '0') fprintf(pgm, "255 ");
					else fprintf(pgm, "100 ");
				}
			}
			// The border at the end of the column
			for (int b = 0; b < border; b++) {
				fprintf(pgm, "0 ");
			}
			fprintf(pgm, "\n");
		}
		// Print the border inbetween rows and at the end
		for (int i = 0; i < border; i++) {
			for (int j = 0; j < newcols; j++) {
				fprintf(pgm, "0 ");
			}
			fprintf(pgm, "\n");
		}
	}

	fclose(pgm);
}

// This method copies an entire bitmatrix into a new bitmatrix
Bitmatrix *Bitmatrix::Copy()
{
	Bitmatrix *bm;
	bm = new Bitmatrix(M.size(), M[0].size());

	for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[i].size(); j++) {
			bm->Set(i, j, M[i][j]);
		}
	}

	return bm;
}

// This is a constructor for a new bitmatrix hash table
// The size corresponds to the number of hash rows available
// We will use separate chaining as our collision resolution
BM_Hash::BM_Hash(int size)
{
	table.resize(size);
}

// This stores a bitmatrix in a hash table with the given key,
// or updates a hash entry if the key already exists
void BM_Hash::Store(string &key, Bitmatrix *bm)
{
	bool update = false;
	int hash;
	HTE *entry;

	hash = djb_hash(key) % table.size();

	for (int j = 0; j < table[hash].size(); j++) {
		if (table[hash][j]->key == key) {
			// The entry already exists
			table[hash][j]->bm = bm;
			update = true;
		}
	}

	// The entry does not exist
	if (update == false) {
		entry = new HTE;
		entry->key = key;
		entry->bm = bm;

		table[hash].push_back(entry);
	}
}

// This retrieves a bitmatrix from the hashtable, if the key exists
Bitmatrix *BM_Hash::Recall(string &key)
{
	int hash;

	hash = djb_hash(key) % table.size();

	for (int j = 0; j < table[hash].size(); j++) {
		if (table[hash][j]->key == key) return table[hash][j]->bm;
	}

	return NULL;
}

// This prints all of the hashtable bitmatrixes that are currently stored
HTVec BM_Hash::All()
{
	HTVec rv;
	int rows, cols;

	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			rows = table[i][j]->bm->Rows();
			cols = table[i][j]->bm->Cols();
			printf("%-31s %2d X  %2d\n", table[i][j]->key.c_str(), rows, cols);
		}
	}

	return rv;
}

// This method will add two matricies together
Bitmatrix *Sum(Bitmatrix *m1, Bitmatrix *m2)
{
	Bitmatrix *bm;
	char m1val, m2val, newval;
	int m1rows = 0, m1cols = 0, m2rows = 0, m2cols = 0;

	// We need the given bitmatricies' information
	m1rows = m1->Rows(); m1cols = m1->Cols();
	m2rows = m2->Rows(); m2cols = m2->Cols();

	// If they are not equal in size, then the summation will not work
	if (m1rows != m2rows || m1cols != m2cols) return NULL;

	bm = new Bitmatrix(m1rows, m1cols);
	for (int r = 0; r < m1rows; r++) {
		for (int c = 0; c < m1cols; c++) {
			m1val = m1->Val(r, c) + '0'; m2val = m2->Val(r, c) + '0';
			newval = (((m1val - '0') + (m2val - '0')) % 2) + '0';
			bm->Set(r, c, newval);
		}
	}

	return bm;
}

// This method will multiply two matricies together
Bitmatrix *Product(Bitmatrix *m1, Bitmatrix *m2)
{
	Bitmatrix *bm;
	char m1val, m2val, newval;
	int m1rows = 0, m1cols = 0, m2rows = 0, m2cols = 0, total = 0;
	// Iterators
	int c = 0, r = 0, c1 = 0;

	// We need the given bitmatricies' information
	m1rows = m1->Rows(); m1cols = m1->Cols();
	m2rows = m2->Rows(); m2cols = m2->Cols();

	// If the first's rows and second's columns are not equal,
	// then the product will not work properly
	if (m1cols != m2rows) return NULL;

	bm = new Bitmatrix(m1rows, m2cols);
	for (r = 0; r < m1rows; r++) {
		for (c = 0; c < m2cols; c++) {
			for (c1 = 0; c1 < m1cols; c1++) {
				m1val = m1->Val(r, c1) + '0';
				m2val = m2->Val(c1, c) + '0';
				total += (m1val - '0') * (m2val - '0');
			}
			newval = (total % 2) + '0';
			bm->Set(r, c, newval);
			total = 0;
		}
	}

	return bm;
}

// This method will create a new matrix from part of an existing matrix
Bitmatrix *Sub_Matrix(Bitmatrix *m, vector <int> &rows)
{
	Bitmatrix *bm;
	char mval;
	int mrows = 0, mcols = 0;

	// We need the given bitmatrix's information
	mrows = m->Rows(); mcols = m->Cols();

	// If we ask for more rows than exist in the bitmatrix, or no rows
	// then this method will not work
	if (rows.size() > mrows || rows.size() <= 0) return NULL;

	bm = new Bitmatrix(rows.size(), mcols);
	for (int r = 0; r < rows.size(); r++) {
		for (int c = 0; c < mcols; c++) {
			mval = m->Val(rows[r], c) + '0';
			bm->Set(r, c, mval);
		}
	}

	return bm;
}

// This method will generate the inverse of an existing matrix
Bitmatrix *Inverse(Bitmatrix *m)
{
	Bitmatrix *bm;
	char mval;
	int mrows = 0, mcols = 0;
	bool inverse = false;

	// We need the given bitmatrix's information
	mrows = m->Rows(); mcols = m->Cols();

	// If the bitmatrix is not square, it will not have an inverse
	if (mrows != mcols) return NULL;

	// We will begin by making the new bitmatrix the identity matrix
	bm = new Bitmatrix(mrows, mcols);
	for (int r = 0; r < mrows; r++) {
		for (int c = 0; c < mcols; c++) {
			if (r == c) bm->Set(r, c, '1');
		}
	}

	// All changes will be performed on both the existing matrix
	// and the new matrix in order to find the inverse, if it exists
	for (int i = 0; i < mrows; i++) {
		mval = m->Val(i, i) + '0';
		if (mval != '1') {
	//			inverse = false;
			for (int j = i+1; j < mrows; j++) {
				mval = m->Val(j, i) + '0';
				if (mval == '1') {
					m->Swap_Rows(i, j);
					bm->Swap_Rows(i, j);
	//					inverse = true;
					break;
				}
			}
			// If we couldn't find a proper row, the inverse does not exist
	//			if (inverse == false) return NULL;
		}

		// Now, look at every row j such that j > i. If M[j][i] equals one,
		// then set row j equal to the sum of rows i and j.
		for (int j = i+1; j < mrows; j++) {
			mval = m->Val(j, i);
			if (mval == '1') {
				m->R1_Plus_Equals_R2(j, i);
				bm->R1_Plus_Equals_R2(j, i);
			}
		}
	}

	// If there is any j > i where M[i][j] equals one, replace row
	// i with the sum of row i and row j.
	for (int i = mrows-1; i >= 0; i--) {
		for (int j = i+1; j < mcols; j++) {
			mval = m->Val(i, j) + '0';
			if (mval == '1') {
cout << "i: " << i << " j: " << j << endl;
				m->R1_Plus_Equals_R2(i, j);
				bm->R1_Plus_Equals_R2(i, j);
			}
		}
	}

	return bm;
}
