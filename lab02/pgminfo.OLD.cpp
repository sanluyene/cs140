// CS140 Spring 2016
// Lab 02: Reading PGM files
// Author: Ashley Sattler
// Date: 02/01/2016

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <fstream>

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

		// This function reads a file.
		// It takes a const string by reference as a fileName. It returns a bool
		// that denotes if it could or could not fully read the file.
		bool readFile(const string& fileName);
};

int main(int argc, char **argv) {
	PGMFile pgm;
	bool goodFile;
	double avgPixel = 0, tempTotal = 0;
	string filename;

	cout << "argc = " << argc << endl;
	cout << "argv0 = " << argv[0] << endl;
	cout << "argv1 = " << argv[1] << endl;
	filename = argv[1];
	goodFile = pgm.readFile(filename.c_str());

	if (goodFile == false) {
		cout << "goodfile = false" << endl;
		return -1;
	}
	else {
		cout << "after file read before calc" << endl;
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
	}

	return 0;
}

Pixel::Pixel(){}

Pixel::Pixel(int r, int g, int b)
	: red(r), green(g), blue(b) {}

PGMFile::PGMFile()
	: width(0), height(0), color(0), numPixels(0) {}

	bool PGMFile::readFile(const string& fileName) {
		ifstream fin;
		string line;
		int currentPixel = 1;

		fin.open(fileName.c_str());

		if(!fin) return false;
		else {
			int r = 0, g = 0, b = 0, i = 0;
			istringstream sin;

			while(getline(fin, line)) {
				sin.clear();
				sin.str(line);

				if (i == 0) {
					sin >> p2;
					// First string should be P2
					if (p2 != "P2") {
						fprintf(stderr, "Bad PGM file -- first word is not P2\n");
						return false;
					}
				}
				if (i == 1) {
					sin >> width >> height;
					if (width < 0) {
						fprintf(stderr, "Bad PGM file -- No column specification\n");
						return false;
					}
					if (height < 0) {
						fprintf(stderr, "Bad PGM file -- No row specification\n");
						return false;
					}
				}
				if (i == 2) {
					sin >> color;
					if (color != 255) {
						fprintf(stderr, "Bad PGM file -- 255 missing\n");
						return false;
					}
				}
				if (i >= 3) { // Copy all the pixels
					sin >> r >> g >> b;
					if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
						fprintf(stderr, "Bad PGM file -- pixel is not a number between 0 and 255");
						return false;
					}
					pixv.push_back(Pixel(r, g, b));
					currentPixel++;
				}
				i++;
			}

			fin.close();
			numPixels = height * width;

			if (pixv.size() == numPixels) return true;
			else {
				fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
				return false;
			}
		}
	}
