#include "dlist.h"
#include <iostream>
using namespace std;

main()
{
  string s;
  Dlist l;
  Dnode *d;

  while (getline(cin, s)) l.Push_Front(s);
  for (d = l.Begin(); d != l.End(); d = d->flink) cout << d->s << endl;
}
