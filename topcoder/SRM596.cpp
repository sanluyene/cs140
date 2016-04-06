#include <iostream>
#include <vector>

using namespace std;

class IncrementAndDoubling {
	public:
		int getMin(vector<int> desiredArray);
		int Adds(int k);
};

int IncrementAndDoubling::getMin(vector<int> desiredArray) {
	int added = 0, doubled = 0;

	for (int i = 0; i < desiredArray.size(); i++) {
		int n = desiredArray[i];
		if (n / 2 > doubled) doubled = n / 2;
		added += Adds(n);
	}

	return doubled + added;
}

int IncrementAndDoubling::Adds(int k) {
	if (k == 0) return 0;
	if (k == 1) return 1;
	if (k % 2 == 0) return Adds(k/2);
	if (k % 2 == 1) return (Adds(k/2) + 1);
}
