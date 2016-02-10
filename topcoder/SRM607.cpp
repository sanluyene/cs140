#include <cmath>
#include <vector>

using namespace std;

class BoundingBox {
	public:
		int smallestArea(vector <int> X, vector <int> Y);
};

int BoundingBox::smallestArea(vector <int> X, vector <int> Y) {
	int lx = 0, bx = 0, ly = 0, by = 0, xLen = 0, yLen = 0;

	lx = X[0];
	bx = X[0];
	ly = Y[0];
	by = Y[0];

	for (int i = 1; i < X.size(); i++) {
		if (X[i] < lx) lx = X[i];
		if (X[i] > bx) bx = X[i];
	}
	for (int i = 1; i < Y.size(); i++) {
		if (Y[i] < ly) ly = Y[i];
		if (Y[i] > by) by = Y[i];
	}

	xLen = abs(lx) + abs(bx);
	yLen = abs(ly) + abs(by);

	return xLen * yLen;
}
