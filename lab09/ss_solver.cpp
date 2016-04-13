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
	row = 0;
	column = 0;
}

// This function will apply a piece at a given row and column.
// If called twice with the same variables, it reverts the grid
// back to its original state.
int ShapeShifter::Apply(int piece, int row, int column) {

	return 0;
}

// This is our recursive function. We will continue to call
// this function until a solution has or has not been found
void ShapeShifter::find_solution(int index) {
	bool win = true;
	int inserted = 0;

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
			printf("winning");
			exit(0);
		}
		else return;		
	}

	// Place the next piece
	inserted = Apply(pieces[index], row, column);
	while (!inserted && row < grid.size() && column < grid[0].length()) {
		// This will undo the bad grid move
		Apply(pieces[index], row, column);
		inserted = Apply(pieces[index], row + 1, column + 1);
	}

	// If it didn't fail, move on to the next piece
	find_solution(index + 1);

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