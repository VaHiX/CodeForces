// Problem: CF 1270 A - Card Game
// https://codeforces.com/contest/1270/problem/A

/*
 * Problem: Card Game
 * Algorithm: Greedy approach to determine if first player wins
 * Time Complexity: O(n) per test case, where n is the number of cards
 * Space Complexity: O(1), only using a few variables for computation
 *
 * The game involves two players with distinct card values from 1 to n.
 * Players take turns playing cards, and the higher-value card wins both.
 * The first player wins if they can eventually force the second player to run out of cards.
 * 
 * Key insight: If any card of the first player equals n (the highest value), 
 * then the first player can win immediately because the second player cannot beat it.
 * Otherwise, the outcome depends on whether the first player has a higher card than some
 * card the second player possesses in their hand.
 *
 * Logic:
 * - Read all cards of first player and check if any equal n (highest value)
 * - If yes, first player wins (output YES)
 * - If no, then the second player can possibly win due to having higher-value cards 
 *   that can beat the first player's cards in some scenario
 * - However, our code only checks for presence of n in first player's hand and returns accordingly
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    bool first(0); // Flag to indicate if first player has the highest card (n)
    for (long p = 0; p < a; p++) { // Read all cards of first player
      long x;
      scanf("%ld", &x);
      first = first | (x == n); // Set flag if any card is n
    }
    for (long p = 0; p < b; p++) { // Read all cards of second player, but do nothing with them
      long x;
      scanf("%ld", &x);
    }
    puts(first ? "YES" : "NO"); // Output result based on flag
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/