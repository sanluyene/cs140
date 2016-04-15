#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include "laba.h"
using namespace std;

class Person {
  public: 
    string name;
    string phone;
    string ssn; 
};

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
  BSTree t;
  Person *p;
  string s;
  vector <string> sv;
  vector <void *> a;
  string prompt;
  int i;

  if (argc != 2) {
    cerr << "usage: laba_test prompt(- for none)\n";
    exit(1);
  }

  prompt = argv[1];

  while (1) {
    if (prompt != "-") {
      printf("%s ", prompt.c_str());
      fflush(stdout);
    }
    if (!getline(cin, s)) exit(0);
    sv = StoSVec(s);
    if (sv.size() == 0 || sv[0][0] == '#') {
    } else if (sv[0] == "QUIT") {
      exit(0);
    } else if (sv[0] == "PRINT") {
      t.Print();
    } else if (sv[0] == "POSTORDER") {
      t.Postorder();
    } else if (sv[0] == "PREORDER") {
      t.Preorder();
    } else if (sv[0] == "ISAVL") {
      printf("%s\n", t.IsAVL() ? "Yes" : "No");
    } else if (sv[0] == "DEPTH") {
      if (sv.size() == 1) {
        printf("usage: DEPTH name\n");
      } else {
        s = sv[1];
        for (i = 2; i < sv.size(); i++) {
          s += " ";
          s += sv[i];
        }
        printf("%d\n", t.Depth(s));
      }
    } else if (sv[0] == "ROTATE") {
      if (sv.size() == 1) {
        printf("usage: ROTATE name\n");
      } else {
        s = sv[1];
        for (i = 2; i < sv.size(); i++) {
          s += " ";
          s += sv[i];
        }
        printf("%s\n", t.Rotate(s) ? "Rotated." : "Did not rotate.");
      }
    } else if (sv[0] == "HEIGHT") {
      printf("%d\n", t.Height());
    } else if (sv[0] == "SIZE") {
      printf("%d\n", t.Size());
    } else if (sv[0] == "EMPTY") {
      printf("%s\n", t.Empty() ? "Yes" : "No");
    } else if (sv[0] == "FIND") {
      if (sv.size() == 1) {
        printf("usage: FIND name\n");
      } else {
        s = sv[1];
        for (i = 2; i < sv.size(); i++) {
          s += " ";
          s += sv[i];
        }
        p = (Person *) t.Find(s);
        if (p == NULL) {
          printf("Not found\n");
        } else {
          printf("%s %s %s\n", p->name.c_str(), p->phone.c_str(), p->ssn.c_str());
        }
      }
    } else if (sv[0] == "DELETE") {
      if (sv.size() == 1) {
        printf("usage: DELETE name\n");
      } else {
        s = sv[1];
        for (i = 2; i < sv.size(); i++) {
          s += " ";
          s += sv[i];
        }
        p = (Person *) t.Find(s);
        if (p == NULL) {
          printf("Not found\n");
        } else {
          t.Delete(p->name);
          delete p;
        }
      }
    } else if (sv[0] == "SORT") {
      a = t.Sorted_Vector();
      for (i = 0; i < a.size(); i++) {
        p = (Person *) a[i];
        printf("%-30s %-15s %-15s\n", p->name.c_str(), p->phone.c_str(), p->ssn.c_str());
      }
    } else if (sv[0] == "INSERT") {
      if (sv.size() < 4) {
        printf("usage: INSERT name phone ssn -- name can have multiple words.\n");
      } else {
        p = new Person;
        p->name = sv[1];
        for (i = 2; i < sv.size()-2; i++) {
          p->name += " ";
          p->name += sv[i];
        }
        p->phone = sv[i];
        p->ssn = sv[i+1];
        if (!t.Insert(p->name, (void *) p)) {
          printf("%s not inserted.\n", p->name.c_str());
          delete p;
        }
      }
    } else {
      printf("Bad command.  Should be PRINT, INSERT, DELETE, FIND, POSTORDER, PREORDER, DEPTH, HEIGHT, ISAVL, ROTATE or SORT\n");
    }
  }
}
