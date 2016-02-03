#include <iostream>
#include <string>

using namespace std;

class AlienAndPassword {
	public:
		int getNumber(string S);
};

int AlienAndPassword::getNumber(string S) {
	int total = 1;
	char prev;

	prev = S[0];
	for (int i = 1; i < S.length(); i++) {
		if(S[i] != prev) total++;
		prev = S[i];
	}

	return total;
}
