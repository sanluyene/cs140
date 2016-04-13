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
ShapeShifter::ShapeShifter(string g, vector<string> p) {
	grid = g;
	pieces = p;
}

// This function will apply a piece at a given row and column.
// If called twice with the same variables, it reverts the grid
// back to its original state.
void ShapeShifter::Apply(int piece, int row, int column) {
	return;
}

// This is our recursive function. We will continue to call
// this function until a solution has or has not been found
void ShapeShifter::find_solution(int index) {
	// Base case
	if (index == pieces.size()) {
		// Test to see if the grid is all 1's for a win
		
	}
	
	return;
}

//int main(int argc, char **argv) {
//	ShapeShifter *s;
//	vector<string> p;
//	istringstream ss;
//	string st;
//	int ps = 0;

//	for (int i = 1; i <= 3; i++) {
//		g.push_back(argv[i]);
//	}

//	while (getline(cin, st)) {
//		ss.clear();
//		ss.str(st);
//		ps++;
//		p.resize(ps);

//		while (ss >> st) {
//			p[ps-1].push_back(st);
//		}
//	}

//	s = new ShapeShifter(g, p);
//	s->insert_piece(0, ps);

//	return 0;
//}
