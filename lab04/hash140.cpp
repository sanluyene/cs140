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
#include <iso646.h>
#include "hash140.h"

using namespace std;

// Here we declare our two hash functions
int Last7(string code);
int XOR(string code);

// This is our constructor for the HashTable
HashTable::HashTable(int table_size, string function, string collision) {
	keys.resize(table_size);
	vals.resize(table_size);
	if (function == "Last7") Fxn = 1;
	else Fxn = 2; // XOR
	if (collision == "Linear") Coll = 1;
	else Coll = 2; // Double
	nkeys = 0;
}

// This is for adding a new entry to the HashTable, including values for
// which hash and collision functions to use
void HashTable::Add_Hash(string &key, string &val) {

	if (nkeys == keys.size()) fprintf(stderr, "Hash Table Full\n");
	else {
		int i = 0; // Index
		int hash = 0, err = 0, temp = 0;
		bool insert = false;

		if (Fxn == 1) hash = Last7(key);
		else hash = XOR(key);

		i = hash % keys.size();

		while (insert == false) {
			if (keys[i] != "") {
				if (Coll == 1) {
					i++;
				}
				else {
					if (Fxn == 1) temp = XOR(key) % keys.size();
					else tmp = Last7(key) % keys.size();
					if (temp == 0) temp = 1;
					i = (hash + temp) % keys.size();
					err++;
					if (err >= 5) {
						fprintf(stderr, "Couldn't put %s into the table", key.c_str());
						insert = true;
					}
				}
			}
			else {
				keys[i] = key;
				vals[i] = val;
				insert = true;
				nkeys++;
			}
		}
	}
}

// This probes the hash table to find the requested key's value
string HashTable::Find(string &key) {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) return vals[i];
		tmp++;
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
int Last7(string code) {
	int i = 0;
	stringstream ss;
	string temp;

	if (code.length() <= 7) {
		ss << code;
		ss >> hex >> i;
	}
	else {
		int length = code.length();
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
int XOR(string code) {
	int i = 0, j = 0;
	stringstream ss;
	string temp1, temp2;

	if (code.length() <= 7) {
		ss << code;
		ss >> hex >> i;
	}
	else {
		// The first 7 character chunk will be what we start with
		int length = code.length();
		for (j = 0; j < 7; j++) {
			temp1.push_back(code[j]);
		}

		// As long as we haven't reached the end of the code, we need
		// to continue breaking it into 7 character chunks
		while (j < length) {
			for (j; j%7 <= 6; j++) {
				temp2.push_back(code[j]);
			}

			// If the last chunk is less than 7 characters, we need to
			// pad it with 0's from the left
			if (temp2.length() != 7) {
				int k = 7 - temp2.length();
				string temp3;
				for (int l = 0; l < k; l++) temp3.push_back('0');
				for (int l = 0; l < temp2.length(); l++) temp3.push_back(temp2[l]);
				temp2 = temp3;
			}

			// Now that we have our chunks, we need to XOR the strings
			// char by char
			for (int k = 0; k < 7; k++) {
				temp1[k] ^= temp2[k];
			}
		}

		ss << temp1;
		ss >> hex >> i;
	}

	return i;
}
