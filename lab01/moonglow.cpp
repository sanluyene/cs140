// CS140 Spring 2016
// Lab 01: File parser for student names and grades for Philosophy 
// Author: Ashley Sattler
// Date: 01/25/2016

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

int main() {
	vector <string> input;
	string name = "", tempInput = "";
	int i = 0, j = 0, numAvg = 0;
	double score = 0, tempNumber = 0, avgScore = 0;	
	bool avgFlag = false;

	cin >> tempNumber;
	while (!cin.eof()) {
		if (cin.fail()) {
			cin.clear();			
			cin >> tempInput;

			// There are possibly scores that need to be averaged after the word "AVERAGE".
			// We add the last calculated average to the score, if there is one.
			if (numAvg > 0) {
				avgScore /= numAvg;
				score += avgScore;
			}
			// We will need to reset this flag, along with the average-related variables
			// if cin fails, because it did not read in a number.
			avgFlag = false;
			avgScore = 0, numAvg = 0;
			// We will turn on the avgFlag so that cin knows that numbers that are read in
			// need to be a part of an average calculation.
			if (tempInput == "AVERAGE") avgFlag = true;

			// The student's name proceeds immediately after the word "NAME".
			if (tempInput == "NAME") {
				cin.clear();
				cin >> name;
			}
		}
		else {
			// All other input are score numbers. If the avgFlag is true, then they are part of
			// the average calculation.
			if (avgFlag == true) {
				avgScore += tempNumber;
				numAvg++;
			}
			else score += tempNumber;
		}

		cin >> tempNumber;
	}

	printf("%s %g\n", name.c_str(), score);

	return 0;
}

