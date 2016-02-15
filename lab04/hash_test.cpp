#include "hash140.h"
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cstdio>
using namespace std;

void usage(string s)
{
  fprintf(stderr, "usage: hash_test table-size function(Last7|XOR) resolution(Linear|Double) [dictionary]\n");
  if (s != "") fprintf(stderr, "%s\n", s.c_str());
  exit(1);
}

main(int argc, char **argv)
{
  string s, s2, key;
  string digits = "0123456789abcdef";
  int i;
  HashTable *h;
  int ts;
  ifstream f;

  if (argc != 5 && argc != 4) usage("");
  ts = atoi(argv[1]);
  if (ts <= 0) usage("Bad Table Size");
  s = argv[2];
  if (s != "Last7" && s != "XOR") usage("Bad function");
  s = argv[3];
  if (s != "Linear" && s != "Double") usage("Bad resolution");
  if (argc == 5) {
    f.open(argv[4]);
    if (f.fail()) { perror(argv[4]); exit(1); }
  }
  
  h = new HashTable(ts, argv[2], argv[3]);
  if (argc == 5) {
    while (getline(f, s)) {
      for (i = 0; digits.find(s[i]) != string::npos; i++) ;
      if (i == 0 || i == s.size() || s[i] != ' ') {
        cerr << "Bad line: " << s << endl;
        exit(1);
      }
      key = s.substr(0, i);
      for (; s[i] == ' '; i++) ;
      if (i == s.size()) { cerr << "Bad line: " << s << endl; exit(1); }
      s2 = s.substr(i);
      if (h->Find(key) != "") {
        fprintf(stderr, "Key %s inserted twice\n", key.c_str());
        exit(1);
      }
      h->Add_Hash(key, s2);
    }
    f.close();
  }

  while (cin >> s) {
    if (s == "PRINT") {
      h->Print();
    } else if (s == "TPROBES") {
      printf("%d\n", h->Total_Probes());
    } else if (s == "ADD") {
      if (cin >> s >> s2) {
        if (h->Find(s) != "") {
          printf("Key %s is already in the table\n", s.c_str());
        } else {
          h->Add_Hash(s, s2);
        }
      }
    } else if (s == "FIND") {
      if (cin >> s) {
        s2 = h->Find(s);
        if (s2 == "") {
          printf("Didn't find %s\n", s.c_str());
        } else {
          printf("%s %s\n", s.c_str(), s2.c_str());
        }
      } 
    } else {
      cerr << "Commands are PRINT, FIND key, ADD key val, and TPROBES\n";
    }
  }
}
