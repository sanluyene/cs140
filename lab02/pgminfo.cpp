// CS140 Spring 2016
// Lab 02: 
// Author: Ashley Sattler
// Date: 01/27/2016

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int rows = 0, columns = 0, numPixels = 0, inputNumber = 0, count = 0;
	int pixels[];
	double avgPixel = 0;
	string input = "";

	// First string should be P2
	cin >> input;
	if (input != "P2") fprintf(stderr, "Bad PGM file -- first word is not P2\n");

	// Next input is columns
	cin >> columns;
	if (columns < 0 || cin.fail()) fprintf(stderr, "Bad PGM file -- No column specification\n");

	// Next input is rows
	cin >> rows;
    if (rows < 0 || cin.fail()) fprintf(stderr, "Bad PGM file -- No row specification\n");

	// Next input should be 255
	cin >> inputNumber;
	if (inputNumber != 255) fprintf(stderr, "Bad PGM file -- 255 missing\n");

	// We calculate the total number of pixels in order to know how many to expect
	numPixels = rows * columns;

	while (cin >> inputNumber) {
		pixels.push_back(inputNumber);
		count++;

		if (cin.fail) fprintf(stderr, "Bad PGM file -- pixel bad");
	}

	return 0;
}
