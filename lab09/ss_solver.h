// CS140 Spring 2016
// Lab 09: ShapeShifter Solver Declaration
// Author: Ashley Sattler
// Date: 04/13/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

class Solver {
	public:
		Solver(vector<string> g, vector<vector<string> > p);
		int insert_piece(int piece);

	protected:
		int ps;
		vector<string> grid;
		vector<vector<string> > pieces;
		vector<int> moves;
};
