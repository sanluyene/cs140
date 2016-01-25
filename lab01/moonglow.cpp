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
	string name, tempInput = "";
	int j = 0, numAvg = 1;
	double score, avgScore = 0;

	cin >> tempInput;

	while (!cin.eof()) {
		input.push_back(tempInput);
		cin >> tempInput;
	}

	for (j; j < input.size(); j++) {
		// The student's name proceeds immediately after the word "NAME"
		if (input[j] == "NAME") name = input[j+1];
		// There are possibly scores that need to be averaged after the word "AVERAGE"
		if (input[j] == "AVERAGE") {
			while (atof(input[j+numAvg].c_str())) {
				avgScore += atof(input[j+numAvg].c_str());
				numAvg++;
			}
			
			avgScore /= numAvg;
			score += avgScore;
			numAvg = 1;
		}
		// Score totals appear as plain numbers
		if (atof(input[j].c_str()))	score += atof(input[j].c_str());

	}

	printf("%s %.0f \n", name.c_str(), score);

	return 0;
}
