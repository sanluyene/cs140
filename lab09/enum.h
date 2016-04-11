// CS140 Spring 2016
// Lab 09: Enumerating Strings Header
// Author: Ashley Sattler
// Date: 04/11/2016

#include <string>

using namespace std;

class Enum {
	public:
		Enum(int length);
		void do_enumeration(int index, int ones);

	protected:
		string s;
		int length;
};
