// CS140 Spring 2016
// Lab 04: Playing with hash tables
// Author: Ashley Sattler
// Date: 02/13/2016

#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "hash140.h"

using namespace std;

HashTable::HashTable(int table_size, string function, string collision) {
	keys.resize(table_size);
	vals.resize(table_size);
	if (function == "Last7") Fxn = 1;
	else Fxn = 2;
	if (collision == "Linear") Coll = 1;
	else Coll = 2;
}

void HashTable::Add_Hash(string &key, string &val) {
	// % 0xkey to find index
	// HashTable[index] = val
	//if HashTable[index] != ""
	// then collision technique

	//fprintf("Hash Table Full");
	//fprintf("Couldn't put %s into the table", key);
}

string HashTable::Find(string &key) {

	return "";
}

void HashTable::Print() {
	for (int i = 0; i < keys.size(); i++) {
		//if [i] != ""
		//printf(%-5d %s %s, i, key, val);
	}
}

int HashTable::Total_Probes() {

	return 0;
}

string Last7(string code) {

	return "";
}

string XOR(string code) {

	return "";
}
