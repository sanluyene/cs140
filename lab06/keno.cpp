// CS140 Spring 2016
// Lab 06: Calculating Keno odds
// Author: Ashley Sattler
// Date: 03/05/2016

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "product.h"

using namespace std;

int main (int argc, char **argv) {
	// Bet is the amount we are betting
	// Payout is the amount of the payout
	// Prob will hold the binomial multiplication result
	// Returnp is the return probability payout
	// Totalp will sum all the probability payouts
	// Catchb is the number of balls you want picked
	// Numb is the number of balls you want to match exactly
	// We need a product to do binomial multiplication
	double bet = 0.0, payout = 0.0, prob = 0.0, returnp = 0.0, totalp = 0.0;
	int catchb = 0, numb = 0;
	Product p;

	// Our first two inputs will always be the bet and the catch
	cin >> bet >> catchb;

	// We always lose our initial bet
	totalp -= bet;

	printf("Bet: %0.2f\n", bet);
	printf("Balls Picked: %d\n", catchb);
	
	// The user can match how ever many times they would like, so this
	// needs to be a while loop to allow multiple inputs
	while (cin >> numb >> payout) {
		p.Clear();
		p.Multiply_Binom(80 - catchb, 20 - numb);
		p.Multiply_Binom(catchb, numb);
		p.Divide_Binom(80, 20);
		prob = p.Calculate_Product();
		returnp = (prob * payout);
		totalp += returnp;
		printf("  Probability of catching %d of %d: ", numb, catchb);
		printf("%g -- Expected return: %g\n", prob, returnp);
	}

	printf("Your return per bet: %0.2f\n", totalp);
	totalp /= bet;
	printf("Normalized: %0.2f\n", totalp);

	return 0;
}
