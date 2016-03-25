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

int Code_Processor::New_Prize(string id, string description, int points, int quantity) {
	Prize *p;
	map <string, Prize *>::iterator pit;

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

	return 0;
}

int Code_Processor::New_User(string username, string realname, int starting_points) {
	User *u;
	map <string, User *>::iterator uit;

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

int Code_Processor::Delete_User(string username) {

	return 0;
}

int Code_Processor::Add_Phone(string username, string phone) {
	map <string, User *>::iterator uit;

	uit = Phones.find(phone);
	if (uit != Phones.end()) return -1;
	uit = Names.find(username);
	if (uit == Names.end()) return -1;
	else {
		uit->second->phone_numbers.insert(phone);
		Phones[phone] = uit->second;
	}

	return 0;
}

int Code_Processor::Remove_Phone(string username, string phone) {

	return 0;
}

string Code_Processor::Show_Phones(string username) {

	return "";
}

int Code_Processor::Enter_Code(string username, string code) {

	return 0;
}

int Code_Processor::Text_Code(string phone, string code) {

	return 0;
}

int Code_Processor::Mark_Code_Used(string code) {

	return 0;
}

int Code_Processor::Balance(string username) {
	map <string, User *>::iterator uit;

	uit = Names.find(username);

	if (uit == Names.end()) return -1;
	else return uit->second->points;
}

int Code_Processor::Redeem_Prize(string username, string prize) {
	map <string, User *>::iterator uit;
	map <string, Prize *>::iterator pit;
	int	upoints = 0, ppoints = 0;

	uit = Names.find(username);
	pit = Prizes.find(prize);

	if (uit == Names.end()) return -1;
	if (pit == Prizes.end()) return -1;
	
	upoints = uit->second->points;
	ppoints = pit->second->points;

	if (upoints < ppoints) return -1;
	uit->second->points -= ppoints;
	pit->second->quantity--;

	if (pit->second->quantity == 0) Prizes.erase(pit);

	return 0;
}

Code_Processor::~Code_Processor() {}

int Code_Processor::Write(const char *file) {
	ofstream fout;
	map <string, Prize *>::iterator pit;
	map <string, User *>::iterator uit;

	fout.open(file);
	if (fout.fail()) return -1;

	for (pit = Prizes.begin(); pit != Prizes.end(); pit++) {
		fout << "PRIZE " << pit->first.c_str() << " " << pit->second->description.c_str() << " ";
		fout << pit->second->points << " " << pit->second->quantity << endl;
	}
	for (uit = Names.begin(); uit != Names.end(); uit++) {
		fout << "ADD_USER " << uit->first.c_str() << " " << uit->second->realname.c_str();
		fout << " " << uit->second->points << endl;
	}
	for (uit = Phones.begin(); uit != Phones.end(); uit++) {
		fout << "ADD_PHONE " << uit->second->username.c_str() << " " << uit->first.c_str() << endl;
	}

	fout.close();

	return 0;
}

