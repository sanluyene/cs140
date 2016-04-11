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

void Enum::do_enumeration(int index, int ones) {
cout << "enum index: " << index << " ones " << ones << endl;
	bool valid = true;
	int count = 0;

	// Base case
	if (index == length) {
		printf("%s", s.c_str());
		return;
	}

cout << "base" << endl;
	// Set index to zero
	s[index] = '0';

cout << "s " << s.c_str() << endl;
cout << "s[index] " << s[index] << endl;
	// Check validity
	for (int i = 0; i < length; i++) {
		if (s[i] == '1') count++;
	}
	if (count > ones) valid = false;
cout << "valid " << valid << endl;

	if (valid) do_enumeration(index++, ones);
	else {
		s[index] = '1';
		if (valid) do_enumeration(index++, ones--);
	}

	// Otherwise it is unsuccessful
	return;	
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
