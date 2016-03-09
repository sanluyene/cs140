#include <set>
#include <deque>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

class User {
  public:
     string username;
     string realname;
     int points;
     set <string> phone_numbers;
};

class Prize {
  public:
     string id;
     string description;
     int points;
     int quantity;
};


class Code_Processor {
  public:
    int New_Prize(string id, string description, int points, int quantity);
    int New_User(string username, string realname, int starting_points);
    int Delete_User(string username);

    int Add_Phone(string username, string phone);
    int Remove_Phone(string username, string phone);
    string Show_Phones(string username);

    int Enter_Code(string username, string code);
    int Text_Code(string phone, string code);
    int Mark_Code_Used(string code);

    int Balance(string username);
    int Redeem_Prize(string username, string prize);
   
    ~Code_Processor();
    int Write(const char *file);

    void Double_Check_Internals();   /* You don't write this */

  protected:
    map <string, User *> Names;
    map <string, User *> Phones;
    set <string> Codes;
    map <string, Prize *> Prizes;
};
