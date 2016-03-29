#include "dlist.h"
#include <iostream>
using namespace std;

main()
{
  string s;
  Dlist l;

  while (getline(cin, s)) l.Push_Front(s);
  while (!l.Empty()) {
    cout << l.Begin()->s << endl;
    l.Erase(l.Begin());
  }
}
