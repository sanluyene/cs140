// CS140 Spring 2016
// Lab 03: 
// Author: Ashley Sattler
// Date: 02/04/2016

#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

typedef vector <int> IVec;

// Write your code here:

// DO NOT CHANGE ANYTHING BELOW THIS LINE

void bad_pgm(string s)
{
  cerr << "Bad PGM file: " << s << endl;
  exit(1);

}