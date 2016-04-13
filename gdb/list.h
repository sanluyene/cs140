#include <string>

using namespace std;

class listNode {
  public:
    string name;
    listNode *next;
};

extern void add_name_to_list(listNode *, string &name);

