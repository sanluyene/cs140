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

	cin >> rows >> columns >> startingCharacter >> cycleSize >> width;

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
