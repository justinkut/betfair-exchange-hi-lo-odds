# Solution and Betting Guide for Betfair's Exchange Hi Lo Card Game

This is a solution and betting guide for Betfair's Exchange Hi Lo card game at https://games.betfair.com/exchange-hi-lo/standard. I figured out a polynomial time dynamic algorithm to efficiently compute the odds of any possible game outcome in no time.

The game is played with a deck of 13 cards. You play alongside the computer, which bets on whether the following card will be higher or lower than the last dealt card. For this, it follows an optimal strategy. If there are more lower cards than higher cards, it predicts that the next card will be lower. If there is an equal or higher number of higher cards remaining, then the computer predicts that the next card will be higher.

Your task is to bet on how many rounds the computer will be correct. An example outcome to bet on is "Card 7 or further". Here, you would be betting that the computer is correct until at least round 7.

The file [prob.c](prob.c) contains an detailed outline of the game in the comments, and a solution to the computation of the probabilities of all game outcomes. The solution relies on the realisation that game states are in fact independent of what specific cards have been dealt. All that matters is the number of cards remaining in the deck, and how many of those cards are lower than the last dealt card. The algorithm works by computing the probabilities of outcomes based on all the outcomes that can lead to them, in typical dynamic algorithm fashion.

The file [main.c](main.c) provides a simple betting guide. In a loop it reads lines, where you are expected to input the number of cards remaining in the deck, and the number of cards in the deck that are lower than the last card played. These two numbers should be separated by a space. When you enter a game state, the programme outputs the probabilities and odds of all successive outcomes possible in the game.

Build the betting guide by running `gcc main.c prob.c -lgmp -lm`. You will need libgmp-devel to be installed.


Here is an example of the programme in action:

![Example](example.png)

In the game's current state, we can see that there is 1 lower card, and 4 higher cards than the last dealt card. The game state is fully characterised by there being 5 cards remaining, and 1 card lower than the last dealt card. Therefore we enter "5 1" into the betting guide.

It outputs 4 lines, each corresponding to a successive outcome that can be bet on in the current game. `P` corresponds to the probability of the outcome. `O` is the odds `(1 / P)` of the outcome to 3 decimal places. `B` is the lowest odds, which if you were to back with them, would guarantee positive expected value. `L` is the highest odds, which if you were to lay with them, would guarantee positive expected value. `B` and `L` take into account the theoretical odds, and adjust for the advertised commission of 3%. You can see how this adjustment is made in [main.c](main.c).

In the game, we can see that for the first outcome, the market is backing and laying (1.26, 1.24) at the theoretically tightest odds that would ensure an expected profit after commission. In the second outcome, we can see that people are trying to lay at 1.66, while the theoretically maximum profitable laying odds given the advertised commission are 1.64. We can also see that in the second outcome, people are trying to back at 1.68 while the minimum theoretically profitable odds for backing are 1.69. This leads me to think that some people are being provided with lower commission. You can also see that in the third outcome, the tightest odds are again tighter than the theoretical backing and laying odds.

In conclusion, there probably isn't much potential in this being used for making money. People are putting up prices that are tighter than the publicly available commission allows, and the game doesn't see much volume anyway. However, this solution does provide an interesting application of dynamic algorithms.