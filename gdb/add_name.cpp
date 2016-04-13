#include "list.h"
#include <string>

using namespace std;

void add_name_to_list(listNode *names, string &name_to_add) {
    listNode *new_node = new listNode;
    
    new_node->name = name_to_add;
    new_node->next = names->next;
    names->next = new_node;
}

