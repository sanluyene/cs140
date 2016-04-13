// CS140 Spring 2016
// Lab 09: ShapeShifter Solver Declaration
// Author: Ashley Sattler
// Date: 04/13/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Solver {
	public:
		Solver(vector<string> grid, vector<vector<string>> pieces);
		int insert_piece(int piece);

	protected:
		int pieces;
};
