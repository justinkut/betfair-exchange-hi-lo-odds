#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "prob.h"

#define MAX_SIZE 13

#define COMMISSION 0.03
#define TICKS_IN_UNIT 100

void printOdds(unsigned long int numerator, unsigned long int denominator);

// This is the betting guide. The game state is defined by the number of cards remaining in the deck = number_remaining, and the number of cards remaining in the deck that are lower than the last played card = number_lower. Input game states on the terminal in the form "number_remaining number_lower" to display the probabilities and tightest profitable backing and laying odds of all subsequent possible outcomes
int main(void) {
  unsigned long int* numeratorsResult = createProbabilitiesResult(MAX_SIZE);
  unsigned long int* denominatorsResult = createProbabilitiesResult(MAX_SIZE);

  int size;
  int numberLower;

  while(scanf("%d %d", &size, &numberLower) == 2) {
    assert(size <= MAX_SIZE);

    int lengthOfProbabilities = getLengthOfProbabilities(size);

    calculateProbabilities(numeratorsResult, denominatorsResult, size, numberLower);

    for (int i = 0; i < lengthOfProbabilities; i++) {
      printOdds(numeratorsResult[i], denominatorsResult[i]);
    }
  }

  return 0;
}

double calculate_tightest_back_odds(double probability) {
  double k = 1 - COMMISSION;
  double zero_payoff_odds = ((probability * k) + 1 - probability) / (probability * k);
  double number_ticks = floor(zero_payoff_odds * TICKS_IN_UNIT);
  double one_tick_wider = number_ticks + 1;
  double tightest_back_odds = one_tick_wider / TICKS_IN_UNIT;

  return tightest_back_odds;
}

double calculate_tightest_lay_odds(double probability) {
  double k = 1 - COMMISSION;
  double zero_payoff_odds = (k - (probability * k) + probability) / probability;
  double number_ticks = ceil(zero_payoff_odds * TICKS_IN_UNIT);
  double one_tick_wider = number_ticks - 1;
  double tightest_lay_odds = one_tick_wider / TICKS_IN_UNIT;

  return tightest_lay_odds;
}

void printOdds(unsigned long int numerator, unsigned long int denominator) {
  double probability = (double) numerator / (double) denominator;
  double odds = (double) denominator / (double) numerator;
  double tightest_back_odds = calculate_tightest_back_odds(probability);
  double tightest_lay_odds = calculate_tightest_lay_odds(probability);

  printf("P: %.3f -- O: %.3f -- B: %.2f -- L: %.2f\n", probability, odds, tightest_back_odds, tightest_lay_odds);
}
