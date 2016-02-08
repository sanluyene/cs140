// CS140 Spring 2016
// Lab 03: 
// Author: Ashley Sattler
// Date: 02/04/2016

#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

void pgm_write(IVec &p);
void pgm_create(int r, int c, int pv);
void pgm_cw(IVec &p);
void pgm_ccw(IVec &p);
void pgm_pad(IVec &p, int w, int pv);
void pgm_panel(IVec &p, int r, int c);
void pgm_crop(IVec &p, int r, int c, int rows, int cols);

typedef vector <int> IVec;

// Write your code here:

int main() {
	vector <IVec> p;
	string input;
	int r = 0, c = 0, w = 0, rows = 0, columns = 0;

	cin >> input;

	if (input == "CREATE") {
		cin >> r >> c;
		pgm_create(r, c, pv);
	}
	else if (input == "CW") pgm_cw(&p);
	else if (input == "CCW") pgm_ccw(&p);
	else if (input == "PAD") {
		cin >> w >> pv;
		pgm_pad(&p, w, pv)
	}
	else if (input == "PANEL") {
		cin >> r >> c;
		pgm_panel(&p, r, c);
	}
	else if (input == "CROP") {
		cin >> r >> c >> rows >> columns;
		pgm_crop(&p, r, c, rows, cols)
	}
	else {
		// The program errors
		printf("usage: pgm_editor command....\n\n");
        printf("        CREATE rows cols pixvalue\n");
        printf("        CW\n");
        printf("        CCW\n");
        printf("        PAD pixels pixvalue\n");
        printf("        PANEL r c\n");
        printf("        CROP r c rows cols\n");
        return -1;
	}

	return 0;
}

void pgm_write(IVec &p) {
	// This writes a PGM file
	// We will keep track of the number of printed pixels in order to maintain
	// the required formatting
	int numPixel = 0;

	// Print the required non-pixel values for the PGM file
	printf("P2\n%d %d\n255\n", p.size(), p[0].size());
	// Then print the pizels
	for (int r = 0; r < p.size(); r++) {
		for (int c = 0; c < p[r].size(); c++) {
			printf("%4d", p[r][c]);
			numPixel++;
			if (numPixel == 20) {
				printf("\n");
				numPixel = 0;
			}
		}
	}
}

void pgm_create(int r, int c, int pv) {
	// This will create a PGM file rxc with pixels of the pv value
	// We will keep track of the number of printed pixels in order to maintain
	// the required formatting
	int numPixel = 0;

	// Print the required non-pixel values for the PGM file
	printf("P2\n%d %d\n255\n", r, c);
	// Then print the pizels
	for (int rows = 0; rows < r; rows++) {
		for (int columns = 0; columns < c; columns++) {
			printf("%4d", pv);
			numPixel++;
			if (numPixel == 20) {
				printf("\n");
				numPixel = 0;
			}
		}
	}

}

void pgm_cw(IVec &p) {
	// This will rotate the PGM file 90 degrees clockwise
	IVec newp;

	for (int c = 0; c < p[0].size(); c++) {
		for (int r = (p.size() - 1); r >= 0; r--) {
			if (c < p[r].size()) newp.push_back(p[r][c]);
		}
	}

	pgm_write(&newp);
}

void pgm_ccw(IVec &p) {
	// This will rotate the PGM file 90 degrees counter-clockwise
	IVec newp;

	for (int c = (p[0].size() - 1); c >= 0; c--) {
		for (int r = 0; r < p.size(); r++) {
			if (c < p[r].size()) newp.push_back(p[r][c]);
		}
	}

	pgm_write(&newp);
}

void pgm_pad(IVec &p, int w, int pv) {
	// This will add a border of w pixels to the PGM file
	IVec newp;

	pgm_write(&newp);
}

void pgm_panel(IVec &p, int r, int c) {
	// This will multiply the PGM file into a grid of PGM files
	IVec newp;

	pgm_write(&newp);
}

void pgm_crop(IVec &p, int r, int c, int rows, int cols) {
	// This will crop the PGM file
	IVec newp;

	pgm_write(&newp);
}

// DO NOT CHANGE ANYTHING BELOW THIS LINE

void bad_pgm(string s)
{
  cerr << "Bad PGM file: " << s << endl;
  exit(1);

}