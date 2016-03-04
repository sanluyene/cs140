// CS140 Spring 2016
// Lab 06: Keno
// Author: Ashley Sattler
// Date: 03/02/2016

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "product.h"

using namespace std;

void Product::Invert() {
	int tmp = 0;

	for (int i = 0; i < numerator.size(); i++) {
		tmp = numerator[i];
		numerator[i] = denominator[i];
		denominator[i] = tmp;
	}		
}

void Product::Multiply_Number(int n) {
	if (numerator.size() <= n) numerator.resize(n+1, 0);
	if (denominator.size() <= n) denominator.resize(n+1, 0);
	numerator[n]++;
}

void Product::Divide_Number(int n) {
	if (numerator.size() <= n) numerator.resize(n+1, 0);
	if (denominator.size() <= n) denominator.resize(n+1, 0);
	denominator[n]++;
}

void Product::Multiply_Factorial(int n) {
	while (n > 1) {
		Multiply_Number(n);
		n--;
	}
}

void Product::Divide_Factorial(int n) {
	while (n > 1) {
		Divide_Number(n);
		n--;
	}
}

void Product::Multiply_Binom(int n, int k) {
	Multiply_Factorial(n);
	Divide_Factorial(k);
	Divide_Factorial(n-k);
}

void Product::Divide_Binom(int n, int k) {
	Divide_Factorial(n);
	Multiply_Factorial(k);
	Multiply_Factorial(n-k);
}

void Product::Clear() {
	numerator.resize(0);
	denominator.resize(0);
}

void Product::Print() {
	// factor will be our temporary subtraction for factoring numer and denom
	// printed will be our counter for printing formatting
	// i is our loop counter
	// fin will tell us whether or not the factored remains are in the numer or denom
	int factor = 0, printed = 0, i = 0;
	vector<int> fin;

	for (i = 0; i < numerator.size(); i++) {
		factor = numerator[i] - denominator[i];
		fin.push_back(factor);
	}

	for (i = 0; i < fin.size(); i++) {
		if (fin[i] > 0) {
			while (fin[i] > 0)
			{	
				if (printed == 0) printf("%d", i);
				else printf(" * %d", i);
				fin[i]--;
				printed++;
			}
		}
	}
	if (printed == 0) printf("1");

	for (i = 2; i < fin.size(); i++) {
		if (fin[i] < 0) {
			fin[i] = abs(fin[i]);
			while (fin[i] > 0)
			{	
				printf(" / %d", i);
				fin[i]--;
				printed++;
			}
		}
	}
	printf("\n");
}

double Product::Calculate_Product() {
	// factor will be our temporary subtraction for factoring numer and denom
	// printed will be our counter for printing formatting
	// i is our loop counter
	// fin will tell us whether or not the factored remains are in the numer or denom
	int factor = 0, printed = 0, i = 0;
	vector<int> fin;
	double ans = 0.0;

	for (i = 0; i < numerator.size(); i++) {
		factor = numerator[i] - denominator[i];
		fin.push_back(factor);
	}

	for (i = 0; i < fin.size(); i++) {
		if (fin[i] > 0) {
			while (fin[i] > 0)
			{
				if (printed == 0) ans = i;
				else ans *= i;
				fin[i]--;
				printed++;
			}
		}
	}
	if (printed == 0) ans = 1;

	for (i = 0; i < fin.size(); i++) {
		if (fin[i] < 0) {
			fin[i] = abs(fin[i]);
			while (fin[i] > 0)
			{
				ans /= i;
				fin[i]--;
				printed++;
			}
		}
	}

	return ans;
}
