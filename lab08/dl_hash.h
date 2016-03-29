#include "dlist.h"
#include <vector>
using namespace std;

class DL_Hash {
  public:
    DL_Hash(int size);
    ~DL_Hash();
    void Insert(string &s);
    int Present(string &s);
    void Erase(string &s);
    void Strip_All_Substring(string &s);
    void Print();
  protected:
    vector <Dlist *> table;
};
