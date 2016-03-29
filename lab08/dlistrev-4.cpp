#include "dlist.h"
#include <iostream>
using namespace std;

main()
{
  string s;
  Dlist l;
  Dnode *d;

  while (getline(cin, s)) l.Push_Back(s);
  for (d = l.Rbegin(); d != l.Rend(); d = d->blink) cout << d->s << endl;
}
