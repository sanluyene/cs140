#include "dlist.h"
#include <iostream>
using namespace std;

main()
{
  string s;
  Dlist l;

  while (getline(cin, s)) l.Push_Back(s);
  while (!l.Empty()) cout << l.Pop_Back() << endl;
}
