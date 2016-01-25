// CS140 Spring 2016
// Lab 01: Alphabetical checkerboard generator
// Author: Ashley Sattler
// Date: 01/25/2016

#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	// We have variables for input from the user.
	int rows, columns, cycleSize, width = 0;
	char startingCharacter, printChar;

	// User needs to input 2 ints, a single char, and 2 ints
	if (!(cin >> rows >> columns >> startingCharacter >> cycleSize >> width)) {
		//printf("Invalid arguments given. ");
		//printf("Please enter 2 ints, a character, and 2 ints.\n");
		return 1;
	}

	// We will process the input and check for errors before progressing.
	if (rows <= 0 || columns <= 0 || cycleSize <= 0 || width <= 0) {
		//printf("Cannot use zero or negative numbers.\n");
		return 2;
	}
	if (startingCharacter + cycleSize > 127) {
		//printf("Invalid input. ");
		//printf("Please enter a different character or a smaller cycle size.\n");
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
