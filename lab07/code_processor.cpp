// CS140 Spring 2016
// Lab 07: Server-side processing for a code-based rewards program
// Author: Ashley Sattler
// Date: 03/25/2016

#include <set>
#include <deque>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "code_processor.h"

using namespace std;

// This is our hash function, our collision resolution is separate chaining
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

// This method adds a new prize to the prize list
int Code_Processor::New_Prize(string id, string description, int points, int quantity) {
	Prize *p;
	map <string, Prize *>::iterator pit;

	// We need to error check to ensure the prize doesn't already exist, and that it
	// is starting with a non-negative quantity and point value
	if (points < 0 || quantity < 0) return -1;
	pit = Prizes.find(id);

	if (pit == Prizes.end()) {
		p = new Prize;
		p->id = id;
		p->description = description;
		p->points = points;
		p->quantity = quantity;
		Prizes[id] = p;
	}
	else return -1;

	return 0;
}

// This method adds a new user to the user list
int Code_Processor::New_User(string username, string realname, int starting_points) {
	User *u;
	map <string, User *>::iterator uit;

	// We need to error check to ensure the user doesn't already exist, and that they
	// are starting with non-negative points
	if (starting_points < 0) return -1;
	uit = Names.find(username);

	if (uit == Names.end()) {
		u = new User;
		u->username = username;
		u->realname = realname;
		u->points = starting_points;
		Names[username] = u;
	}
	else return -1;

	return 0;
}

// This method deletes a user from the user list
int Code_Processor::Delete_User(string username) {
	map <string, User *>::iterator pit;
	map <string, User *>::iterator uit;
	set <string>::iterator upit;

	// We need to error check to ensure the user exists
	uit = Names.find(username);
	if (uit == Names.end()) return -1;

	for (upit = uit->second->phone_numbers.begin(); upit != uit->second->phone_numbers.end(); upit++) {
		Phones.erase(*upit);
	}

	Names.erase(uit);

	return 0;
}

// This method adds a phone to the phones list and to the specified user
int Code_Processor::Add_Phone(string username, string phone) {
	map <string, User *>::iterator pit;
	map <string, User *>::iterator uit;

	// We need to error check to ensure the phone doesn't already exist, that the user
	// does exist, and that the phone doesn't already belong to someone else
	pit = Phones.find(phone);
	if (pit != Phones.end()) return -1;
	uit = Names.find(username);
	if (uit == Names.end()) return -1;
	if (username != uit->first) return -1;

	uit->second->phone_numbers.insert(phone);
	Phones.insert(make_pair(phone, uit->second));

	return 0;
}

// This method removes a phone from the phone list and from the user's phones
int Code_Processor::Remove_Phone(string username, string phone) {
	map <string, User *>::iterator pit;
	map <string, User *>::iterator uit;

	// We need to error check to ensure the phone and user both exist, and that the
	// phone is attached to the specified user
	pit = Phones.find(phone);
	if (pit == Phones.end()) return -1;
	uit = Names.find(username);
	if (uit == Names.end()) return -1;
	if (pit->second->username != uit->first) return -1;

	uit->second->phone_numbers.erase(phone);
	Phones.erase(pit);

	return 0;
}

// This method returns a list of phones associated with a user
string Code_Processor::Show_Phones(string username) {
	map <string, User *>::iterator uit;
	set <string>::iterator pit;
	string phones = "";

	// We need to error check to ensure the user exists
	uit = Names.find(username);
	if (uit == Names.end()) return "BAD USER";

	for (pit = uit->second->phone_numbers.begin(); pit != uit->second->phone_numbers.end(); pit++) {
		phones += *pit + "\n";
	}

	return phones;
}

// This method redeems a code for points
int Code_Processor::Enter_Code(string username, string code) {
	set <string>::iterator sit;
	map <string, User *>::iterator uit;
	unsigned int hash = 0;
	int points = 0;

	// We need to error check to ensure the user exists and that the code
	// hasn't already been entered
	uit = Names.find(username);
	if (uit == Names.end()) return -1;
	sit = Codes.find(code);
	if (sit != Codes.end()) return -1;

	hash = djb_hash(code);

	if (hash % 17 == 0) points = 10;
	else if (hash % 13 == 0) points = 3;
	else return 0;

	Codes.insert(code);
	Names[username]->points += points;

	return points;
}

// This method redeems a code for points via a text message
int Code_Processor::Text_Code(string phone, string code) {
	set <string>::iterator cit;
	map <string, User *>::iterator uit;
	unsigned int hash = 0;
	int points = 0;

	// We need to error check to ensure the phone exists and that the code
	// hasn't already been entered
	uit = Phones.find(phone);
	if (uit == Phones.end()) return -1;
	cit = Codes.find(code);
	if (cit != Codes.end()) return -1;

	hash = djb_hash(code);

	if (hash % 17 == 0) points = 10;
	else if (hash % 13 == 0) points = 3;
	else return 0;

	Codes.insert(code);
	uit->second->points += points;

	return points;
}

// This method marks a code as used once redeemed
int Code_Processor::Mark_Code_Used(string code) {
	unsigned int hash = 0;
	bool realCode = false;
	set <string>::iterator cit;

	hash = djb_hash(code);

	// We need to error check to ensure the code is a real code, and that
	// it has not already been added
	if (hash % 17 == 0) realCode = true;
	else if (hash % 13 == 0) realCode = true;

	if (realCode == true) {
		cit = Codes.find(code);
		if (cit != Codes.end()) return -1;
		else {
			Codes.insert(code);
			return 0;
		}
	}
	return -1;
}

// This method returns the number of points associated with a user
int Code_Processor::Balance(string username) {
	map <string, User *>::iterator uit;

	// We need to error check to ensure the user exists
	uit = Names.find(username);
	if (uit == Names.end()) return -1;
	else return uit->second->points;
}

// This method redeems a prize for a specific user
int Code_Processor::Redeem_Prize(string username, string prize) {
	map <string, User *>::iterator uit;
	map <string, Prize *>::iterator pit;
	int	upoints = 0, ppoints = 0;

	// We need to error check to ensure the user and prize both exist, and that
	// the user has enough points to afford the prize
	uit = Names.find(username);
	pit = Prizes.find(prize);
	if (uit == Names.end()) return -1;
	if (pit == Prizes.end()) return -1;

	upoints = uit->second->points;
	ppoints = pit->second->points;

	// might need to include || pit->second->quantity == 0
	if (upoints < ppoints) return -1;
	uit->second->points -= ppoints;
	pit->second->quantity--;

	if (pit->second->quantity == 0) Prizes.erase(pit);

	return 0;
}

// This is the deconstructor
Code_Processor::~Code_Processor() {
	map <string, Prize *>::iterator pit;
	map <string, User *>::iterator uit;
	for (pit = Prizes.begin(); pit != Prizes.end(); pit++) {
		Prizes.erase(pit);
	}
	for (uit = Names.begin(); uit != Names.end(); uit++) {
		Names.erase(uit);
	}
}

// This method writes all of the server's current information to a file for backup and
// restoration purposes
int Code_Processor::Write(const char *file) {
	ofstream fout;
	map <string, Prize *>::iterator pit;
	map <string, User *>::iterator uit;
	set <string>::iterator cit;

	fout.open(file);
	if (fout.fail()) return -1;

	for (pit = Prizes.begin(); pit != Prizes.end(); pit++) {
		fout << "PRIZE " << pit->first.c_str() << " " << pit->second->points << " ";
		fout << pit->second->quantity << " " << pit->second->description.c_str() << endl;
	}
	for (uit = Names.begin(); uit != Names.end(); uit++) {
		fout << "ADD_USER " << uit->first.c_str() << " " << uit->second->points;
		fout << " " << uit->second->realname.c_str() << endl;
		for (cit = uit->second->phone_numbers.begin(); cit != uit->second->phone_numbers.end(); cit++) {
			fout << "ADD_PHONE " << uit->second->username.c_str() << " " << *cit << endl;
		}
	}
	for (cit = Codes.begin(); cit != Codes.end(); cit++) {
		fout << "MARK_USED " << *cit << endl;
	}

	fout.close();

	return 0;
}
