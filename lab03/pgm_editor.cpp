// CS140 Spring 2016
// Lab 03: Creating, editing, and manipulating PGM files 
// Author: Ashley Sattler
// Date: 02/09/2016

#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

typedef vector <int> IVec;

// Write your code here:

void pgm_write(vector <IVec> &p) {
	// This writes a PGM file
	// We will keep track of the number of printed pixels in order to maintain
	// the required formatting
	int numPixel = 0;

	// Print the required non-pixel values for the PGM file
	printf("P2\n%d %d\n255\n", p[0].size(), p.size());
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
	if (numPixel != 0) printf("\n");
}

vector <IVec> pgm_create(int r, int c, int pv) {
	// This will create a new PGM file pixel vector
	vector <IVec> newp;

	newp.resize(r, vector<int>(c, pv));

	return newp;
}

void pgm_cw(vector <IVec> &p) {
	// This will rotate the PGM file 90 degrees clockwise
	vector <IVec> newp;
	IVec temp;
	int rows = p.size(), columns = p[0].size();
	
	// Number of rows and columns flip flop
	newp.resize(columns, vector<int>());
	for (int c = 0; c < columns; c++) {
		for (int r = (rows - 1); r >= 0; r--) {
			newp[c].push_back(p[r][c]);
		}
	}

	p = newp;
}

void pgm_ccw(vector <IVec> &p) {
	// This will rotate the PGM file 90 degrees counter-clockwise
	vector <IVec> newp;
	int rows = p.size(), columns = p[0].size();
	int newr = 0;
	
	// Number of rows and columns flip flop
	newp.resize(columns, vector<int>());
	for (int c = (columns - 1); c >= 0; c--) {
		for (int r = 0; r < rows; r++) {
			newp[newr].push_back(p[r][c]);
		}
		newr++;
	}

	p = newp;
}

void pgm_pad(vector <IVec> &p, int w, int pv) {
	// This will add a border of w pixels to the PGM file
	vector <IVec> newp;
	int rows = p.size(), columns = p[0].size();
	int newrows = rows + (2 * w), newcolumns = columns + (2 * w);

	// First we need to fill the new vector of vectors with the pad colour
	newp.resize(newrows, vector<int>());
	for (int i = 0; i < newrows; i++) {
		for (int j = 0; j < newcolumns; j++) {
			newp[i].push_back(pv);
		}
	}

	// Then replace the pixels with the original image
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			newp[r+w][c+w] = p[r][c];
		}
	}

	//for (int r = 0; r < (newrows); r++) {
	//	for (int c = 0; c < (newcolumns); c++) {
	//		if (r <= w || c <= w || r >= rows || c >= columns) newp[r].push_back(pv);
	//		else newp[r].push_back(p[r-w][c-w]);
	//	}
	//}

	p = newp; 
}

void pgm_panel(vector <IVec> &p, int r, int c) {
	// This will multiply the PGM file into a grid of PGM files
	vector <IVec> newp;
	int rows = p.size(), columns = p[0].size();

	// We need to loop through the entire PGM file rxc times
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			// We need to loop through all of the pixels in the PGM file
			for (int pi = 0; pi < p.size(); pi++) {
				for (int pj = 0; pj < p[pi].size(); pj++) {
					newp[i].push_back(p[pi][pj]);
				}
			}
		}
	}

	p = newp;
}

void pgm_crop(vector <IVec> &p, int r, int c, int rows, int cols) {
	// This will crop the PGM file
	vector <IVec> newp;
	int row = 0;

	for (int i = r; i < (r + rows); i++) {
		for (int j = c; j < (c + cols); j++) {
			newp[r].push_back(p[i][j]);
		}

		row++;
	}

	p = newp;
}

// DO NOT CHANGE ANYTHING BELOW THIS LINE

void bad_pgm(string s)
{
  cerr << "Bad PGM file: " << s << endl;
  exit(1);

}

vector <IVec> pgm_read()
{
  string s;
  int r, c, i, j, v;
  vector <IVec> p;

  if (!(cin >> s)) bad_pgm("Empty file.");
  if (s != "P2") bad_pgm("First word is not P2.");
  if (!(cin >> c) || c <= 0) bad_pgm("Bad column spec.");
  if (!(cin >> r) || r <= 0) bad_pgm("Bad column spec.");
  if (!(cin >> i) || i != 255) bad_pgm("Bad spec of 255.");
  p.resize(r);
  for (i = 0; i < r; i++) for (j = 0; j < c; j++) {
    if (!(cin >> v) || v < 0 || v > 255) bad_pgm("Bad pixel.");
    p[i].push_back(v);
  }
  if (cin >> s) bad_pgm("Extra stuff at the end of the file.");
  return p;
}

void usage()
{
  cerr << "usage: pgm_editor command....\n\n";
  cerr << "        CREATE rows cols pixvalue\n";
  cerr << "        CW\n";
  cerr << "        CCW\n";
  cerr << "        PAD pixels pixvalue\n";
  cerr << "        PANEL r c\n";
  cerr << "        CROP r c rows cols\n";
  exit(1);
}

main(int argc, char **argv)
{
  istringstream ss;
  int r, c, i, j, p, w, rows, cols;
  vector <IVec> pgmf;
  string a1;

  if (argc < 2) usage();
  a1 = argv[1];

  if (a1 == "CREATE") {
    if (argc != 5) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c <= 0) usage();
    ss.clear(); ss.str(argv[4]); if (!(ss >> p) || p < 0 || p > 255) usage();
    pgmf = pgm_create(r, c, p);
  } else if (a1 == "PAD") {
    if (argc != 4) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> w) || w <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> p) || p < 0 || p > 255) usage();
    pgmf = pgm_read();
    pgm_pad(pgmf, w, p);
  } else if (a1 == "CCW") {
    if (argc != 2) usage();
    pgmf = pgm_read();
    pgm_ccw(pgmf);
  } else if (a1 == "CW") {
    if (argc != 2) usage();
    pgmf = pgm_read();
    pgm_cw(pgmf);
  } else if (a1 == "PANEL") {
    if (argc != 4) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c <= 0) usage();
    pgmf = pgm_read();
    pgm_panel(pgmf, r, c);
  } else if (a1 == "CROP") {
    if (argc != 6) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r < 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c < 0) usage();
    ss.clear(); ss.str(argv[4]); if (!(ss >> rows) || rows <= 0) usage();
    ss.clear(); ss.str(argv[5]); if (!(ss >> cols) || cols <= 0) usage();
    pgmf = pgm_read();
    if (r + rows > pgmf.size() || c + cols > pgmf[0].size()) {
      fprintf(stderr, "CROP - Bad params for the pictures size (r=%d, c=%d)\n",
           (int) pgmf.size(), (int) pgmf[0].size());
      exit(1);
    }
    pgm_crop(pgmf, r, c, rows, cols);
  } else {
    usage();
  }
  pgm_write(pgmf);
}
