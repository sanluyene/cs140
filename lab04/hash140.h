#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HashTable {
  public:
    HashTable(int table_size, string function, string collision);
    void Add_Hash(string &key, string &val);
    string Find(string &key);
    void Print();
    int Total_Probes();
  protected:
    vector <string> keys;
    vector <string> vals;
    int nkeys;
    int Fxn;
    int Coll;
    int tmp;
};

