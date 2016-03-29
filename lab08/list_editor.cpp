#include "dlist.h"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
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
  map <string, Dnode *> words;
  Dlist *l;
  Dnode *n;
  vector <string> sv;
  string s;
  string p;

  if (argc != 2) {
    cerr << "usage: list_editor prompt(- for none)\n";
    exit(1);
  }

  l = new Dlist;
  p = argv[1];

  while(1) {
    if (p != "-") {
      printf("%s ", p.c_str());
      fflush(stdout);
    }
    if (!getline(cin, s)) exit(0);

    sv = StoSVec(s);
    if (sv.size() == 0 || sv[0][0] == '#') {
    } else if (sv[0] == "CLEAR") {
      if (sv.size() != 1) {
        printf("CLEAR takes no arguments.\n");
      } else {
        delete l;
        words.clear();
        l = new Dlist;
      }
    } else if (sv[0] == "EMPTY") {
      if (sv.size() != 1) {
        printf("EMPTY takes no arguments.\n");
      } else {
        cout << ((l->Empty()) ? "Yes" : "No") << endl;
      }
    } else if (sv[0] == "SIZE") {
      if (sv.size() != 1) {
        printf("SIZE takes no arguments.\n");
      } else {
        cout << l->Size() << endl;
      }
    } else if (sv[0] == "ERASE") {
      if (sv.size() != 2) {
        printf("ERASE word.\n");
      } else {
        if (words.find(sv[1]) == words.end()) {
          cout << sv[1] << " is not on the list\n";
        } else {
          l->Erase(words[sv[1]]); 
          words.erase(words.find(sv[1]));
        }
      }
    } else if (sv[0] == "INSERT_BEFORE") {
      if (sv.size() != 3) {
        printf("INSERT_BEFORE s1 s2.\n");
      } else {
        if (words.find(sv[1]) != words.end()) {
          cout << sv[1] << " is already on the list\n";
        } else if (words.find(sv[2]) == words.end()) {
          cout << sv[2] << " is not on the list\n";
        } else {
          n = words[sv[2]];
          l->Insert_Before(sv[1], n);
          words[sv[1]] = n->blink;
        }
      }
    } else if (sv[0] == "INSERT_AFTER") {
      if (sv.size() != 3) {
        printf("INSERT_AFTER s1 s2.\n");
      } else {
        if (words.find(sv[1]) != words.end()) {
          cout << sv[1] << " is already on the list\n";
        } else if (words.find(sv[2]) == words.end()) {
          cout << sv[2] << " is not on the list\n";
        } else {
          n = words[sv[2]];
          l->Insert_After(sv[1], n);
          words[sv[1]] = n->flink;
        }
      }
    } else if (sv[0] == "PUSH_BACK") {
      if (sv.size() != 2) {
        printf("PUSH_BACK word.\n");
      } else {
        if (words.find(sv[1]) != words.end()) {
          cout << sv[1] << " is already on the list\n";
        } else {
          l->Push_Back(sv[1]);
          words[sv[1]] = l->Rbegin();
        }
      }
    } else if (sv[0] == "PUSH_FRONT") {
      if (sv.size() != 2) {
        printf("PUSH_FRONT word.\n");
      } else {
        if (words.find(sv[1]) != words.end()) {
          cout << sv[1] << " is already on the list\n";
        } else {
          l->Push_Front(sv[1]);
          words[sv[1]] = l->Begin();
        }
      }
    } else if (sv[0] == "POP_FRONT") {
      if (sv.size() != 1) {
        printf("POP_FRONT takes no arguments.\n");
      } else if (l->Empty()) {
        printf("POP_FRONT called on an empty list.\n");
      } else {
        s = l->Pop_Front();
        words.erase(words.find(s));
        cout << s << endl;
      }
    } else if (sv[0] == "POP_BACK") {
      if (sv.size() != 1) {
        printf("POP_BACK takes no arguments.\n");
      } else if (l->Empty()) {
        printf("POP_BACK called on an empty list.\n");
      } else {
        s = l->Pop_Back();
        words.erase(words.find(s));
        cout << s << endl;
      }
    } else if (sv[0] == "PRINT_FORWARD") {
      if (sv.size() != 1) {
        printf("PRINT_FORWARD takes no arguments.\n");
      } else {
        for (n = l->Begin(); n != l->End(); n = n->flink) {
          if (n != l->Begin()) cout << " ";
          cout << n->s;
        }
        cout << endl;
      }
    } else if (sv[0] == "QUIT") {
      exit(0);
    } else if (sv[0] == "PRINT_REVERSE") {
      if (sv.size() != 1) {
        printf("PRINT_REVERSE takes no arguments.\n");
      } else {
        for (n = l->Rbegin(); n != l->Rend(); n = n->blink) {
          if (n != l->Rbegin()) cout << " ";
          cout << n->s;
        }
        cout << endl;
      }
    } else {
      printf("Bad command\n");
    }
  }
  
}
