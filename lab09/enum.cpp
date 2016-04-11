// CS140 Spring 2016
// Lab 09: Enumerating Strings Declaration
// Author: Ashley Sattler
// Date: 04/11/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "enum.h"

using namespace std;

Enum::Enum(int length) {
	length = length;
	s.resize(length);
}

int Enum::do_enumeration(int index, int ones) {
	int count = 0;

	// Base case
	if (index == length) {
		printf("%s", s.c_str());
		return 1;
	}

	// Check validity
	for (int i = 0; i < length; i++) {
		if (s[i] == '1') count++;
	}
	if (count > ones) return 0;

	// Otherwise continue solving
	for (i = '0'; i <= '1'; i++) {
		s[index] = i;
		if (i == '1') ones--;
		if (do_enumeration(index++, ones)) return 1;
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
