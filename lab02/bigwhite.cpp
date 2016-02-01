// CS140 Spring 2016
// Lab 02: Creating white pixel PGM files
// Author: Ashley Sattler
// Date: 02/01/2016

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct Pixel {
	int red, green, blue;
	
	// This is a 0-argument constructor class for Pixel
	Pixel();
	
	// This is a 3-argument constructor class for Pixel that will set the 3 struct variables
	// to the user-defined ints
	Pixel(int r, int g, int b);
};

class PPMFile {
	vector<Pixel> pixv;
	int width, height, color, numPixels;
	string p2 = "";

	public: 
		// This is a 0-argument constructor class for PPMFile
		PPMFile();
		
		// This function sets a pixel's properties.
		// It takes two ints for width and height coordinates, and a Pixel by const
		// reference to set at the desired coordinates. It returns a bool that
		// denotes if the desired coordinate is out of the bounds of the image.
		bool setPixel(int x, int y, const Pixel&);
		
		// This function writes a file.
		// It takes a const string by reference as a fileName. It returns a bool
		// that denotes if it could or could not write to the file.
		bool writeFile(const string& fileName);
};

int main(int argc, char **argv) {
	PPMFile ppm;
	bool goodFile;

	if (argc != 3) {
		fprintf(stderr, "Bad PGM file -- arguments not correct\n");
		return -1;
	}

	ppm.height = argv[1];
	ppm.width = argv[2];

	if (height < 0) {
		fprintf(stderr, "Bad PGM file -- rows not correct\n");
		return -2;
	}
	else if (width < 0) {
		fprintf(stderr, "Bad PGM file -- columns not correct\n");
		return -3;
	}
	else {
		ppm.numPixels = (ppm.height * ppm.width);
		for (int i = 0; i < ppm.numPixels; i++) {
			pixv.push_back(Pixel(0, 0, 0));
		}

		goodFile = ppm.writeFile(argv[3]);
		if (goodFile == false) {
			fprintf(stderr, "Bad PGM file -- output file failed\n");
			return -4;
		}
	}

	return 0;
}

Pixel::Pixel(){}

Pixel::Pixel(int r, int g, int b)
	: red(r), green(g), blue(b) {}

PPMFile::PPMFile()
	: width(0), height(0), color(0), numPixels(0) {}

bool PPMFile::writeFile(const string& fileName) {
	ofstream fout;
	
	fout.open(fileName);
	
	if(!fout) return false;
	else {
		// This covers the first 3 lines of the file
		fout << "P2" << endl << width << " " << height << endl << "255" << endl;
		
		// This holds all of our pixel colours
		for (unsigned int i = 0; i < pixv.size(); i++) {
			fout << pixv[i].red << " " << pixv[i].green << " " << pixv[i].blue << endl;
		}
		
		fout.close();
		return true;
	}
}