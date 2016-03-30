// CS140 Spring 2016
// Lab 08: Dlisting
// Author: Ashley Sattler
// Date: 03/29/2016

#include <iostream>
#include <cstdlib>
#include "dlist.h"

Dlist::Dlist() {
	Dnode *d;

	d = new Dnode;

	sentinel = d;
	d->flink = d;
	d->blink = d;
	size = 0;
}

Dlist::~Dlist() {

}

int Dlist::Empty() {
	return size;
}

int Dlist::Size() {
	return size;
}

void Dlist::Push_Front(string s) {
	Insert_Before(s, sentinel->flink);
}

void Dlist::Push_Back(string s) {
	Insert_Before(s, sentinel);
}

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

	return s;
}

string Dlist::Pop_Back() {
	string s = "";
	Dnode *d, *prev;

	d = new Dnode;
	prev = new Dnode;

	d = sentinel->blink;
	prev = d->blink;
	sentinel->blink = prev;
	prev->blink = sentinel;
	s = d->s;

	size--;

	return s;
}

Dnode *Dlist::Begin() {
	return sentinel->flink;
}

Dnode *Dlist::End() {
	return sentinel;
}

Dnode *Dlist::Rbegin() {
	return sentinel->blink;
}

Dnode *Dlist::Rend() {
	return sentinel;
}

void Dlist::Insert_Before(string s, Dnode *n) {
	Dnode *prev, *next, *newnode;

	prev = new Dnode;
	next = new Dnode;
	newnode = new Dnode;

	prev = n->blink;
	next = n->flink;
	newnode->s = s;
	newnode->blink = prev;
	newnode->flink = next;
	prev->flink = newnode;
	next->blink = newnode;

	size++;
}

void Dlist::Insert_After(string s, Dnode *n) {
	Insert_Before(s, n->blink);
}

void Dlist::Erase(Dnode *n) {

}
