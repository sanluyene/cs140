// CS140 Spring 2016
// Lab 08: Dlisting
// Author: Ashley Sattler
// Date: 03/29/2016

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstdio>
#include "dl_hash.h"

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

DL_Hash::DL_Hash(int size) {
	Dlist *newlist;

	table.resize(size);

	for (int i = 0; i < size; i++) {
		newlist = new Dlist;
		table[i] = newlist;
	}
}

DL_Hash::~DL_Hash() {
	for (int i = 0; i < table.size(); i++) {

	}
}

void DL_Hash::Insert(string &s) {
	unsigned int val;

	val = djb_hash(s) % table.size();

	if (!(Present(s))) table[val]->Push_Back(s);
}

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

void DL_Hash::Erase(string &s) {
	unsigned int val;
	Dnode *d;

	val = djb_hash(s) % table.size();
	d = new Dnode;

	d = table[val]->Begin();
	while (d != table[val]->End()) {
		if (d->s == s) {
			table[val]->Erase(d);
			break;
		}
		d = d->flink;
	}
}

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
