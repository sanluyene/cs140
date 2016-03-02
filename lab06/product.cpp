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
//	if (numerator == NULL || denominator == NULL) return;
	if (numerator.size() < n) numerator.resize(n+1, 0);
	numerator[n]++;
}

void Product::Divide_Number(int n) {
//	if (numerator.size() <= 0 || denominator.size() <= 0) return;
	if (denominator.size() < n) denominator.resize(n+1, 0);
	denominator[n]++;
}

void Product::Multiply_Factorial(int n) {

}

void Product::Divide_Factorial(int n) {

}

void Product::Multiply_Binom(int n, int k) {

}

void Product::Divide_Binom(int n, int k) {

}

void Product::Clear() {

}

void Product::Print() {
	// factor will be our temporary subtration for factoring numer and denom
	// printed will be our counter for printing formatting
	// i is our loop counter
	// final will tell us whether or not the factored remains are in the numer or denom
	int factor = 0, printed = 0, i = 0;
	vector<int> final;

	final.resize(numerator.size());
	for (i = 0; i < numerator.size(); i++) {
		factor = numerator[i] - denominator[i];
		final.push_back(factor);
	}

	for (i = 0; i < final.size(); i++) {
		if (final[i] > 0) {
			while (final[i] > 0)
			{	
				if (printed == 0) printf("%d", i);
				else printf(" * %d", i);
				final[i]--;
				printed++;
			}
		}
	}
	if (printed == 0) printf("1");

	for (i = 0; i < final.size(); i++) {
		if (final[i] < 0) {
			final[i] = abs(final[i]);
			while (final[i] > 0)
			{	
				printf(" / %d", i);
				final[i]--;
				printed++;
			}
		}
	}
	printf("\n");
}

double Product::Calculate_Product() {
	double i;
	i = 0.0;
	return i;
}
