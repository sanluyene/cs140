#include "dl_hash.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
using namespace std;

vector <string> StoSVec(string &s)
{
  istringstream ss;
  string t;
  vector <string> rv;

  ss.str(s);
  while (ss >> t) rv.push_back(t);
  return rv;
}

main(int argc, char **argv)
{
  vector <string> sv;
  string s;
  int i;
  DL_Hash *h;
  string p;
  
  if (argc != 3 || atoi(argv[1]) <= 0) {
    cerr << "usage: dl_hash_test table-size prompt(- for none)\n";
    exit(1);
  }

  h = new DL_Hash(atoi(argv[1]));
  p = argv[2];

  while(1) {
    if (p != "-") {
      printf("%s ", p.c_str());
      fflush(stdout);
    }
    if (!getline(cin, s)) {
      delete h;
      exit(0);
    }
    sv = StoSVec(s);
    if (sv.size() == 0 || sv[0][0] == '#') {
    } else if (sv[0] == "INSERT") {
      if (sv.size() == 1) {
        printf("INSERT needs a name to follow it.\n");
      } else {
        s = sv[1];
        for (i = 2; i < sv.size(); i++) {
          s += " ";
          s += sv[i];
        }
        h->Insert(s);
      }
    } else if (sv[0] == "PRESENT") {
      if (sv.size() == 1) {
        printf("PRESENT needs a name to follow it.\n");
      } else {
        s = sv[1];
        for (i = 2; i < sv.size(); i++) {
          s += " ";
          s += sv[i];
        }
        printf("%s\n", (h->Present(s)) ? "Yes" : "No");
      }
    } else if (sv[0] == "ERASE") {
      if (sv.size() == 1) {
        printf("ERASE needs a name to follow it.\n");
      } else {
        s = sv[1];
        for (i = 2; i < sv.size(); i++) {
          s += " ";
          s += sv[i];
        }
        h->Erase(s);
      }
    } else if (sv[0] == "STRIP") {
      if (sv.size() == 1) {
        printf("STRIP needs a substring to follow it.  It can have spaces.\n");
      } else {
        s = sv[1];
        for (i = 2; i < sv.size(); i++) {
          s += " ";
          s += sv[i];
        }
        h->Strip_All_Substring(s);
      }
    } else if (sv[0] == "QUIT") {
      delete h;
      exit(0);
    } else if (sv[0] == "PRINT") {
      if (sv.size() != 1) {
        printf("PRINT takes no arguments.\n");
      } else {
        h->Print();
      }
    } else {
      printf("Commands are INSERT, PRESENT, ERASE, STRIP, PRINT, QUIT\n");
    }
  }
  
}
