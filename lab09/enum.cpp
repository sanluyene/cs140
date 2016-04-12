// CS140 Spring 2016
// Lab 09: Enumerating Strings Declaration
// Author: Ashley Sattler
// Date: 04/11/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "enum.h"

using namespace std;

Enum::Enum(int len) {
	length = len;
	s.resize(length);
}

int Enum::do_enumeration(int index, int ones) {
	// Base case
	if (index == length) {
		printf("%s\n", s.c_str());
		return 1;
	}

	// Check and solve
	if ((length - index) > ones) {
		s[index] = '0';
		do_enumeration((index + 1), ones);
	}
	if (ones > 0) {
		s[index] = '1';
		do_enumeration((index + 1), (ones - 1));
	}

	// Otherwise it is unsuccessful
	return 0;	
}

int main(int argc, char **argv) {
	Enum *e;
	int ones = 0;

	if (argc != 3 || atoi(argv[1]) <= 0 || atoi(argv[2]) < 0 || atoi(argv[2]) > atoi(argv[1])) {
		fprintf(stderr, "usage: enum length ones\n");
		return -1;
	}

	e = new Enum(atoi(argv[1]));
	ones = atoi(argv[2]);
	e->do_enumeration(0, ones);

	return 0;
}
