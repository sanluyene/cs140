#include <iostream>
#include <string>

using namespace std;

class FauxPalindromes {
	public:
		string classifyIt(string word);
};

string FauxPalindromes::classifyIt(string word) {
	string backwards = "", collapsed = "", collapsedBackwards = "";
	int i = 0, length = word.size(), clength = 0;

	for (i = 0; i < word.size(); i++) backwards.push_back(word[length - i - 1]);
	if (word == backwards) return "PALINDROME";

	collapsed.push_back(word[0]);
	for (i = 1; i < word.size(); i++) {
		if (word[i] != word[i-1]) collapsed.push_back(word[i]);
	}

	cout << "word " << word << "\n";
	cout << "backwards " << backwards << "\n";
	cout << "collapsed " << collapsed << "\n";

	clength = collapsed.size();
	for (i = 0; i < collapsed.size(); i++) collapsedBackwards.push_back(collapsed[clength - i - 1]);

	cout << "collapsed backwards " << collapsedBackwards << "\n";

	if (collapsed == collapsedBackwards) return "FAUX";
	else return "NOT EVEN FAUX";

}
