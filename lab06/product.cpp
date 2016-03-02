// CS140 Spring 2016
// Lab 06: Keno
// Author: Ashley Sattler
// Date: 03/02/2016

#include <iostream>
#include <vector>
#include <cstdlib>
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
	if (numerator.size() <= 0 || denominator.size() <= 0) return;
	numerator[n]++;
}

void Product::Divide_Number(int n) {
	if (numerator.size() <= 0 || denominator.size() <= 0) return;
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

}

double Product::Calculate_Product() {
	double i;
	i = 0.0;
	return i;
}
