// CS140 Spring 2016
// Lab 0.5: Read a map on standard input and print total oz of gold
// Author: Ashley Sattler
// Date: 01/19/2016

#include <iostream>

using namespace std;

int main() {
	char input;
	int ounces = 0;

	cin >> input;
	while (!cin.eof()) {
		// The only rocks that have gold underneath them are
		// designated with the capital alphabetical characters.
		if (input < 65 || input > 91) ounces = ounces; 
		else ounces += (input - 64);
		cin.clear();
		cin >> input;
	}

	// We will display to the digger how much gold they found.
	cout << ounces << "\n";

	return 0;
}
