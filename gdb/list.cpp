#include <cstdio>
#include <iostream>
#include "list.h"

using namespace std;

const int NUM_NAMES = 5;

int main() {
    int i;
    string name;
    listNode *name_list;
    listNode *name_list_ptr;

    name_list = new listNode;
    name_list->next = NULL;

    for (i = 0; i < NUM_NAMES; i++) {
        printf("enter a name: ");
	cin >> name;
	add_name_to_list(name_list, name);
    }

    for (name_list_ptr = name_list->next;
	 name_list_ptr != 0;
	 name_list_ptr = name_list_ptr->next) {
	printf("%s\n", name_list_ptr->name.c_str());
    }
}
	 
