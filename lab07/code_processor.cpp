#include <set>
#include <deque>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
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
	}
	else return -1;

	return 0;
}

int Code_Processor::Delete_User(string username) {

	return 0;
}

int Code_Processor::Add_Phone(string username, string phone) {

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

	return 0;
}

Code_Processor::~Code_Processor() {}

int Code_Processor::Write(const char *file) {

	return 0;
}

