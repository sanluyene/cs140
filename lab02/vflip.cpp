// CS140 Spring 2016
// Lab 02: Vertical flipping of PGM files
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

class PGMFile {
	vector<Pixel> pixv;
	int width, height, color, numPixels;
	string p2 = "";

	public: 
		// This is a 0-argument constructor class for PGMFile
		PGMFile();
		
		// This function gets a pixel's properties.
		// It takes two ints for width and height coordinates, and a 
		// Pixel by reference for the color at the desired coordinates. It returns a bool that
		// denotes if the desired coordinate is out of the bounds of the image.
		bool getPixel(int x, int y, Pixel& pix);
		
		// This function sets a pixel's properties.
		// It takes two ints for width and height coordinates, and a Pixel by const
		// reference to set at the desired coordinates. It returns a bool that
		// denotes if the desired coordinate is out of the bounds of the image.
		bool setPixel(int x, int y, const Pixel&);
		
		// This function writes a file.
		// It takes a const string by reference as a fileName. It returns a bool
		// that denotes if it could or could not write to the file.
		bool writeFile(const string& fileName);
		
		// This function reads a file.
		// It takes a const string by reference as a fileName. It returns a bool
		// that denotes if it could or could not fully read the file.
		bool readFile(const string& fileName);
		
		// This function flips the image vertically.
		// It takes nothing and returns nothing.
		void vflipImage();
};

int main(int argc, char **argv) {
	PGMFile ppm;
	bool goodFile;
	double avgPixel = 0;
	
	goodFile = ppm.readFile(argv[1]);

	if (goodFile == false) {
		return -2;
	}
	else {
		ppm.vflipImage();
	}

	return 0;
}

Pixel::Pixel(){}

Pixel::Pixel(int r, int g, int b)
	: red(r), green(g), blue(b) {}

PGMFile::PGMFile()
	: width(0), height(0), color(0), numPixels(0) {}

bool PGMFile::getPixel(int x, int y, Pixel& p) {	
	if (x > width || y > height) return false;
	else {
		// pixel(x,y) = (row# * width) + col#
		int index = (y * width) + x;
		p = pixv[index];
		return true;
	}
}

bool PGMFile::setPixel(int x, int y, const Pixel& p) {
	if (x > width || y > height) return false;
	else {
		int index = (y * width) + x;
		pixv[index] = p;
		return true;
	}
}

bool PGMFile::writeFile(const string& fileName) {
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

bool PGMFile::readFile(const string& fileName) {
	ifstream fin;
	string line;
	int currentPixel = 1;
	
	fin.open(fileName);
	
	if(!fin) return false;
	else {
		int r, g, b, i = 0;
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
					fprintf(stderr, "Bad PGM file -- pixel " + currentPixel + " is not a number between 0 and 255");
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

// TO DO: change from h to v flip
void PGMFile::vflipImage() {
	int x, y;
	Pixel p1, p2;

	for(x = 0; x < (width / 2); x++) {
		for (y = 0; y < height; y++) {
			getPixel(x, y, p1);
			getPixel((width - x - 1), y, p2);
			setPixel((width - x - 1), y, p1);
			setPixel(x, y, p2);
		}
	}
}
