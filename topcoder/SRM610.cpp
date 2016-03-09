#include <vector>
#include <iostream>

using namespace std;

class DivideByZero {
	public:
		int CountNumbers(vector <int> numbers);
};

int DivideByZero::CountNumbers(vector <int> numbers) {
	int result = 0;
	vector<int> processed;
	vector<int> paper;

	paper.resize(101, 0);

	for (int i = 0; i < numbers.size(); i++) {
		paper[numbers[i]] = 1;
	}

	for (int i = 0; i < numbers.size(); i++) {
		for (int j = 0; j < processed.size(); j++) {
			if (numbers[i] != 0 && processed[j] != 0) {
				if (numbers[i] > processed[j]) result = numbers[i] / processed[j];
				else result = processed[j] / numbers[i];
				if (paper[result] != 1) {
					paper[result] = 1;
					numbers.push_back(result);
				}
			}
		}
		processed.push_back(numbers[i]);
	}

	return processed.size();
}
