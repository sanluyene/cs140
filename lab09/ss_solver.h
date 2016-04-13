// CS140 Spring 2016
// Lab 09: ShapeShifter Solver Declaration
// Author: Ashley Sattler
// Date: 04/13/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

class ShapeShifter {
	public:
		ShapeShifter(vector<string> g, vector<<vector<string> > p);
		bool Apply(int piece, int row, int column);
		void find_solution(int index);

	protected:
		vector<string> grid;
		vector<vector<string> > pieces;
};