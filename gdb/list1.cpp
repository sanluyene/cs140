#include <cstdio>
#include <iostream>
#include "list.h"

using namespace std;

const int NUM_NAMES = 3;

int main() {
    string name;
    string name_list[NUM_NAMES];
    int num_names = 0;
    int i;

    printf("enter a name: ");
    while (cin >> name) {
	name_list[num_names] = name;
        printf("enter a name: ");
	num_names++;
    }

    printf("\n");
    for (i = 0; i < num_names; i++) {
	printf("%s\n", name_list[i].c_str());
    }
}
	 
