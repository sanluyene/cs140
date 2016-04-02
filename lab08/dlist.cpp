// CS140 Spring 2016
// Lab 08: Double-Linked Lists practice
// Author: Ashley Sattler
// Date: 03/29/2016

#include <iostream>
#include <cstdlib>
#include "dlist.h"

// This is the constuctor for our double-linked list
Dlist::Dlist() {
	Dnode *d;

	d = new Dnode;

	sentinel = d;
	d->flink = d;
	d->blink = d;
	d->s = "";
	size = 0;
}

// This is the deconstructor for our double-linked list
Dlist::~Dlist() {
	while(!(Empty())) {
		Dnode *d, *next;

		d = new Dnode;
		next = new Dnode;

		d = sentinel->flink;
		next = d->flink;
		sentinel->flink = next;
		next->blink = sentinel;

		size--;
		delete d;
	}
}

// This method checks to see if the Dlist has any values in it
int Dlist::Empty() {
	if (size > 0) return 0;
	return 1;
}

// This method returns the number of values in the Dlist
int Dlist::Size() {
	return size;
}

// This method inserts the given string into the front of the Dlist
void Dlist::Push_Front(string s) {
	Insert_Before(s, sentinel->flink);
}

// This method inserts a given string into the back of the Dlist
void Dlist::Push_Back(string s) {
	Insert_Before(s, sentinel);
}

// This method removes and returns the value at the front of the Dlist
string Dlist::Pop_Front() {
	string s = "";
	Dnode *d, *next;

	d = new Dnode;
	next = new Dnode;

	d = sentinel->flink;
	next = d->flink;
	sentinel->flink = next;
	next->blink = sentinel;
	s = d->s;

	size--;
	delete d;

	return s;
}

// This method removes and returns the value at the back of the Dlist
string Dlist::Pop_Back() {
	string s = "";
	Dnode *d, *prev;

	d = new Dnode;
	prev = new Dnode;

	d = sentinel->blink;
	prev = d->blink;
	sentinel->blink = prev;
	prev->flink = sentinel;
	s = d->s;

	size--;
	delete d;

	return s;
}

// This method returns the first item in the Dlist
Dnode *Dlist::Begin() {
	return sentinel->flink;
}

// This method returns the sentinel node
Dnode *Dlist::End() {
	return sentinel;
}

// This method returns the last item in the Dlist
Dnode *Dlist::Rbegin() {
	return sentinel->blink;
}

// This method returns the sentinel node
Dnode *Dlist::Rend() {
	return sentinel;
}

// This method inserts a given strings before the given element
void Dlist::Insert_Before(string s, Dnode *n) {
	Dnode *prev, *newnode;

	prev = new Dnode;
	newnode = new Dnode;

	prev = n->blink;
	newnode->s = s;
	newnode->blink = prev;
	newnode->flink = n;
	prev->flink = newnode;
	n->blink = newnode;

	size++;
}

// This method inserts a given strings after the given element
void Dlist::Insert_After(string s, Dnode *n) {
	Insert_Before(s, n->flink);
}

// This method removes the given element
void Dlist::Erase(Dnode *n) {
	Dnode *prev, *next;

	prev = new Dnode;
	next = new Dnode;

	prev = n->blink;
	next = n->flink;
	next->blink = prev;
	prev->flink = next;

	size--;
	delete n;
}