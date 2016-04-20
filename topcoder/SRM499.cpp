#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <iostream>

using namespace std;

class InternetSecurity {
	public:
		vector <string> determineWebsite(vector <string> address, vector <string> keyword, vector <string> dangerous, int threshold);
};

vector <string> InternetSecurity::determineWebsite(vector <string> address, vector <string> keyword, vector <string> dangerous, int threshold) {
	set <string> dangerWords;
	set <string>::iterator dit;
	set <int> webIndex;
	vector <vector <string> > KV;
	istringstream ss;
	string s;
	int count;
	vector <string> badSites;
	bool add = true;

	KV.resize(keyword.size());
	for (int i = 0; i < keyword.size(); i++) {
		ss.clear();
		ss.str(keyword[i]);
		while (ss >> s) KV[i].push_back(s);
	}

	for (int i = 0; i < dangerous.size(); i++) {
		dangerWords.insert(dangerous[i]);
	}

	while (add) {
		add = false;
		for (int i = 0; i < address.size(); i++) {
			count = 0;

			if (webIndex.find(i) == webIndex.end()) {
				for (int j = 0; j < KV[i].size(); j++) {
					if (dangerWords.find(KV[i][j]) != dangerWords.end()) count++;
				}

				if (count >= threshold) {
					for (int j = 0; j < KV[i].size(); j++) dangerWords.insert(KV[i][j]);
					webIndex.insert(i);
					add = true;
				}
			}
		}
	}

	for (int i = 0; i < webIndex.size(); i++) {
		badSites.push_back(address[i]);
	}

	return badSites;
}
