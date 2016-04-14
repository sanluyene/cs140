// CS140 Spring 2016
// Lab 09: ShapeShifter Solver Declaration
// Author: Ashley Sattler
// Date: 04/13/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class ShapeShifter {
	public:
		ShapeShifter(vector<string> g, vector<vector<string> > p);
		bool Apply(int piece, int row, int column);
		bool find_solution(int index);

	protected:
		vector<string> grid;
		vector<vector<string> > pieces;
		vector<vector<int> > moves;
};
