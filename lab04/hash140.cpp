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

// Here we declare our two hash functions
int Last7(string &code);
int XOR(string &code);

// This is our constructor for the HashTable
HashTable::HashTable(int table_size, string function, string collision) {
	keys.resize(table_size);
	vals.resize(table_size);
	if (function == "Last7") Fxn = 1;
	else Fxn = 2; // XOR
	if (collision == "Linear") Coll = 1;
	else Coll = 2; // Double
	nkeys = 0;
	tmp = 0;
}

// This is for adding a new entry to the HashTable, including values for
// which hash and collision functions to use
void HashTable::Add_Hash(string &key, string &val) {
	if (nkeys == keys.size()) fprintf(stderr, "Hash Table Full\n");
	else {
		int i = 0; // Index
		int hash = 0, step = 0, times = 1;
		bool insert = false;
		int repeats = 0;

		if (Fxn == 1) hash = Last7(key);
		else hash = XOR(key);
		i = hash % keys.size();

		// For double hashing, if we get the same value more than once
		// we know it can't be inserted into the table
		repeats = i;
		while (insert == false) {
			if (keys[i] != "") {
				if (Coll == 1) {
					i = (i + 1) % keys.size();
					tmp++;
				}
				else {
					if (Fxn == 1) step = (XOR(key) % keys.size());
					else step = (Last7(key) % keys.size());
					if (step == 0) step = 1;
					i = (hash + (times * step)) % keys.size();
						if (i == repeats) {
							fprintf(stderr, "Couldn't put %s into the table\n", key.c_str());
							exit(1);
						}
					tmp++;
					times++;
				}
			}
			else {
				keys[i] = key;
				vals[i] = val;
				insert = true;
				nkeys++;
				repeats = 0;
			}
		}
	}
}

// This probes the hash table to find the requested key's value
string HashTable::Find(string &key) {
	int i = 0; // Index
	for (i; i < keys.size(); i++) {
		if (keys[i] == key) return vals[i];
	}

	return "";
}

// This prints the values stored in the hash table
void HashTable::Print() {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] != "") {
			printf("%5d %s %s\n", i, keys[i].c_str(), vals[i].c_str());
		}
	}
}

// This returns the total number of probes that were made against the
// hash table to find the requested values
int HashTable::Total_Probes() {
	return tmp;
}

// This function hashes a given code by using the last 7 characters as
// hex digits, and representing them as a decimal number
int Last7(string &code) {
	int i = 0;
	int length = code.length();
	stringstream ss;
	string temp;

	if (length <= 7) {
		ss << code;
		ss >> hex >> i;
	}
	else {
		for (int j = length - 7; j < length; j++) {
			temp.push_back(code[j]);
		}
		ss << temp;
		ss >> hex >> i;
	}

	return i;
}

// This function hashes a given code by separating the string into 7 
// character hex strings and performing an exclusive OR on them
int XOR(string &code) {
	int i = 0, j = 0, length = code.length();
	unsigned int hash = 0, nextWord = 0;
	stringstream ss;
	istringstream ss2;
	vector<string> subKeys;

	if (length <= 7) {
		ss << code;
		ss >> hex >> i;
	}
	else {
		for (j = 0; j < length; j++) {
			if (j%7 == 0) subKeys.push_back(code.substr(j, 7));
		}

		for (j = 0; j < subKeys.size(); j++) {
			ss2.clear();
			ss2.str(subKeys[j]);
			ss2 >> hex >> nextWord;
			hash = nextWord ^ hash;
		}
	}

	return hash;
}
