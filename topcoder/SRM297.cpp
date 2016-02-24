#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PackingParts {
	public:
		int pack(vector <int> partSizes, vector <int> boxSizes);
};

int PackingParts::pack(vector <int> partSizes, vector <int> boxSizes) {
	int i = 0, j = 0;
	
	while (i < partSizes.size()) {
cout << "partsize[" << i << "] " << partSizes[i] << " boxsize[" << j << "] " << boxSizes[j] << endl;
		if (partSizes[i] <= boxSizes[j]) { i++; j++; }
		else j++;
		if (j == boxSizes.size()) return i;
	}
	
	return i;
}
