#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

class Cryptography {
	public:
		long long encrypt(vector <int> numbers);
};

long long Cryptography::encrypt(vector <int> numbers) {
	long long num = 1;
	
	sort(numbers.begin(), numbers.end());
	numbers[0]++;
	
	for (int i = 0; i < numbers.size(); i++) {
		num *= numbers[i];
	}
	
	return num;
}
