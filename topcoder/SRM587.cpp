#include <iostream>
#include <string>

using namespace std;

class InsertZ {
	public:
		string canTransform(string init, string goal);
};

bool isEqual(string s1, string s2);

string InsertZ::canTransform(string init, string goal) {
	bool equal = false;
	string newGoal;	

	if (init.length() > goal.length()) {
		return "No";
	}
	else if (init.length() == goal.length()) {
		equal = isEqual(init, goal);
	}
	else {
		for (int i = 0; i < goal.length(); i++) {
			if (goal[i] == 'z') continue;
			else newGoal.push_back(goal[i]);
		}
	}

	equal = isEqual(init, newGoal);

	if (equal == true) return "Yes";
	else return "No";
}

bool isEqual(string s1, string s2) {
	bool equal = true;

	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] != s2[i]) equal = false;
	}

	return equal;
}
