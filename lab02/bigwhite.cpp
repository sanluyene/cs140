// CS140 Spring 2016
// Lab 02: Creating white pixel PGM files
// Author: Ashley Sattler
// Date: 02/03/2016

#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
	istringstream ss;
	int row, column, i, totalPixels;

	if (argc != 3) {
		fprintf(stderr, "usage: bigwhite rows cols\n");
		return -1;
	}

	ss.clear();
	ss.str(argv[1]);
	if (!(ss >> row)) {
		fprintf(stderr, "usage: bigwhite rows cols\n", argv[1]);
		return -1;
	}

	ss.clear();
	ss.str(argv[2]);
	if (!(ss >> column)) {
		fprintf(stderr, "usage: bigwhite rows cols\n", argv[2]);
		return -1;
	}

	if (row < 1 || column < 1) {
		fprintf(stderr, "usage: bigwhite rows cols\n");
		return -1;
	}

	totalPixels = row * column;

	// Print the beginning of the file
	printf("P2\n%d %d\n255\n", column, row);

	// Then print each pixel
	for (i = 0; i < totalPixels; i++) {
		printf("255\n");
	}

	return 0;
}
