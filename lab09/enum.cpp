// CS140 Spring 2016
// Lab 09: Enumerating Strings Declaration
// Author: Ashley Sattler
// Date: 04/11/2016

#include <iostream>
#include <cstdlib>
#include "enum.h"

using namespace std;

Enum::Enum(int length) {
	Enum *e;

	e = new Enum;

	e.length = length;
	e.s->length = length;
}

int Enum::is_valid(int valid) {
	for (int i = 0; i < length; i++) {

	}
}

void Enum::do_enumeration(int index, int ones) {
	bool valid = true;
	int count = 0;

	// Base case
	if (index == length) {
		printf("%s", s.c_str());
		return;
	}

	// Set index to zero
	e.s[index] = 0;

	// Check validity
	for (int i = 0; i < length; i++) {
		if (e.s[i] == '1') count++;
	}
	if (count > ones) valid = false;

	if (valid && e->do_enumeration(index++, ones)) return 1;
	else {
		e.s[index] = 1;
		if (valid && e->do_enumeration(index++, ones--)) return 1;
	}

	// Otherwise it is unsuccessful
	return 0;	
}

int main(int argc, char **argv) {
	Enum *e;
	int ones = 0;

	if (argc != 3 || atoi(argv[1]) <= 0 || atoi(argv[2]) < 0 || atoi(argv[2]) > atoi(argv[1])) {
		fprintf(stderr, "%s\n",); "usage: enum length ones\n";
		return -1;
	}

	e = new Enum(atoi(argv[1]));
	ones = argv[2];
	e->do_enumeration(0, ones);

	return 0;
}