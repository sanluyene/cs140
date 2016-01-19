// CS140 Spring 2016
// Lab 01: Alphabetical checkerboard generator
// Author: Ashley Sattler
// Date: 01/19/2016

#include <iostream>

using namespace std;

int main() {
	// We have variables for input from the user.
	int rows, columns, cycleSize, width = 0;
	char startingCharacter, printChar;

	// User needs to input 2 ints, a single char, and 2 ints
	if (!(cin >> rows >> columns >> startingCharacter >> cycleSize >> width)) {
		cout << "Invalid arguments given. ";
		cout << "Please enter 2 ints, a character, and 2 ints.\n";
		return 1;
	}

	// We will process the input and check for errors before progressing.
	if (rows <= 0 || columns <= 0 || cycleSize <= 0 || width <= 0) {
		cout << "Cannot use zero or negative numbers.\n";
		return 2;
	}
	if (startingCharacter + cycleSize > 127) {
		cout << "Invalid input. ";
		cout << "Please enter a different character or a smaller cycle size.\n";
		return 3;
	}

	for (int r = 0; r < rows; r++) {
		for (int wr = 0; wr < width; wr++) {
			for (int c = 0; c < columns; c++) {
				for (int wc = 0; wc < width; wc++) {
					printChar = startingCharacter + (r + c) % cycleSize;
					cout << printChar;
				}
			}
			cout << "\n";
		}
	}

	return 0;
}
