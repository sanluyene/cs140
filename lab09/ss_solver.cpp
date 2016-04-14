// CS140 Spring 2016
// Lab 09: ShapeShifter Solver
// Author: Ashley Sattler
// Date: 04/12/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <vector>
#include <string>
#include "ss_solver.h"

using namespace std;

// This is our constructor for building our grid and piece set
ShapeShifter::ShapeShifter(vector<string> g, vector<vector<string> > p) {
	grid = g;
	pieces = p;
	moves.resize(pieces.size());

	// Our moves vector will hold a reference to each of the pieces
	// for proper move printing
	for (int p = 0; p < moves.size(); p++) {
		moves[p].push_back(p);
		moves[p].push_back(0);
		moves[p].push_back(0);
	}
}

// This function will apply a piece at a given row and column.
// If called twice with the same variables, it reverts the grid
// back to its original state.
bool ShapeShifter::Apply(int piece, int row, int column) {
	int piecepart = 0;

	for (int rp = 0; rp < pieces[piece].size(); rp++) {
		for (int cp = 0; cp < pieces[piece][rp].length(); cp++) {
			// If the piece row or column are beyond the bounds of the grid
			// the piece will not fit
			if (((rp + row) < grid.size()) && ((cp + column) < grid[0].length())) {
				// Save the move we made to be able to print it later,
				// so long as it's the very first part of the piece
				if (piecepart == 0) {
					moves[piece][1] = (rp + row);
					moves[piece][2] = (cp + column);
					piecepart++;
				}

				// Change the grid value if the piece part is a 1
				if (pieces[piece][rp][cp] == '1') {
					if (grid[rp + row][cp + column] == '1') grid[rp + row][cp + column] = '0';
					else grid[rp + row][cp + column] = '1';
				}
			}
			else return false;
		}
	}

	return true;
}

// This is our recursive function. We will continue to call
// this function until a solution has or has not been found
bool ShapeShifter::find_solution(int index) {
	bool solution = true, apply = false;
	int score = 0;

	// Base case
	if (index == pieces.size()) {
		// Reset the score in case it carries over any count
		score = 0;

		// Test to see if the grid is all 1's for a win
		for (int r = 0; r < grid.size(); r++) {
			for (int c = 0; c < grid[0].length(); c++) {
				if (grid[r][c] == '1') score++;
			}
		}

		// If we've won, we want to print all of the moves we made
		if (score == (grid.size() * grid[0].length())) {
			for (int i = 0; i < moves.size(); i++) {
				for (int j = 0; j < pieces[i].size(); j++) {
					printf("%s ", pieces[i][j].c_str());
				}
				printf("%d %d\n", moves[i][1], moves[i][2]);
			}
			exit(0);
		}

		return false;
	}

	// Place the piece
	for (int r = 0; r < grid.size(); r++) {
		for (int c = 0; c < grid[0].length(); c++) {
			apply = Apply(index, r, c);
			if (apply) solution = find_solution(index + 1);

			// If a piece doesn't work, undo the placement
			if (!solution || !apply) Apply(index, r, c);
		}
	}

	return false;
}

int main(int argc, char **argv) {
	ShapeShifter *shifter;
	vector<string> g;
	vector<vector<string> > p;
	istringstream ss;
	string s;
	int numpieces = 0;

	for (int i = 1; i <= (argc - 1); i++) {
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
