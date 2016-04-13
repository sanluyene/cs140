// CS140 Spring 2016
// Lab 09: ShapeShifter Solver Game
// Author: Ashley Sattler
// Date: 04/12/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <vector>
#include "ss_solver.h"

using namespace std;

Solver::Solver(vector<string> g, vector<vector<string> > p) {
	grid = g;
	pieces = p;
	ps = p.size();
}

int Solver::insert_piece(int piece) {
	// Base case, if all pieces have been used
	if (ps == 0) {
		// check for win
		// if yes, print all moves
		return 1;

		//else return 0;
	}

	ps--;
	insert_piece((piece + 1));	
}

int main(int argc, char **argv) {
	Solver *s;
	vector<string> g;
	vector<vector<string> > p;
	istringstream ss;
	string st;
	int ps = 0;

	for (int i = 1; i <= 3; i++) {
		g.push_back(argv[i]);
	}

	while (getline(cin, st)) {
		ss.clear();
		ss.str(st);
		ps++;
		p.resize(ps);

		while (ss >> st) {
			p[ps-1].push_back(st);
		}
	}

	s = new Solver(g, p);
	s->insert_piece(0);

	return 0;
}
