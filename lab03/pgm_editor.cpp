// CS140 Spring 2016
// Lab 03: 
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

void pgm_write(IVec &p);
void pgm_create(int r, int c, int pv);
void pgm_cw(IVec &p);
void pgm_ccw(IVec &p);
void pgm_pad(IVec &p, int w, int pv);
void pgm_panel(IVec &p, int r, int c);
void pgm_crop(IVec &p, int r, int c, int rows, int cols);

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

  p = newp;
}

void pgm_ccw(IVec &p) {
  // This will rotate the PGM file 90 degrees counter-clockwise
  IVec newp;

  for (int c = (p[0].size() - 1); c >= 0; c--) {
    for (int r = 0; r < p.size(); r++) {
      if (c < p[r].size()) newp.push_back(p[r][c]);
    }
  }

  p = newp;
}

void pgm_pad(IVec &p, int w, int pv) {
  // This will add a border of w pixels to the PGM file
  IVec newp;

  // The border needs to be added on the top, bottom, and both sides of the PGM file
  for (int r = 0; r < (p.size() + w); r++) {
    for (int c = 0; c < (p[r].size() + w); c++) {
        if (r < w || c < w || r > (p.size() - 1) || c > (p[r].size() - 1)) newp.push_back(pv);
        else newp.push_back(p[r-w][c-w]);
    }
  }

  p = newp; 
}

void pgm_panel(IVec &p, int r, int c) {
  // This will multiply the PGM file into a grid of PGM files
  IVec newp;

  // We need to loop through the entire PGM file rxc times
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      // We need to loop through all of the pixels in the PGM file
      for (int pi = 0; pi < p.size(); pi++) {
        for (int pj = 0; pj < p[pi].size(); pj++) {
          newp.push_back(p);
        }
      }
    }
  }

  p = newp;
}

void pgm_crop(IVec &p, int r, int c, int rows, int cols) {
  // This will crop the PGM file
  IVec newp;

  for (int i = r; i < (r + rows); i++) {
    for (int j = c; j < (c + cols); j++) {
      newp.push_back(p[i][j]);
    }
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
