// CS140 Spring 2016
// Lab 02: Reading PGM files
// Author: Ashley Sattler
// Date: 02/01/2016

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

class Pixel {
	public:
		int red, green, blue;

		// This is a 0-argument constructor class for Pixel
		Pixel();

		// This is a 3-argument constructor class for Pixel that will set the 3 struct variables
		// to the user-defined ints
		Pixel(int r, int g, int b);
};

class PGMFile {
	public: 
		vector<Pixel> pixv;
		int width, height, color, numPixels;
		string p2;

		// This is a 0-argument constructor class for PGMFile
		PGMFile();
};

int main(int argc, char **argv) {
	PGMFile pgm;
	bool goodFile;
	double avgPixel = 0, tempTotal = 0;
	int r = 0, g = 0, b = 0, i = 0, currentPixel = 0;

	cin >> pgm.p2;
	// First string should be P2
	if (pgm.p2 != "P2") {
		fprintf(stderr, "Bad PGM file -- first word is not P2\n");
		return -1;
	}

	while(!cin.eof()) {
		if (i > 0 && cin.fail()) break;
		else if (i == 1) {
			pgm.width = tempNumber;
			cout << sin << endl;
			if (pgm.width < 0) {
				fprintf(stderr, "Bad PGM file -- No column specification\n");
				return -1;
			}
		}
		else if (i == 2) {
			pgm.height = tempNumber;
			if (pgm.height < 0) {
				fprintf(stderr, "Bad PGM file -- No row specification\n");
				return -1;
			}
		}
		else if (i == 3) {
			pgm.color = tempNumber;
			if (pgm.color != 255) {
				fprintf(stderr, "Bad PGM file -- 255 missing\n");
				return -1;
			}
		}
		else if (i >= 3) { // Copy all the pixels
			while (!cin.eof) {
			int pixNum = 0;
			if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
				fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", currentPixel);
				return -1;
			}
			}
			pgm.pixv.push_back(Pixel(r, g, b));
			currentPixel++;
		}
		i++;
		cin >> tempNumber;
	}

	pgm.numPixels = pgm.height * pgm.width;

	// Calculate the average pixel number
	for (int i = 0; i < pgm.pixv.size(); i++) {
		tempTotal += pgm.pixv[i].red;
		tempTotal += pgm.pixv[i].green;
		tempTotal += pgm.pixv[i].blue;
		tempTotal /= 3;
		avgPixel += tempTotal;
	}
	avgPixel /= pgm.pixv.size();

	printf("# Rows:%-11s\n", pgm.height);
	printf("# Columns:%-8s\n", pgm.width);
	printf("# Pixels:%-9s\n", pgm.pixv.size());
	printf("Avg Pixel:%-8s\n", avgPixel);

	return 0;
}

Pixel::Pixel(){}

Pixel::Pixel(int r, int g, int b)
	: red(r), green(g), blue(b) {}

PGMFile::PGMFile()
	: width(0), height(0), color(0), numPixels(0) {}
