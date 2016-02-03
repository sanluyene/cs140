// CS140 Spring 2016
// Lab 02: Horizontal flipping of PGM files
// Author: Ashley Sattler
// Date: 02/03/2016

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

class PGMFile {
	public: 
		vector<int> pixels;
		int column, row, color, numPixels;
		string p2;

		// This is a 0-argument constructor class for PGMFile
		PGMFile();
				
		// This function flips the image horizontally.
		// It takes nothing and returns nothing.
		void flipImage();
};

int main(int argc, char **argv) {
	PGMFile pgm;
	double avgPixel = 0;
	int i = 0, currentPixel = 0, tempNumber = 0;
	string input;

	cin >> pgm.p2;
	// First string should be P2
	if (pgm.p2 != "P2") {
		fprintf(stderr, "Bad PGM file -- first word is not P2\n");
		return -1;
	}

	// Next should be a number of columns
	cin >> pgm.column;
	if (pgm.column < 0) {
		fprintf(stderr, "Bad PGM file -- No column specification\n");
		return -1;
	}

	// Next should be a number of rows
	cin >> pgm.row;
	if (pgm.row < 0) {
		fprintf(stderr, "Bad PGM file -- No row specification\n");
		return -1;
	}

	// Next should be 255
	cin >> pgm.color;
	if (pgm.color != 255) {
		fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
		return -1;
	}

	pgm.numPixels = pgm.row * pgm.column;

	// Then should be all of the pixels
	for (currentPixel = 0; currentPixel < pgm.numPixels; currentPixel++) {
		cin >> tempNumber;
		if (tempNumber < 0 || tempNumber > 255) {
			fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", currentPixel);
			return -1;
		}
		pgm.pixels.push_back(tempNumber);
	}

	// Anything beyond is not acceptable data
	if (cin >> input) {
		fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
		return -1;
	}

	pgm.flipImage();

	return 0;
}

PGMFile::PGMFile()
	: column(0), row(0), color(0), numPixels(0) {}

void PGMFile::flipImage() {
	int x, y, pixelTmp;
	
	// Print the beginning of the file
	printf("%s\n%d %d\n%d\n", p2.c_str(), column, row, color);

	// Then print each pixel, starting from the farthest column
	for (y = 0; y < row; y++) {
		for(x = column; x > 0; x--) {
			int index = ((y * column) + x - 1);
			pixelTmp = pixels[index];
			printf("%d ", pixelTmp);
		}
		printf("\n");
	}
}
