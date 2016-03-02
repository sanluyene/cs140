#include <iostream>
#include <cstdlib>
#include "product.h"
using namespace std;


main(int argc, char **argv)
{
  Product p;
  int n, k;
  string s;

  while (1) {
    cin >> s;
    if (cin.fail()) exit(0);
    if (s == "CLEAR") {
      p.Clear();
    } else if (s == "CALCULATE") {
      cout << p.Calculate_Product() << endl;
    } else if (s == "INVERT") {
      p.Invert();
    } else if (s == "PRINT") {
      p.Print();
    } else if (s == "MULTIPLY") {
      cin >> n;
      if (cin.fail()) exit(1);
      p.Multiply_Number(n);
    } else if (s == "DIVIDE") {
      cin >> n;
      if (cin.fail()) exit(1);
      p.Divide_Number(n);
    } else if (s == "MULT_FACT") {
      cin >> n;
      if (cin.fail()) exit(1);
      p.Multiply_Factorial(n);
    } else if (s == "DIV_FACT") {
      cin >> n;
      if (cin.fail()) exit(1);
      p.Divide_Factorial(n);
    } else if (s == "MULT_BINOM") {
      cin >> n >> k;
      if (cin.fail()) exit(1);
      p.Multiply_Binom(n, k);
    } else if (s == "DIV_BINOM") {
      cin >> n >> k;
      if (cin.fail()) exit(1);
      p.Divide_Binom(n, k);
    } else {
      cout << "Bad command.  Should be one of\n";
      cout << endl;
      cout << "  CLEAR, CALCULATE, INVERT, PRINT, MULTIPLY, DIVIDE, MULT_FACT, DIV_FACT, MULT_BINOM or DIV_BINOM.\n";
    }
  }
}

