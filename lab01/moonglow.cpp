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
	string name = "";
	int i, j = 0;
	int numAvg = 1;
	double temp, score, avgScore = 0;

	cin >> input[0];
	while (!cin.eof()) {
		i++;
		cin >> input[i];
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
		if (temp == atof(input[j].c_str())) score += temp;

		temp = 0;
	}

	printf("%s %f", name.c_str(), score);

	return 0;
}
