#include <string>
#include <iostream>

using namespace std;

class MagicalStringDiv2 {
	public:
		int minimalMoves(string S);
};

int MagicalStringDiv2::minimalMoves(string S) {
	int i = 0, j = 0;
	
	for (; j < (S.size()/2); j++) {
		if (S[j] == '<') {
			S[j] = '>';
			i++;
		}
	}
	
	for (; j < S.size(); j++) {
		if (S[j] == '>') {
			S[j] = '<';
			i++;
		}
	}
	
	return i;
}
