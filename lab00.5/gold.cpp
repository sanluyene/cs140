// CS140 Spring 2016
// Lab 0.5: Read a map on standard input and print total oz of gold
// Author: Ashley Sattler
// Date: 01/19/2016

#include <iostream>

using namespace std;

int main() {
	char input;
	int ounces = 0;

	while (cin >> input) {
		// The only rocks that have gold underneath them are
		// designated with the characters 'A', 'C', and 'Z'.
		// All other characters can be ignored, for they are
		// either dirt or plain rocks.
		switch(input) {
			case 'A':
				ounces += 1;
				break;
			case 'C':
				ounces += 3;
				break;
			case 'Z':
				ounces += 26;
				break;
			default:
				break;
		}
	}
	// We will display to the digger how much gold they found.
	cout << ounces << "\n";

	return 0;
}
