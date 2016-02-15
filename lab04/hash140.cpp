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

string HashTable::Find(string &key) {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) return vals[i];
		tmp++;
	}

	return "";
}

void HashTable::Print() {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] != "") {
			printf("%5d %s %s\n", i, keys[i].c_str(), vals[i].c_str());
		}
	}
}

int HashTable::Total_Probes() {
	return tmp;
}

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

int XOR(string code) {
	int i = 0;
	stringstream ss;
//	string temp1, temp2, temp3, temp4, temp5;

	if (code.length() <= 7) {
		ss << code;
		ss >> hex >> i;
	}
//	else {
//		for (int j = 0; j < code.length(); j++) {
//			if (j < 7) temp1.push_back(code[j]);
//			else if (j < 14) temp2.push_back(code[j]);
//			else if (j < 21) temp3.push_back(code[j]);
//			else if (j < 28) temp4.push_back(code[j]);
//			else if (j < 35) temp5.push_back(code[j]);
//		}
//		temp1 = (temp1 ^ temp2);
//		if (temp3 != "") temp1 ^= temp3;
//		if (temp4 != "") temp1 ^= temp4;
//		if (temp5 != "") temp1 ^= temp5;

//		ss << temp1;
//		ss >> hex >> i;
//	}

	return i;
}
