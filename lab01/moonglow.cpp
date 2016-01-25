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

	cin >> tempInput;

	while (!cin.eof()) {
		input.push_back(tempInput);
		cin >> tempInput;
	}

	for (j; j < input.size(); j++) {
		// There are possibly scores that need to be averaged after the word "AVERAGE"
		if (input[j] == "AVERAGE") {
			while (tempNumber = atof(input[j+1].c_str())) {
				avgScore += tempNumber;
				j++;
				numAvg++;
			}
			
			avgScore /= numAvg;
			score += avgScore;

			// Reset temporary variables when done
			avgScore = tempNumber = numAvg = 0;
		}
		// The student's name proceeds immediately after the word "NAME"
		if (input[j] == "NAME") name = input[j+1];
		// Score totals appear as plain numbers
		if (atof(input[j].c_str())) score += atof(input[j].c_str());
	}

	printf("%s %g\n", name.c_str(), score);

	return 0;
}

