#ifndef _PRODUCT_H
#define _PRODUCT_H
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Product {
  public:
    void Invert();
    void Multiply_Number(int n);
    void Divide_Number(int n);
    void Multiply_Factorial(int n);
    void Divide_Factorial(int n);
    void Multiply_Binom(int n, int k);
    void Divide_Binom(int n, int k);
    void Clear();
    void Print();
    double Calculate_Product();
  protected:
    vector <int> numerator;
    vector <int> denominator;
};

#endif
