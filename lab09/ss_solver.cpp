// CS140 Spring 2016
// Lab 09: ShapeShifter Solver
// Author: Ashley Sattler
// Date: 04/12/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <vector>
#include "ss_solver.h"

using namespace std;

// This is our constructor for building our grid and piece set
ShapeShifter::ShapeShifter(vector<string> g, vector<vector<string> > p) {
	grid = g;
	pieces = p;
}

// This function will apply a piece at a given row and column.
// If called twice with the same variables, it reverts the grid
// back to its original state.
bool ShapeShifter::Apply(int piece, int row, int column) {
	for (int rp = 0; rp < pieces[piece].size(); rp++) {
		for (int cp = 0; cp < pieces[piece][rp].length(); cp++) {
			if (pieces[piece][rp][cp] == '1') {
				// If the piece row or column are beyond the bounds of the grid
				// the piece will not fit
				if (((rp + row) >= grid.size()) || ((cp + column) >= grid[0].length())) return false;

				// Otherwise, change the grid value
				if (grid[rp + row][cp + column] == '1') grid[rp + row][cp + column] = '0';
				else grid[rp + row][cp + column] = '1';
			}
		}
	}

	return true;
}

// This is our recursive function. We will continue to call
// this function until a solution has or has not been found
void ShapeShifter::find_solution(int index) {
	bool win = true, insert = false;

	// Base case
	if (index == pieces.size()) {
		// Test to see if the grid is all 1's for a win
		for (int r = 0; r < grid.size(); r++) {
			for (int c = 0; c < grid[0].length(); c++) {
				if (grid[r][c] == '0') win = false;
				break;
			}
		}
	
		if (win == true) {
			printf("winning\n");
			exit(0);
		}
		return;		
	}

	// Place the piece
	for (int r = 0; r < grid.size(); r++) {
		for (int c = 0; c < grid[0].length(); c++) {
			insert = Apply(index, r, c);
			if (insert) find_solution(index + 1);

			// If a future piece doesn't work, undo this piece's placement
			Apply(index, r, c);
		}
	}

	return;
}

int main(int argc, char **argv) {
	ShapeShifter *shifter;
	vector<string> g;
	vector<vector<string> > p;
	istringstream ss;
	string s;
	int numpieces = 0;

	for (int i = 1; i <= 3; i++) {
		g.push_back(argv[i]);
	}

	while (getline(cin, s)) {
		ss.clear();
		ss.str(s);
		numpieces++;
		p.resize(numpieces);

		while (ss >> s) {
			p[numpieces-1].push_back(s);
		}
	}

	shifter = new ShapeShifter(g, p);
	shifter->find_solution(0);

	return 0;
}
