// CS140 Spring 2016
// Lab 01: Alphabetical checkerboard generator
// Author: Ashley Sattler
// Date: 01/25/2016

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main() {
	// We have variables for input from the user.
	int rows = 0, columns = 0, cycleSize = 0, width = 0;
	char startingCharacter, printChar;

	// User needs to input 2 ints, a single char, and 2 ints
	if (!(cin >> rows >> columns >> startingCharacter >> cycleSize >> width)) {
		fprintf(stderr, "usage: checkerboard  - stdin should contain R, C, SC, CS and W\n");
		return 1;
	}

	// We will process the input and check for errors before progressing.
	if (rows <= 0 || columns <= 0 || cycleSize <= 0 || width <= 0) {
		return 2;
	}
	if (startingCharacter + cycleSize > 127) {
		return 3;
	}

	for (int r = 0; r < rows; r++) {
		for (int wr = 0; wr < width; wr++) {
			for (int c = 0; c < columns; c++) {
				for (int wc = 0; wc < width; wc++) {
					printChar = startingCharacter + (r + c) % cycleSize;
					printf("%c",printChar);
				}
			}
			printf("\n");
		}
	}

	return 0;
}
