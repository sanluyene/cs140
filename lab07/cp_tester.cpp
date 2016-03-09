#include <set>
#include <deque>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "code_processor.h"
using namespace std;

#define VIT(i, v) for (i = 0; i < v.size(); i++) 
#define IT(it, ds) for (it = ds.begin(); it != ds.end(); it++)

vector <string> StoSVec(string &s)
{
  istringstream ss;
  string t;
  vector <string> rv;

  ss.str(s);
  while (ss >> t) rv.push_back(t);
  return rv;
}

int main(int argc, char **argv)
{
  ifstream f;
  int i, a;
  int points, quantity, done;
  int do_cin;
  vector <string> sv;
  string s, id, description, realname;
  Code_Processor CP;

  for (a = 1; a < argc; a++) {
    s = argv[a];
    if (s == "-") {
      do_cin = 1;
    } else {
      do_cin = 0;
      f.clear();
      f.open(argv[a]);
      if (f.fail()) {
        perror(argv[a]);
        exit(1);
      }
    }
    do {
      if (do_cin) {
        cout << "CP_Tester> ";
        cout.flush();
        done = (getline(cin, s)) ? 0 : 1;
      } else {
        done = (getline(f, s)) ? 0 : 1;
      }
      if (!done) {
        sv = StoSVec(s);
        if (sv.size() > 0 && sv[0] != "#") {
          if (sv.size() > 20) {
            printf("Too many words on the line.  Must be <= 20.\n");
          } else if (sv[0] == "ADD_USER") {
            if (sv.size() < 4 || sscanf(sv[2].c_str(), "%d", &points) == 0 || points < 0) {
              printf("Bad ADD_USER line: %s\n", s.c_str());
            } else {
              id = sv[1];
              realname = sv[3];
              for (i = 4; i < sv.size(); i++) {
                realname += " ";
                realname += sv[i];
              }
              if (CP.New_User(id, realname, points) != 0) {
                printf("ADD_USER %s unsuccessful\n", id.c_str());
              } else if (do_cin) {
                printf("ADD_USER successful\n");
              }
            }
    

          } else if (sv[0] == "ADD_PHONE") {
            if (sv.size() != 3) {
              printf("Bad ADD_PHONE line: %s\n", s.c_str());
            } else if (CP.Add_Phone(sv[1], sv[2]) != 0) {
              printf("ADD_PHONE: Either the user (%s) doesn't exist,\n", sv[1].c_str());
              printf("           or the phone number (%s) is already assigned\n", sv[2].c_str());
            } else if (do_cin) {
              printf("ADD_PHONE successful\n");
            }
          } else if (sv[0] == "ENTER_CODE") {
            if (sv.size() != 3) {
              printf("Bad ENTER_CODE line: %s\n", s.c_str());
            } else {
              i = CP.Enter_Code(sv[1], sv[2]);
              if (i < 0) {
                printf("ENTER_CODE: Either the user (%s) doesn't exist,\n", sv[1].c_str());
                printf("            or the code (%s) has been used already\n", sv[2].c_str());
              } else if (i == 0) {
                printf("ENTER_CODE: Bad code (%s).\n", sv[2].c_str());
              } else if (do_cin) {
                printf("ENTER_CODE: Added %d points to %s.\n", i, sv[1].c_str());
              }
            }
          } else if (sv[0] == "TEXT_CODE") {
            if (sv.size() != 3) {
              printf("Bad TEXT_CODE line: %s\n", s.c_str());
            } else {
              i = CP.Text_Code(sv[1], sv[2]);
              if (i < 0) {
                printf("TEXT_CODE: Either the phone number (%s) is not registered,\n", sv[1].c_str());
                printf("           or the code (%s) has been used already\n", sv[2].c_str());
              } else if (i == 0) {
                printf("TEXT_CODE: Bad code (%s).\n", sv[2].c_str());
              } else if (do_cin) {
                printf("TEXT_CODE: Added %d points.\n", i);
              }
            }
          } else if (sv[0] == "REDEEM") {
            if (sv.size() != 3) {
              printf("Bad REDEEM line: %s\n", s.c_str());
            } else if (CP.Redeem_Prize(sv[1], sv[2]) != 0) {
              printf("REDEEM: Either the user (%s) doesn't exist,\n", sv[1].c_str());
              printf("        or the prize (%s) doesn't exist,\n", sv[2].c_str());
              printf("        or the user can't afford the prize.\n");
            } else if (do_cin) {
              printf("REDEEM successful\n");
            }
 
          } else if (sv[0] == "REMOVE_PHONE") {
            if (sv.size() != 3) {
              printf("Bad REMOVE_PHONE line: %s\n", s.c_str());
            } else if (CP.Remove_Phone(sv[1], sv[2]) != 0) {
              printf("REMOVE_PHONE: Either the user (%s) doesn't exist,\n", sv[1].c_str());
              printf("              or the phone number (%s) is unassigned,\n", sv[2].c_str());
              printf("              or the phone number is not assigned to the user.\n");
            } else if (do_cin) {
              printf("REMOVE_PHONE successful\n");
            }

          } else if (sv[0] == "DELETE_USER") {
            if (sv.size() != 2) {
              printf("Bad DELETE_USER line: %s\n", s.c_str());
            } else if (CP.Delete_User(sv[1]) != 0) {
              printf("DELETE_USER: The user (%s) doesn't exist,\n", sv[1].c_str());
            } else if (do_cin) {
              printf("DELETE_USER successful\n");
            }
 
          } else if (sv[0] == "QUIT") {
            exit(0);

          } else if (sv[0] == "PRIZE") {
            if (sv.size() < 5 || atoi(sv[2].c_str()) <= 0 || 
                                 atoi(sv[3].c_str()) <= 0) {
              printf("Bad PRIZE line: %s\n", s.c_str());
            } else {
              id = sv[1];
              points = atoi(sv[2].c_str());
              quantity = atoi(sv[3].c_str());
              description = sv[4];
              for (i = 5; i < sv.size(); i++) {
                description += " ";
                description += sv[i];
              }
              if (CP.New_Prize(sv[1], description, points, quantity) != 0) {
                printf("Prize %s couldn't be added\n", id.c_str());
              } else if (do_cin) {
                printf("PRIZE successful\n");
              } 
            }
          } else if (sv[0] == "WRITE") {
            if (sv.size() != 2) {
              printf("Bad WRITE line: %s\n", s.c_str());
            } else if (CP.Write(sv[1].c_str()) != 0) {
              printf("Couldn't write to %s\n", sv[1].c_str());
            } else if (do_cin) {
              printf("WRITE successful\n");
            } 
          } else if (sv[0] == "SHOW_PHONES") {
            if (sv.size() != 2) {
              printf("Bad SHOW_PHONES line: %s\n", s.c_str());
            } else {
              s = CP.Show_Phones(sv[1]);
              if (s == "BAD USER") {
                 printf("SHOW_PHONES: No user %s\n", sv[1].c_str());
              } else {
                cout << s;
              } 
            }
          } else if (sv[0] == "BALANCE") {
            if (sv.size() != 2) {
              printf("Bad BALANCE line: %s\n", s.c_str());
            } else {
              i = CP.Balance(sv[1]);
              if (i == -1) {
                printf("BALANCE: No user %s\n", sv[1].c_str());
              } else {
                printf("%d Point%s\n", i, ((i == 1) ? "" : "s"));
              }
            } 
          } else if (sv[0] == "DOUBLE_CHECK") {
             CP.Double_Check_Internals();

          } else if (sv[0] == "MARK_USED") {
            for (i = 1; i < sv.size(); i++) {
              if (CP.Mark_Code_Used(sv[i]) == 0) {
                if (do_cin) {
                  printf("%s marked as used\n", sv[i].c_str());
                } 
              } else {
                printf("MARK_USED: Either %s is already used or it's a bad code.\n", sv[i].c_str());
              } 
            } 
          } else {
            printf("Unknown command: %s\n", s.c_str());
          }
        }
      }
    } while (!done);
    if (!do_cin) f.close();
  }
}
