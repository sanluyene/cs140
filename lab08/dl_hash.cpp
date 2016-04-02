// CS140 Spring 2016
// Lab 08: Hash table for Dlists
// Author: Ashley Sattler
// Date: 03/29/2016

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstdio>
#include "dl_hash.h"

// This is our hashing function
unsigned int djb_hash(string &s)
{
	int i;
	unsigned int h;

	h = 5381;

	for (i = 0; i < s.size(); i++) {
		h = (h << 5) + h + s[i];
	}
	return h;
}

// This is a constructor for the hash table
DL_Hash::DL_Hash(int size) {
	Dlist *newlist;

	table.resize(size);

	// We will be using separate chaining, so the vector must
	// be properly sized and initially populated with Dlists
	for (int i = 0; i < size; i++) {
		newlist = new Dlist;
		table[i] = newlist;
	}
}

// This is a deconstructor for the hash table
DL_Hash::~DL_Hash() {
	Dnode *d, *next;

	d = new Dnode;
	next = new Dnode;

	for (int i = 0; i < table.size(); i++) {
		d = table[i]->Begin();
		while (d != table[i]->End()) {
			next = d->flink;
			table[i]->Erase(d);
			d = next;
		}
	}
}

// This method inserts values into the hash table
void DL_Hash::Insert(string &s) {
	unsigned int val;

	val = djb_hash(s) % table.size();

	// We only want to insert a value if it is not already in
	// the table
	if (!(Present(s))) table[val]->Push_Back(s);
}

// This method checks to see if a given value is in the hash table
int DL_Hash::Present(string &s) {
	unsigned int val;
	Dnode *d;

	val = djb_hash(s) % table.size();
	d = new Dnode;

	d = table[val]->Begin();
	while (d != table[val]->End()) {
		if (d->s == s) return 1;
		d = d->flink;
	}

	return 0;
}

// This method deletes a given value from the hash table
void DL_Hash::Erase(string &s) {
	unsigned int val;
	Dnode *d;

	val = djb_hash(s) % table.size();
	d = new Dnode;

	// We only want to search if we know the value is in the table
	if (Present(s)) {
		d = table[val]->Begin();
		while (d != table[val]->End()) {
			if (d->s == s) {
				table[val]->Erase(d);
				break;
			}
			d = d->flink;
		}
	}
}

// This method will remove all hash table entries that contain the
// given string
void DL_Hash::Strip_All_Substring(string &s) {
	Dnode *d;

	d = new Dnode;

	for (int i = 0; i < table.size(); i++) {
		d = table[i]->Begin();
		while (d != table[i]->End()) {
			if (d->s.find(s) != string::npos) {
				table[i]->Erase(d);
			}
			d = d->flink;
		}
	}
}

// This method prints all values in the hash table
void DL_Hash::Print() {
	Dnode *d;

	d = new Dnode;

	for (int i = 0; i < table.size(); i++) {
		d = table[i]->Begin();
		while (d != table[i]->End()) {
			printf("%4d %s\n", i, d->s.c_str());
			d = d->flink;
		}
	}
}
