// CS140 Spring 2016
// Lab 02: Reading PGM files
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
};

int main(int argc, char **argv) {
	PGMFile pgm;
	double avgPixel = 0;
	int i = 1, currentPixel = -1, tempNumber = 0;

	cin >> pgm.p2;
	// First string should be P2
	if (pgm.p2 != "P2") {
		fprintf(stderr, "Bad PGM file -- first word is not P2\n");
		return -1;
	}
	//printf("P2? %s\n",pgm.p2.c_str());

	cin >> pgm.column;
	if (pgm.column < 0) {
		fprintf(stderr, "Bad PGM file -- No column specification\n");
		return -1;
	}
	//printf("column? %d\n",pgm.column);

	cin >> pgm.row;
	if (pgm.row < 0) {
		fprintf(stderr, "Bad PGM file -- No row specification\n");
		return -1;
	}
	//printf("row? %d\n",pgm.row);

	cin >> pgm.color;
	if (pgm.color != 255) {
		fprintf(stderr, "Bad PGM file -- 255 missing\n");
		return -1;
	}
	//printf("color? %d\n",pgm.color);

	while(!cin.eof()) {
		// Copy all the pixels
		if (tempNumber < 0 || tempNumber > 255) {
			fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", currentPixel);
			return -1;
		}
		pgm.pixels.push_back(tempNumber);
		currentPixel++;
		cin >> tempNumber;
	}

	pgm.numPixels = pgm.row * pgm.column;
	if (pgm.numPixels != pgm.pixels.size()) {
		fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels");
		return -1;
	}

	// Calculate the average pixel number
	for (i = 0; i < pgm.pixels.size(); i++) {
		avgPixel += pgm.pixels[i];
	}
	avgPixel /= pgm.numPixels;

	printf("# Rows: %11d\n", pgm.row);
    printf("# Columns: %8d\n", pgm.column);
    printf("# Pixels: %9d\n", pgm.numPixels);
    printf("Avg Pixel: %8.3f\n", avgPixel);

	return 0;
}

PGMFile::PGMFile()
	: column(0), row(0), color(0), numPixels(0) {}