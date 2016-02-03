// CS140 Spring 2016
// Lab 02: Creating white pixel PGM files
// Author: Ashley Sattler
// Date: 02/01/2016

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {
	istringstream ss;
	int row, column, i, totalPixels;

	if (argc != 3) {
		fprintf(stderr, "Bad PGM file -- arguments not correct\n");
		return -1;
	}

	ss.str(argv[1]);
	if (!(ss >> row)) {
		fprintf(stderr, "Argument %s is not an integer.\n", argv[1]);
		return -1;
	} 
	printf("Argument i: %d\n", i);

	ss.str(argv[2]);
	if (!(ss >> column)) {
		fprintf(stderr, "Argument %s is not an integer.\n", argv[2]);
		return -1;
	}

	totalPixels = row * column;

	// Print the beginning of the file
	printf("P2\n%d %d\n255\n", column, row);

	// Then print each pixel
	for (i = 0; i < totalPixels; i++) {
		printf("0\n");
	}

	return 0;
}
