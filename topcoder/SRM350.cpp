#include <iostream>
#include <string>

using namespace std;

class DistanceBetweenStrings {
	public:
		getDistance(string a, string b, string letterSet);
}

int getDistance(string a, string b, string letterSet) {
	// Counters
	int i = 0, j = 0, k = 0;
	// Calculation variables
	int numA = 0, numB = 0, distance = 0;

	// Set each string a and b to lowercase
	for (i = 0; i < a.size(); i++) {
		if (a[i] >= 'A' && a[i] <= 'Z') a[i] += ('a' - 'A');
	}
	for (j = 0; j < b.size(); j++) {
		if (b[j] >= 'A' && b[j] <= 'Z') b[j] += ('a' - 'A');
	}

	// Count the number of times each letter in letterSet appears
	// in strings a and b
	for (k = 0; k < letterSet.size(); k++) {
		for (i = 0; i < a.size(); i++) {
			if (a[i] == letterSet[k]) numA++;
		}
		for (j = 0; j < b.size(); j++) {
			if (b[j] == letterSet[k]) numB++;
		}

		// Perform distance calculation
		distance += pow((numA - numB), 2);

		// Reset numA and numB for next char in letterSet
		numA = numB = 0;
	}

	return distance;
}
